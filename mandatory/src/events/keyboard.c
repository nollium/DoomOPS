/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 17:13:04 by smaccary          #+#    #+#             */
/*   Updated: 2020/08/03 19:32:58 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "garbage_collection.h"

int		left_handler(t_vars *vars)
{
	double	next_x;
	double	next_y;

	next_x = (double)(vars->cam.x - (vars->cam.dir_y) * (vars->cam.speed));
	next_y = (double)(vars->cam.y - (-vars->cam.dir_x) * (vars->cam.speed));
	if (key_chr(vars->keys, LEFT_KEY, K_BUFF_SIZE))
	{
		if (vars->map.array[(int)next_x][(int)(vars->cam.y)] == '0')
			vars->cam.x = next_x;
		if (vars->map.array[(int)(vars->cam.x)][(int)next_y] == '0')
			vars->cam.y = next_y;
		return (1);
	}
	return (0);
}

int		right_handler(t_vars *vars)
{
	double	next_x;
	double	next_y;

	next_x = (double)(vars->cam.x - (vars->cam.dir_y) * -(vars->cam.speed));
	next_y = (double)(vars->cam.y - (-vars->cam.dir_x) * -(vars->cam.speed));
	if (key_chr(vars->keys, RIGHT_KEY, K_BUFF_SIZE))
	{
		if (vars->map.array[(int)next_x][(int)(vars->cam.y)] == '0')
			vars->cam.x = next_x;
		if (vars->map.array[(int)(vars->cam.x)][(int)next_y] == '0')
			vars->cam.y = next_y;
		return (1);
	}
	return (0);
}

void	turn(t_vars *vars, double angle)
{
	long double	old_dir_x;
	long double	old_plane_x;

	old_dir_x = vars->cam.dir_x;
	vars->cam.dir_x = vars->cam.dir_x * cos(angle)
		- vars->cam.dir_y * sin(angle);
	vars->cam.dir_y = old_dir_x * sin(angle)
		+ vars->cam.dir_y * cos(angle);
	old_plane_x = vars->cam.plane.x;
	vars->cam.plane.x = vars->cam.plane.x * cos(angle)
		- vars->cam.plane.y * sin(angle);
	vars->cam.plane.y = old_plane_x * sin(angle)
		+ vars->cam.plane.y * cos(angle);
}

int		keyboard_handler(t_vars *vars)
{
	int redraw;

	redraw = (int)(forward_handler(vars) | backward_handler(vars)
					| right_handler(vars) | left_handler(vars)
					| alt_handler(vars) | turn_left_handler(vars)
					| turn_right_handler(vars));
	if (key_chr(vars->keys, CTRL_KEY, K_BUFF_SIZE))
	{
		if (key_chr(vars->keys, C_KEY, K_BUFF_SIZE))
		{
			free_vars(vars);
			exit(0);
		}
	}
	return (redraw);
}
