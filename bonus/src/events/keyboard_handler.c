/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirty <dirty@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 16:15:55 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/15 02:58:47 by dirty            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "garbage_collection.h"

int		forward_handler(t_vars *vars)
{
	double	next_x;
	double	next_y;

	next_x = (double)(vars->cam.x + vars->cam.dir_x * (vars->cam.speed));
	next_y = (double)(vars->cam.y + vars->cam.dir_y * (vars->cam.speed));
	if (key_chr(vars->keys, FORWARD_KEY, K_BUFF_SIZE))
	{
		if (vars->map.array[(int)next_x][(int)(vars->cam.y)] == '0'
		&& !sprite_collision(vars->sprites, next_x, vars->cam.y, ENNEMIES_TEX,
		vars->num_sprites))
			vars->cam.x += vars->cam.dir_x * (vars->cam.speed);
		if (vars->map.array[(int)(vars->cam.x)][(int)next_y] == '0'
		&& !sprite_collision(vars->sprites, vars->cam.x, next_y, ENNEMIES_TEX,
			vars->num_sprites))
			vars->cam.y += vars->cam.dir_y * (vars->cam.speed);
		return (1);
	}
	return (0);
}

int		backward_handler(t_vars *vars)
{
	double	next_x;
	double	next_y;

	next_x = (double)(vars->cam.x - vars->cam.dir_x * (vars->cam.speed));
	next_y = (double)(vars->cam.y - vars->cam.dir_y * (vars->cam.speed));
	if (key_chr(vars->keys, BACKWARD_KEY, K_BUFF_SIZE))
	{
		if (vars->map.array[(int)next_x][(int)(vars->cam.y)] == '0'
		&& !sprite_collision(vars->sprites, next_x, vars->cam.y, ENNEMIES_TEX,
		vars->num_sprites))
			vars->cam.x -= vars->cam.dir_x * (vars->cam.speed);
		if (vars->map.array[(int)(vars->cam.x)][(int)next_y] == '0'
		&& !sprite_collision(vars->sprites, vars->cam.x, next_y, ENNEMIES_TEX,
		vars->num_sprites))
			vars->cam.y -= vars->cam.dir_y * (vars->cam.speed);
		return (1);
	}
	return (0);
}

int		right_handler(t_vars *vars)
{
	if (key_chr(vars->keys, RIGHT_KEY, K_BUFF_SIZE))
	{
		turn_right(vars);
		return (1);
	}
	return (0);
}

int		left_handler(t_vars *vars)
{
	if (key_chr(vars->keys, LEFT_KEY, K_BUFF_SIZE))
	{
		turn_left(vars);
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
