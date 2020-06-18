/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 15:46:42 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/18 16:06:30 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
 #define STRUCTS_H
 #include "events_structs.h"
 #include "parsing_structs.h"
 #include "draw_structs.h"
 #include "raycast_structs.h"
 #include "sprites_structs.h"

 #include <stdlib.h>

 #define K_BUFF_SIZE 20

typedef struct	s_db_point
{
	double	x;
	double	y;
}				t_db_point;

typedef struct  s_vars
{
	void        *mlx;
	void        *win;
	t_screen	game_screen;
	t_map		map;
	t_data      *img;
	t_data      img2[2];
	t_camera	cam;
	t_keys      keys[K_BUFF_SIZE + 1];
	t_texture	*text;
	t_sprite	*sprites;
	t_spawn		spawn;
	int			floor_color;
	int			roof_color;
	char		*text_paths[6];
	int			num_sprites;
	double		*z_buffer;
	int			redraw;
	int			seen_sprite;
	//int			w_color;
}               t_vars;

#endif