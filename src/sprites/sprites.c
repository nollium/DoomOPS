/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 21:40:17 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/27 18:32:18 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprites.h"

void		draw_sprite_pxl(t_sprite_drawer *draw, int stripe, t_data *img)
{
	register size_t d;
	register int 	y;

	y = draw->start_y - 1;
	while (++y < draw->end_y)
	{
		d = (y) * 256 + draw->factor_128;
		draw->text_y = ((d * draw->text->width)
						/ (draw->sprite_height) / 256);
		draw->color = draw->text->array[draw->text->width
										* draw->text_y + draw->text_x]; 
		my_mlx_pixel_put(img, stripe, y, (SHADOW_MODE) ?
					add_shade(draw->shader, draw->color) : draw->color);
	}
}

void		draw_sprites(t_sprite_drawer *draw, t_sprite *sprites,
						double *sprites_depth, t_data *img)
{
	int	stripe;

	stripe = draw->start_x - 1;
	while (++stripe < draw->end_x)
	{
		draw->text_x = (int)(stripe * draw->pre_calc1 + draw->pre_calc2);
		if (draw->transform_y > 0 && stripe > 0 && stripe < draw->screen->width
			&& draw->transform_y < sprites_depth[stripe])
		{
			draw_sprite_pxl(draw, stripe, img);
			sprites[draw->sprite_index].seen = 1;
		}
		else
			sprites[draw->sprite_index].seen = 0;
	}
}

void		put_sprites(t_vars *vars, t_sprite *sprites,
						t_sprites_sorter *sprites_srt, t_camera *cam)
{
	int 			i;
	t_sprite		v_sprite;
	t_sprite_drawer	draw;

	draw.denom = 1.0 / (cam->plane.x * cam->dir_y - cam->dir_x * cam->plane.y);
	draw.screen = &(vars->game_screen);
	draw.half_win_height = draw.screen->height / 2;
	draw.half_win_width = draw.screen->width / 2;
	i = -1;
	while (++i < vars->num_sprites)
	{
		draw.sprite_index = sprites_srt[i].sprite_order;
		v_sprite = sprites[draw.sprite_index];
		v_sprite.x -= cam->x;
		v_sprite.y -= cam->y;
		draw.dist = sqrt(v_sprite.x * v_sprite.x + v_sprite.y * v_sprite.y);
		if 	(draw.dist < 8 || !SHADOW_MODE)
		{
			init_sprite_drawing(&draw, cam, &v_sprite,
								vars->text + v_sprite.tex_num);
			draw_sprites(&draw, sprites, vars->z_buffer, vars->img);
		}
	}
}
