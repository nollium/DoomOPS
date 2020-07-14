/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirty <dirty@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 17:13:04 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/14 19:27:15 by dirty            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "garbage_collection.h"
#include "sprites.h"

int				shoot_sprites(t_sprite *sprites, t_camera *cam, int *n_sprites)
{
	int		i;
	double	min_dist;
	double	dist;
	int		min_i;
	
	i = -1;
	min_dist = -1;
	min_i = -1;
	while (++i < *n_sprites)
	{
		if (sprites[i].hp > 0 && sprites[i].seen && sprites[i].tex_num
			== ENNEMIES_TEX)
		{
			dist = my_dist(sprites[i].x, sprites[i].y, cam->x, cam->y);
			if (min_dist == -1 || dist < min_dist)
			{
				min_dist = dist;
				min_i = i;	
		
			}
		}
	}
	if (min_i == -1 || min_dist == -1)
		return (0);
	sprites[min_i].hp -= GUN_DAMAGE;
	if (sprites[min_i].hp <= 0)
	{
		swap_sprites(sprites + min_i, sprites + *n_sprites);
		(*n_sprites)--;
	}
	return (1);
}

int				click_handler(t_vars *vars)
{
	static clock_t	last_shot = 0;
	double			elapsed;
	static int		released = 1;
	
	elapsed = (double)(clock() - last_shot) / (double)CLOCKS_PER_SEC;
	if (!released && !key_chr(vars->keys, LEFT_CLICK, K_BUFF_SIZE))
		released = 1;
	if (key_chr(vars->keys, LEFT_CLICK, K_BUFF_SIZE)
		&& elapsed > (double)SHOT_DURATION && released)
	{
		released = 0;
		if (elapsed > (double)SHOT_DURATION + (double)SHOT_COOLDOWN)
		{
			last_shot = clock();
			vars->draw_shot = 1;
			system("(" PLAYER " " GUNSHOT_PATH BACKGROUND ") "  OPTIONS);
			shoot_sprites(vars->sprites, &(vars->cam), &(vars->num_sprites));
			return (1);
		}
	}
	if (elapsed > (double)SHOT_DURATION && vars->draw_shot)
	{
		vars->draw_shot = 0;
		return (1);
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
