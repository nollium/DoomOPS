/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvements.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:30:19 by smaccary          #+#    #+#             */
/*   Updated: 2020/08/04 18:30:19 by smaccary         ###   ########.fr       */
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
