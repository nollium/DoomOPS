/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 19:52:44 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/19 15:12:14 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void *printshit(void *str)
{
	ft_putendl_fd((char *)str, 1);
	return (NULL);
}

int get_conf(t_vars *vars, char *line)
{
	static char *text_type[] = {"NO", "SO", "WE", "EA", "S ", 0};
	int i;
	int error;

	i = -1;
	error = SUCCESS_CODE;
	if (ft_strnstr(line, "R ", 2))
		error = parse_resolution(line + 2, &(vars->game_screen));
	else if (ft_strnstr(line, "F ", 2))
		vars->floor_color = parse_color(line + 2);
	else if (ft_strnstr(line, "C ", 2))
		vars->roof_color =  parse_color(line + 2);
	else
		while (text_type[++i])
			if (ft_strnstr(line, text_type[i], 2))
				if (!(vars->text_paths[i] = ft_strtrim(line + 2, WHITESPACES)))
					return (MALLOC_ERROR);
	if (error != SUCCESS_CODE)
		return (error);
	return (SUCCESS_CODE);
}

int parse_config(t_list *cub, t_vars *vars)
{
	char *line __attribute__((cleanup(free_str)));
	int  error;

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
	}
	if (vars->floor_color < 0 || vars->roof_color < 0)
		return (COLOR_ERROR);
	vars->text_paths[5] = NULL;
	return (SUCCESS_CODE);
}

int read_cub(char *path, t_list **alst)
{
	char *line;
	int error;
	int fd;
	int len;

	fd = open(path, O_RDONLY);
	*alst = NULL;
	len = 0;
	while ((error = get_next_line(fd, &line)) == 1)
	{
		(len)++;
		if (line)
			ft_lstadd_back(alst, ft_lstnew(line));
		else
		{
			close(fd);
			ft_lstclear(alst, free);
			return (-1);
		}
	}
	close(fd);
	return ((!error) ? len : error == -1 || !*alst);
}

int	find_spawn(char **map, t_spawn *spawn)
{
	char	*spawn_ptr;
	char	*last_ptr;
	int		x;
	int		y;
	
	y = -1;
	x = -1;
	*spawn = (t_spawn){-1, -1, 0};
	while (map[++x])
	{
		if ((spawn_ptr = ft_setchr(map[x], SPAWN_CHARS))
						!= (last_ptr = ft_setrchr(map[x], SPAWN_CHARS)))
			return (MAP_ERROR);
		else if (spawn_ptr)
		{
			if (spawn->x != -1 && spawn->y != -1)
				return (MAP_ERROR);
			spawn->x = (double)x;
			spawn->y = (double)(spawn_ptr - map[x]);
			spawn->dir = map[(int)spawn->x][(int)spawn->y];
			map[(int)spawn->x][(int)spawn->y] = '0';
		}
	}
	if (spawn->x <= 0 || spawn->y <= 0 || !ft_strchr(SPAWN_CHARS, spawn->dir))
		return (MAP_ERROR);
	return (SUCCESS_CODE);
}

int	parse_sprites(t_vars *vars, char **map, int *size)
{
	t_sprite	*array;
	int			x;
	int			y;
	int			i;
	
	x = -1;
	y = -1;
	*size = 0;
	while (map[++x])
	{
		y = -1;
		while (map[++y])
			if (map[x][y] == '2')
				(*size)++;
	}
	if (!(array = malloc(sizeof(t_sprite) * (1 + *size))))
		return (MALLOC_ERROR);
	x = -1;
	y = -1;
	i = 0;
	while (map[++x])
	{
		y = -1;
		while (map[++y])
			if (map[x][y] == '2')
				array[i++] = (t_sprite){x, y, 0, 4};
	}
	vars->map.array = array;
	return (SUCCESS_CODE);
}

int load_cub(char *path, t_vars *vars)
{
	t_list *cub;
	int len;
	int error;

	if (!ft_strnstr(path + ft_strlen(path) - 4, ".cub", 4))
		return (WRONG_EXTENSION_ERROR);
	vars->map = (t_map){0, 0, 0};
	if ((len = read_cub(path, &cub)) <= 0)
		return (FILE_INVALID_ERROR);
	if ((error = parse_config(cub, vars)) != SUCCESS_CODE)
		return (error);
	if (!(vars->map.array = parse_array(cub, len)))
		return (MAP_ERROR);
	if (find_spawn(vars->map.array, &(vars->spawn)) != SUCCESS_CODE)
		return (MAP_ERROR);
	if ((error = parse_sprites(vars, vars->map.array, &(vars->num_sprites)))
				 != SUCCESS_CODE)
		return (error);
	return (SUCCESS_CODE);
}