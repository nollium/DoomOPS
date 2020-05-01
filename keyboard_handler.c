/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 16:15:55 by smaccary          #+#    #+#             */
/*   Updated: 2020/05/01 19:36:06 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int		forward_handler(t_vars *vars)
{
	if (key_chr(vars->keys, FORWARD_KEY, K_BUFF_SIZE))
	{
		if (vars->map.worldMap[(int)(vars->cam.x + vars->cam.dir_x * vars->cam.speed)]
			[(int)(vars->cam.y)] - '0' == 0)
			vars->cam.x += vars->cam.dir_x * vars->cam.speed;
		if (vars->map.worldMap[(int)(vars->cam.x)]
			[(int)(vars->cam.y + vars->cam.dir_y * vars->cam.speed)] - '0' == 0)
			vars->cam.y += vars->cam.dir_y * vars->cam.speed;
		return (1);
	}
	return (0);
}

static int		backward_handler(t_vars *vars)
{
	if (key_chr(vars->keys, BACKWARD_KEY, K_BUFF_SIZE))
	{
		if (vars->map.worldMap[(int)(vars->cam.x - vars->cam.dir_x * vars->cam.speed)]
			[(int)(vars->cam.y)] - '0' == 0)
			vars->cam.x -= vars->cam.dir_x * vars->cam.speed;
		if (vars->map.worldMap[(int)(vars->cam.x)]
			[(int)(vars->cam.y - vars->cam.dir_y * vars->cam.speed)] - '0' == 0)
			vars->cam.y -= vars->cam.dir_y * vars->cam.speed;
		return (1);
	}
	return (0);
}

static int		right_handler(t_vars *vars)
{
	long double old_dir_x;
	long double old_plane_x;

	if (key_chr(vars->keys, RIGHT_KEY, K_BUFF_SIZE))
	{
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
		return (1);
	}
	return (0);
}

static int		left_handler(t_vars *vars)
{
	long double old_dir_x;
	long double old_plane_x;

	if (key_chr(vars->keys, LEFT_KEY, K_BUFF_SIZE))
	{
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
		return (1);
	}
	return (0);
}

static int		alt_handler(t_vars *vars)
{
	t_camera 	*cam;
	static int	sprinting = 0;

	cam = &(vars->cam);
	if (key_chr(vars->keys, ALT_KEY, K_BUFF_SIZE) && !sprinting)
	{
		if (DEBUG_MODE)
			ft_putendl_fd("Sprinting", 1);
		cam->speed = ALT_MULT * SPEED;
		cam->turn_speed = ALT_MULT * TURN_SPEED;
		sprinting = 1;
	}
	else if (!sprinting)
	{
		cam->speed = SPEED;
		cam->turn_speed = TURN_SPEED;
	}
	else
		sprinting = 0;
	return (0);
}

int				keyboard_handler(t_vars *vars)
{
	int redraw;

	redraw = (int)(forward_handler(vars) + backward_handler(vars)
					+ right_handler(vars) + left_handler(vars) 
					+ alt_handler(vars));
	if (key_chr(vars->keys, CTRL_KEY, K_BUFF_SIZE))
	{
		if (key_chr(vars->keys, C_KEY, K_BUFF_SIZE))
			exit(0);
		redraw = 1;
		vars->cam.plane.y -= 0.01;
		vars->cam.plane.x -= 0.01;
	}
	return (redraw);
}
