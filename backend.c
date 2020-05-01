/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 19:52:44 by smaccary          #+#    #+#             */
/*   Updated: 2020/05/01 13:27:17 by smaccary         ###   ########.fr       */
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



/*
t_map   parse_map(char *path)
{
	int		fd;
	char	*line;
	t_map	map;

	if fd = open(path, O_RDONLY);
	map.height = 0;
	map.width = 0;

}*/