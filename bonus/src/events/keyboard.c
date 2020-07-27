/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 17:13:04 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/27 18:39:56 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "garbage_collection.h"
#include "sprites.h"

int				shoot_sprites(t_sprite **ptr, int *n_sprites)
{
	int			i;
	t_sprite	*sprites;

	sprites = *ptr;
	i = *n_sprites;
	while (--i >= 0)
	{
		if (sprites[i].seen && sprites[i].tex_num == ENNEMIES_TEX)
		{
			sprites[i].hp -= GUN_DAMAGE;
			if (sprites[i].hp <= 0)
			{
				play_death_sound(rand() % 6);
				swap_sprites(sprites + i, sprites);
				(*n_sprites)--;
				(*ptr)++;
			}
			return (1);
		}
	}
	return (0);
}

int				switch_closest_door(t_vars *vars)
{
	int		n;
	int		*tex_num;
	double	dist;

	n = -1;
	while (++n < vars->num_sprites)
	{
		tex_num = &(vars->sprites[n].tex_num);
		if (*tex_num == DOOR_TEX || *tex_num == DOOR_OPEN_TEX)
		{
			dist = my_dist(vars->sprites[n].x, vars->sprites[n].y,
							vars->cam.x, vars->cam.y);
			if (SPRITE_RADIUS < dist && dist <= SPRITE_RADIUS + 1)
			{
				if (*tex_num == DOOR_TEX)
					*tex_num = DOOR_OPEN_TEX;
				else if (*tex_num == DOOR_OPEN_TEX)
					*tex_num = DOOR_TEX;
				system("(" PLAYER " " DOOR_SOUND BACKGROUND ") " OPTIONS);
				return (1);
			}
		}
	}
	return (1);
}

int				doors_handler(t_vars *vars)
{
	int			n;
	static int	released = 1;

	n = -1;
	if (key_chr(vars->keys, USE_KEY, K_BUFF_SIZE))
	{
		if (released)
			switch_closest_door(vars);
		released = 0;
		return (1);
	}
	released = 1;
	return (0);
}

int				arrow_handler(t_vars *vars)
{
	if (key_chr(vars->keys, ARROW_UP_KEY, K_BUFF_SIZE))
		vars->pitch += 30;
	if (key_chr(vars->keys, ARROW_DOWN_KEY, K_BUFF_SIZE))
		vars->pitch -= 30;
	if (key_chr(vars->keys, ARROW_LEFT_KEY, K_BUFF_SIZE))
		turn_left(vars, TURN_SPEED);
	if (key_chr(vars->keys, ARROW_RIGHT_KEY, K_BUFF_SIZE))
		turn_right(vars, TURN_SPEED);
	if (key_chr(vars->keys, SHOOT_KEY, K_BUFF_SIZE))
		click_handler(vars);
	check_pitch(&(vars->pitch));
	return (1);
}

int				keyboard_handler(t_vars *vars)
{
	int redraw;

	redraw = (int)(forward_handler(vars) | backward_handler(vars)
					| right_handler(vars) | left_handler(vars)
					| alt_handler(vars) | mouse_move_handler(vars)
					| click_handler(vars) | doors_handler(vars)
					| arrow_handler(vars));
	if (key_chr(vars->keys, CTRL_KEY, K_BUFF_SIZE))
	{
		vars->pos_z = CAM_HEIGHT + CROUNCH;
		if (key_chr(vars->keys, C_KEY, K_BUFF_SIZE))
		{
			free_vars(vars);
			exit(0);
		}
	}
	else
		vars->pos_z = CAM_HEIGHT;
	return (redraw);
}
