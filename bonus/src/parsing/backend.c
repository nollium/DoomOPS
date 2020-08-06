/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 19:52:44 by smaccary          #+#    #+#             */
/*   Updated: 2020/08/06 18:03:17 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "mlx.h"

int	get_conf(t_vars *vars, char *line)
{
	static char	*text_type[] = {"NO", "SO", "WE", "EA", "S ", "DC", "EN", "DO",
								0};
	int			i;
	int			error;

	i = -1;
	error = SUCCESS_CODE;
	if (ft_strnstr(line, "R ", 2))
		error = parse_resolution(line + 2, &(vars->game_screen));
	else if (ft_strnstr(line, "F ", 2))
		vars->floor_color = parse_color(line + 2);
	else if (ft_strnstr(line, "C ", 2))
		vars->roof_color = parse_color(line + 2);
	else
		while (text_type[++i])
			if (ft_strnstr(line, text_type[i], 2))
				if (!(vars->text_paths[i] = ft_strtrim(line + 2, WHITESPACES)))
					return (MALLOC_ERROR);
	if (error != SUCCESS_CODE)
		return (error);
	vars->roof_color = (vars->roof_color == 0x1) ? 0 : vars->roof_color;
	vars->floor_color = (vars->floor_color == 0x1) ? 0 : vars->floor_color;
	return (SUCCESS_CODE);
}

int	check_resolution(void *mlx, int *width, int *height)
{
	int	max_width;
	int max_height;

	mlx_get_screen_size(mlx, &max_width, &max_height);
	*width = (*width > max_width || *width < 0) ? max_width : *width;
	*height = (*height > max_height || *height < 0) ? max_height : *height;
	return (SUCCESS_CODE);
}

int	parse_config(t_list *cub, t_vars *vars)
{
	char	*line __attribute__((cleanup(free_str)));
	int		error;

	line = NULL;
	if (!cub || !vars)
		return (NULL_ERROR);
	while (cub->next)
	{
		if (ft_replace_charset(cub->content, WHITESPACES, ' ') < 0)
			return (NULL_ERROR);
		if (!(line = ft_strtrim(cub->content, WHITESPACES)))
			return (MALLOC_ERROR);
		if ((error = get_conf(vars, line)) != SUCCESS_CODE)
			return (error);
		cub = cub->next;
		free(line);
		line = NULL;
	}
	if (vars->floor_color < 0 || vars->roof_color < 0)
		return (COLOR_ERROR);
	vars->text_paths[T_BUFF_SIZE] = NULL;
	return (SUCCESS_CODE);
}

int	read_cub(char *path, t_list **alst)
{
	char	*line;
	int		error;
	int		fd;
	int		len;

	if ((fd = open(path, O_RDONLY)) <= 0)
		return (FILE_INVALID_ERROR);
	*alst = NULL;
	len = 0;
	while ((error = get_next_line(fd, &line)) == 1)
	{
		(len)++;
		if (line)
			ft_lstadd_back(alst, ft_lstnew(line));
		else
			ft_lstclear(alst, free);
	}
	free(line);
	close(fd);
	if (error != SUCCESS_CODE || !*alst)
		return ((error != SUCCESS_CODE) ? error : NULL_ERROR);
	return (len);
}

int	load_cub(char *path, t_vars *vars)
{
	t_list	*cub __attribute__((cleanup(free_cub)));
	int		len;
	int		error;

	cub = NULL;
	if (!ft_strnstr(path + ft_strlen(path) - 4, CONF_FILE_EXTENSION, 4))
		return (WRONG_EXTENSION_ERROR);
	vars->map = (t_map){0};
	if ((len = read_cub(path, &cub)) <= 0)
		return (FILE_INVALID_ERROR);
	if ((error = parse_config(cub, vars)) != SUCCESS_CODE)
		return (error);
	if (!(vars->map.array = parse_array(cub, len)))
		return (MAP_ERROR);
	if (find_spawn(vars->map.array, &(vars->spawn)) != SUCCESS_CODE)
		return (MAP_ERROR);
	if (parse_sprites(vars, vars->map.array, &(vars->num_sprites))
		!= SUCCESS_CODE)
		return (MAP_ERROR);
	return (check_borders(vars->map.array));
}
