/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 17:13:04 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/16 19:21:27 by user42           ###   ########.fr       */
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
