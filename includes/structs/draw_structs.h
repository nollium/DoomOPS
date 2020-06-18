/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 15:56:52 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/18 15:58:02 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_STRUCTS_H
 #define DRAW_STRUCTS_H
 #include "structs.h"

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
	double 		step;
	double		tex_pos;
	t_screen	*screen;
	
}				t_drawer;
#endif