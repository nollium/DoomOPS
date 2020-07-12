/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemies.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirty <dirty@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 15:43:58 by dirty             #+#    #+#             */
/*   Updated: 2020/07/12 15:50:09 by dirty            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

double  my_dist(double x0, double y0, double x1, double y1)
{    
    return (sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1)));
}

int		sprite_collision(t_sprite *sprites, double x, double y)
{
	int	i;

	i = -1;
	while (sprites[++i].tex_num)
	{
		if (sprites[i].tex_num == ENNEMIES_TEX)
		{
			if (my_dist(sprites[i].x, sprites[i].y, x, y) <= SPRITE_RADIUS)
				return (1);
		}
	}
	return (0);
}