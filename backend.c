/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 19:52:44 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/15 23:40:22 by smaccary         ###   ########.fr       */
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

int format_map_line(char *line)
{
	int error;
	int i;

	i = -1;
	error = 0;
	printf("\e[31m%p: %s\e[0m\n", line, line);
	if (!line || !*line)
		return ((line) ? 0 : 1);
	while (line[++i])
	{
		if (ft_isspace(line[i]))
			line[i] = '0';
		if (!ft_isalnum(line[i]))
			error = 1;
	}
	printf("\e[32m%p: %s\e[0m\n", line, line);
	return (error);
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

char **parse_array(t_list *lst, int len)
{
	char **array;
	int error;

	error = 0;
	if (lst && (array = malloc(sizeof(char *) * (len + 1))))
	{
		len = 1;
		while (lst->next && !ft_isdigit(*(char *)(lst->content)) && !ft_isspace(*(char *)lst->content))
			lst = lst->next;
		array[0] = lst->content;
		error |= format_map_line(array[0]);
		while ((lst = lst->next) && !(error |= format_map_line(lst->content)))
			array[len++] = lst->content;
		array[len] = NULL;
	}
	else
		array = NULL;
	ft_lstclear(&lst, NULL);
	if (error)
	{
		free(array);
		return (NULL);
	}
	len = -1;
	while (DEBUG_MODE && array && array[++len]) // print map
		ft_putendl_fd(array[len], 2);
	return (array);
}

int get_resolution(char *line, t_screen *screen)
{
	char **array __attribute__((cleanup(free_split)));
	int i;

	array = ft_split(line, ' ');
	i = -1;
	while (array[++i])
		if (i > 1)
			return (RESOLUTION_ERROR);
	screen->width = ft_atoi(array[0]);
	screen->height = ft_atoi(array[1]);
	if (screen->width <= 0 || screen->height <= 0)
		return (RESOLUTION_ERROR);
	return (SUCCESS_CODE);
}

int get_conf(t_vars *vars, char *line)
{
	static char *text_type[] = {"NO", "SO", "WE", "EA", "S ", 0};
	int i;

	i = -1;
	if (ft_strnstr(line, "R ", 2))
		get_resolution(line + 2, &(vars->game_screen));
	else if (ft_strnstr(line, "F ", 2))
		;
	else if (ft_strnstr(line, "C ", 2))
		;
	else
		while (text_type[++i])
			if (ft_strnstr(line, text_type[i], 2))
				vars->text_paths[i] = ft_strtrim(line + 2, WHITESPACES);
	return (SUCCESS_CODE);
}

int parse_config(t_list *cub, t_vars *vars)
{
	char *line __attribute__((cleanup(free_str)));

	line = NULL;
	if (!cub || !vars)
		return (NULL_ERROR);
	while (cub->next)
	{
		if (ft_replace_charset(cub->content, WHITESPACES, ' ') < 0)
			return (NULL_ERROR);
		if (!(line = ft_strtrim(cub->content, WHITESPACES)))
			return (MALLOC_ERROR);
		if (get_conf(vars, line) != SUCCESS_CODE)
			return (CONFIG_ERROR);
		cub = cub->next;
	}
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
	if ((len = read_cub(path, &cub)) <= 0) // FIXED
		return (FILE_INVALID_ERROR);
	if ((error = parse_config(cub, vars)) != SUCCESS_CODE)
		return (error);
	if (!(vars->map.worldMap = parse_array(cub, len)))
		return (MAP_ERROR);
	return (SUCCESS_CODE);
}