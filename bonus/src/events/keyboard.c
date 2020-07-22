/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirty <dirty@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 17:13:04 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/22 04:24:40 by dirty            ###   ########.fr       */
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

int				keyboard_handler(t_vars *vars)
{
	int redraw;

	redraw = (int)(forward_handler(vars) | backward_handler(vars)
					| right_handler(vars) | left_handler(vars)
					| alt_handler(vars) | mouse_move_handler(vars)
					| click_handler(vars));
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
