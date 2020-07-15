/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_structs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirty <dirty@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 16:01:39 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/15 01:02:06 by dirty            ###   ########.fr       */
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
	int			hp;
}				t_sprite;

#endif
