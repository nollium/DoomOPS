/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:00:23 by user42            #+#    #+#             */
/*   Updated: 2020/07/15 16:00:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

double  my_dist(double x0, double y0, double x1, double y1)
{    
    return (sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1)));
}

int		s_s_collision(t_sprite *sprites, t_sprite *curr, double x, double y,
						int n)
{
	while (--n >= 0)
	{
		if (sprites[n].tex_num == ENNEMIES_TEX && sprites + n != curr)
		{
			if (my_dist(sprites[n].x + 0.5, sprites[n].y + 0.5, x, y)
				<= SPRITE_RADIUS)
				return (n + 1);
		}
	}
	return (0);
}

int		sprite_collision(t_sprite *sprites, double x, double y, int tex, int n)
{
	while (--n >= 0)
	{
		if (sprites[n].tex_num == tex)
		{
			if (my_dist(sprites[n].x, sprites[n].y, x, y) <= SPRITE_RADIUS)
				return (n + 1);
		}
	}
	return (0);
}
