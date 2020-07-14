/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirty <dirty@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 21:41:36 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/14 23:52:23 by dirty            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprites.h"

void		init_sprites_info(t_camera *cam, t_sprite *sprites, int n)
{
	sort_sprites(cam, sprites, n);
}

static void	get_stripe_size(t_sprite_drawer *draw)
{
	draw->start_y = -draw->half_sprite_height + draw->half_win_height;
	draw->start_y = (draw->start_y < 0) ? 0 : draw->start_y;
	draw->end_y = draw->half_sprite_height + draw->half_win_height;
	if (draw->end_y >= draw->screen->height)
		draw->end_y = draw->screen->height - 1;
	draw->sprite_width = fabs((draw->screen->height / (draw->transform_y)));
	draw->half_sprite_width = draw->sprite_width / 2;
	draw->start_x = -draw->half_sprite_width + draw->sprite_screen_x + 1;
	draw->start_x = (draw->start_x < 0) ? 0 : draw->start_x;
	draw->end_x = draw->half_sprite_width + draw->sprite_screen_x;
	if (draw->end_x >= draw->screen->width)
		draw->end_x = draw->screen->width - 1;
}

static void	init_sprite_texture(t_sprite_drawer *draw, t_texture *text)
{
	draw->text = text;
	draw->factor_128 = (-draw->screen->height + draw->sprite_height) * 128;
	draw->shader = draw->dist / 16 * 2;
	draw->pre_calc1 = ((double)draw->text->width / (double)draw->sprite_width);
	draw->pre_calc2 = -draw->pre_calc1
	* (-draw->half_sprite_width + draw->sprite_screen_x);
}

void		init_sprite_drawing(t_sprite_drawer *draw, t_camera *cam,
								t_sprite *v_sprite, t_texture *text)
{
	draw->transform_x = draw->denom * (cam->dir_y * v_sprite->x - cam->dir_x
	* v_sprite->y);
	draw->transform_y = draw->denom * (-cam->plane.y * v_sprite->x
	+ cam->plane.x * v_sprite->y);
	draw->sprite_screen_x = (int)(draw->half_win_width) * (1 + draw->transform_x
	/ draw->transform_y);
	draw->sprite_height = fabs((int)draw->screen->height / (draw->transform_y));
	draw->half_sprite_height = draw->sprite_height / 2;
	get_stripe_size(draw);
	init_sprite_texture(draw, text);
}
