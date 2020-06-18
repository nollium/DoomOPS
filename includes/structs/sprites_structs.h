/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_structs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 16:01:39 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/18 16:03:59 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_STRUCT_H
 #define SPRITES_STRUCT_H

 #include "structs.h"

 typedef struct s_sprite
{
	double		x;
	double		y;
	char		seen;
	int			tex_num;
}				t_sprite;

typedef struct s_sprites_sorter
{
	int			sprite_order;
	double		sprite_distance;
}				t_sprites_sorter;

typedef struct s_sprite_drawer
{
	double		sprite_x;
	double		sprite_y;
	double		transform_x;
	double		transform_y;
	double		denom;
	double		dist;
	int			sprite_screen_x;
	int			sprite_height;
	double		half_sprite_height;
	double		sprite_width;
	double		half_sprite_width;
	double		half_win_height;
	double		half_win_width;
	int			start_x;
	int			start_y;
	int			end_x;
	int			end_y;
	size_t		text_x;
	size_t		text_y;
	int			color;
	double		shader;
	double		pre_calc1;
	double		pre_calc2;
	int			factor_128;
	t_texture	*text;
	int			sprite_index;
	t_screen	*screen;
}				t_sprite_drawer;

#endif