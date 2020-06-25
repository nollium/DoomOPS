/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_structs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 15:54:40 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/25 17:18:15 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_STRUCTS_H
# define PARSING_STRUCTS_H

/*
**  s_data CONTAINS ALL THE DATA RELATED TO AN MLX IMAGE
*/

typedef struct	s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			height;
	int			width;
}				t_data;

typedef struct	s_spawn
{
	double	x;
	double	y;
	char	dir;
}				t_spawn;

typedef struct	s_texture
{
	int			*array;
	int			width;
	int			height;
	int			x;
	int			y;
}				t_texture;

typedef struct	s_map
{
	int			x;
	int			y;
	char		**array;
}				t_map;

typedef struct	s_screen
{
	int			width;
	int			height;
	int			x;
	int			y;
	t_data		*img;
}				t_screen;

#endif
