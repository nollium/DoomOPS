/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 19:52:44 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/16 17:04:59 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void hooks(t_vars *vars)
{
	mlx_hook(vars->win, KeyPress, KeyPressMask, key_handler, (void *)vars);
	mlx_mouse_hook(vars->win, mouse_handler, vars);
	mlx_hook(vars->win, ResizeRequest, 1, resize_handler, (void *)0);
	mlx_hook(vars->win, EnterNotify, EnterWindowMask, enter_handler, NULL);
	mlx_hook(vars->win, LeaveNotify, LeaveWindowMask, leave_handler, NULL);
	mlx_hook(vars->win, KeyRelease, KeyReleaseMask, release_handler, (void *)vars);
	mlx_loop_hook(vars->mlx, loop_handler, (void *)vars);
}

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

int load_cub(char *path, t_vars *vars)
{
	t_list *cub;
	int len;
	int error;

	if (!ft_strnstr(path + ft_strlen(path) - 4, ".cub", 4))
		return (WRONG_EXTENSION_ERROR);
	vars->map = (t_map){0, 0, 0};
	if ((len = read_cub(path, &cub)) <= 0) // FIXED
		return (FILE_INVALID_ERROR);
	if ((error = parse_config(cub, vars)) != SUCCESS_CODE)
		return (error);
	if (!(vars->map.worldMap = parse_array(cub, len)))
		return (MAP_ERROR);
	return (SUCCESS_CODE);
}