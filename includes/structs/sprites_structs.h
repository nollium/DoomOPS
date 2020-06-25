/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_structs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 16:01:39 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/25 17:19:03 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_STRUCTS_H
# define SPRITES_STRUCTS_H

# include "structs.h"

typedef struct	s_sprite
{
	double		x;
	double		y;
	char		seen;
	int			tex_num;
}				t_sprite;

typedef struct	s_sprites_sorter
{
	int			sprite_order;
	double		sprite_distance;
}				t_sprites_sorter;

#endif
