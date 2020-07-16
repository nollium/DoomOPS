/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvements.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 14:54:02 by dirty             #+#    #+#             */
/*   Updated: 2020/07/16 19:31:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

void	turn_left(t_vars *vars, double speed)
{
	long double	old_dir_x;
	long double	old_plane_x;

	old_dir_x = vars->cam.dir_x;
	vars->cam.dir_x = vars->cam.dir_x * cos(speed)
		- vars->cam.dir_y * sin(speed);
	vars->cam.dir_y = old_dir_x * sin(speed)
		+ vars->cam.dir_y * cos(speed);
	old_plane_x = vars->cam.plane.x;
	vars->cam.plane.x = vars->cam.plane.x * cos(speed)
		- vars->cam.plane.y * sin(speed);
	vars->cam.plane.y = old_plane_x * sin(speed)
		+ vars->cam.plane.y * cos(speed);
}

void	turn_right(t_vars *vars, double speed)
{
	long double	old_dir_x;
	long double	old_plane_x;

	old_dir_x = vars->cam.dir_x;
	vars->cam.dir_x = vars->cam.dir_x * cos(-speed)
		- vars->cam.dir_y * sin(-speed);
	vars->cam.dir_y = old_dir_x * sin(-speed)
		+ vars->cam.dir_y * cos(-speed);
	old_plane_x = vars->cam.plane.x;
	vars->cam.plane.x = vars->cam.plane.x * cos(-speed)
		- vars->cam.plane.y * sin(-speed);
	vars->cam.plane.y = old_plane_x * sin(-speed)
		+ vars->cam.plane.y * cos(-speed);
}
