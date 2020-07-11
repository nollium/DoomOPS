/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirty <dirty@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 14:54:02 by dirty             #+#    #+#             */
/*   Updated: 2020/07/11 14:57:19 by dirty            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

void turn_left(t_vars *vars)
{
    long double	old_dir_x;
	long double	old_plane_x;

    old_dir_x = vars->cam.dir_x;
    vars->cam.dir_x = vars->cam.dir_x * cos(vars->cam.turn_speed)
        - vars->cam.dir_y * sin(vars->cam.turn_speed);
    vars->cam.dir_y = old_dir_x * sin(vars->cam.turn_speed)
        + vars->cam.dir_y * cos(vars->cam.turn_speed);
    old_plane_x = vars->cam.plane.x;
    vars->cam.plane.x = vars->cam.plane.x * cos(vars->cam.turn_speed)
        - vars->cam.plane.y * sin(vars->cam.turn_speed);
    vars->cam.plane.y = old_plane_x * sin(vars->cam.turn_speed)
        + vars->cam.plane.y * cos(vars->cam.turn_speed);
}

void turn_right(t_vars *vars)
{
    long double	old_dir_x;
	long double	old_plane_x;

    old_dir_x = vars->cam.dir_x;
    vars->cam.dir_x = vars->cam.dir_x * cos(-vars->cam.turn_speed)
        - vars->cam.dir_y * sin(-vars->cam.turn_speed);
    vars->cam.dir_y = old_dir_x * sin(-vars->cam.turn_speed)
        + vars->cam.dir_y * cos(-vars->cam.turn_speed);
    old_plane_x = vars->cam.plane.x;
    vars->cam.plane.x = vars->cam.plane.x * cos(-vars->cam.turn_speed)
        - vars->cam.plane.y * sin(-vars->cam.turn_speed);
    vars->cam.plane.y = old_plane_x * sin(-vars->cam.turn_speed)
        + vars->cam.plane.y * cos(-vars->cam.turn_speed);
}