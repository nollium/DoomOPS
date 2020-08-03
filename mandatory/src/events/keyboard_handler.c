/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 16:15:55 by smaccary          #+#    #+#             */
/*   Updated: 2020/08/03 17:41:14 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "garbage_collection.h"

int		forward_handler(t_vars *vars)
{
	if (key_chr(vars->keys, FORWARD_KEY, K_BUFF_SIZE))
	{
		if (vars->map.array
		[(int)(vars->cam.x + vars->cam.dir_x * (vars->cam.speed * 3))]
		[(int)(vars->cam.y)] - '0' == 0)
			vars->cam.x += vars->cam.dir_x * (vars->cam.speed);
		if (vars->map.array[(int)(vars->cam.x)]
			[(int)(vars->cam.y + vars->cam.dir_y * (vars->cam.speed * 3))]
			- '0' == 0)
			vars->cam.y += vars->cam.dir_y * (vars->cam.speed);
		return (1);
	}
	return (0);
}

int		backward_handler(t_vars *vars)
{
	if (key_chr(vars->keys, BACKWARD_KEY, K_BUFF_SIZE))
	{
		if (vars->map.array
			[(int)(vars->cam.x - vars->cam.dir_x * (vars->cam.speed * 3))]
			[(int)(vars->cam.y)] - '0' == 0)
			vars->cam.x -= vars->cam.dir_x * (vars->cam.speed);
		if (vars->map.array[(int)(vars->cam.x)]
			[(int)(vars->cam.y - vars->cam.dir_y * (vars->cam.speed * 3))]
			- '0' == 0)
			vars->cam.y -= vars->cam.dir_y * (vars->cam.speed);
		return (1);
	}
	return (0);
}

int		turn_right_handler(t_vars *vars)
{
	if (key_chr(vars->keys, ARROW_RIGHT_KEY, K_BUFF_SIZE))
	{
		turn(vars, -vars->cam.turn_speed);
		return (1);
	}
	return (0);
}

int		turn_left_handler(t_vars *vars)
{
	if (key_chr(vars->keys, ARROW_LEFT_KEY, K_BUFF_SIZE))
	{
		turn(vars, vars->cam.turn_speed);
		return (1);
	}
	return (0);
}

int		alt_handler(t_vars *vars)
{
	t_camera	*cam;
	int			sprinting;

	sprinting = 0;
	cam = &(vars->cam);
	if (key_chr(vars->keys, ALT_KEY, K_BUFF_SIZE) && !sprinting)
	{
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
