/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 19:52:44 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/14 01:39:56 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    hooks(t_vars *vars)
{
	mlx_hook(vars->win, KeyPress, KeyPressMask, key_handler, (void *)vars);
	mlx_mouse_hook(vars->win, mouse_handler, vars);
	mlx_hook(vars->win, ResizeRequest, 1, resize_handler, (void *)0);
	mlx_hook(vars->win, EnterNotify, EnterWindowMask, enter_handler, NULL);
	mlx_hook(vars->win, LeaveNotify, LeaveWindowMask, leave_handler, NULL);
	mlx_hook(vars->win, KeyRelease, KeyReleaseMask, release_handler, (void *)vars);
	mlx_loop_hook(vars->mlx, loop_handler, (void *)vars);
}

void	*printshit(void *str)
{
	ft_putendl_fd((char *)str, 1);
	return (NULL);
}

int		format_map_line(char *line)
{
	int	error;
	int	i;
	
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

int		read_cub(char *path, t_list **alst)
{
	char	*line;
	int		error;
	int		fd;
	int		len;

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

char	**parse_array(t_list *lst, int len)
{
	char	**array;
	int		error;

	error = 0;
	if (lst && (array = malloc(sizeof(char *) * (len + 1))))
	{	
		len = 1;
		while (lst->next && !ft_isdigit(*(char *)(lst->content)) && !ft_isspace(*(char *)lst->content))
			lst = lst->next;
		array[0] = lst->content;
		error |= format_map_line(array[0]);
		while ((lst = lst->next))
		{
			//DEBUG_PRINT("WSH LA ZONE LE 100 TEAM JUL");
			if (!(error |= format_map_line(lst->content)))
			{
				//DEBUG_PRINT("La tu vois j'assigne une valeur à cette merde");
				array[len++] = lst->content;
			//	DEBUG_PRINT("Et là c'est fait (:");
			}
			else
				break;
		}
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

int   load_cub(char *path, t_vars *vars)
{
	t_list	*lst;
	int		len;
	
	if (!ft_strnstr(path + ft_strlen(path) - 4, ".cub", 4))
		return (WRONG_EXTENSION_ERROR);
	vars->map = (t_map){0, 0, 0};
	if ((len = read_cub(path, &lst)) <= 0) // FIXED
		return (FILE_INVALID_ERROR);
	if (!(vars->map.worldMap = parse_array(lst, len)))
		return (MAP_ERROR);
	return (SUCCESS_CODE);
}