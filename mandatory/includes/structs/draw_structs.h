/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:30:19 by smaccary          #+#    #+#             */
/*   Updated: 2020/08/04 18:30:19 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_STRUCTS_H
# define DRAW_STRUCTS_H
# include "structs.h"
# include <sys/types.h>

typedef struct	s_drawer
{
	int			start;
	int			end;
	int			color;
	int			line_height;
	int			x;
	int			y;
	int			dist;
	int			side;
	double		step;
	double		tex_pos;
	int			floor_color;
	int			roof_color;
	t_screen	*screen;

}				t_drawer;

typedef struct	s_sprite_drawer
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
	ssize_t		text_x;
	ssize_t		text_y;
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
