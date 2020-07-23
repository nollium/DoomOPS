/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 17:13:04 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/23 18:33:09 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "garbage_collection.h"
#include "sprites.h"

void			play_death_sound(int n)
{
	static int last = 0;

	if (last == n)
		n = (n + 1) % 6;
	last = n;
	if (n == 0)
		system("(" PLAYER " " EN_DEATH_00 BACKGROUND ") " OPTIONS);
	if (n == 1)
		system("(" PLAYER " " EN_DEATH_01 BACKGROUND ") " OPTIONS);
	if (n == 2)
		system("(" PLAYER " " EN_DEATH_02 BACKGROUND ") " OPTIONS);
	if (n == 3)
		system("(" PLAYER " " EN_DEATH_03 BACKGROUND ") " OPTIONS);
	if (n == 4)
		system("(" PLAYER " " EN_DEATH_04 BACKGROUND ") " OPTIONS);
	if (n == 5)
		system("(" PLAYER " " EN_DEATH_05 BACKGROUND ") " OPTIONS);
}

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

int				doors_handler(t_vars *vars)
{
	int			n;
	int			*tex_num;
	static int	released = 1;

	n = -1;
	if (key_chr(vars->keys, USE_KEY, K_BUFF_SIZE))
	{
		while (released && ++n < vars->num_sprites)
		{
			tex_num = &(vars->sprites[n].tex_num);
			if (*tex_num == DOOR_TEX || *tex_num == DOOR_OPEN_TEX)
			{
				if (my_dist(vars->sprites[n].x, vars->sprites[n].y, vars->cam.x, vars->cam.y) <= SPRITE_RADIUS + 1)
				*tex_num = (*tex_num == DOOR_TEX) ? DOOR_OPEN_TEX : DOOR_TEX;
			}
		}
		released = 0;
		return (1);
	}
	released = 1;
	return (0);
}

int				keyboard_handler(t_vars *vars)
{
	int redraw;

	redraw = (int)(forward_handler(vars) | backward_handler(vars)
					| right_handler(vars) | left_handler(vars)
					| alt_handler(vars) | mouse_move_handler(vars)
					| click_handler(vars) | doors_handler(vars));
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
