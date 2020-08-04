/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:30:18 by smaccary          #+#    #+#             */
/*   Updated: 2020/08/04 18:30:18 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

double	my_dist(double x0, double y0, double x1, double y1)
{
	return (sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1)));
}

int		s_s_collision(t_sprite *sprites, t_sprite *curr, double x, double y)
{
	int	n;

	n = get_n(NULL);
	while (--n >= 0)
	{
		if ((sprites[n].tex_num == ENNEMIES_TEX
			|| sprites[n].tex_num == DOOR_TEX) && sprites + n != curr)
		{
			if (my_dist(sprites[n].x + 0.5, sprites[n].y + 0.5, x, y)
				<= SPRITE_RADIUS)
				return (n + 1);
		}
	}
	return (0);
}

int		sprite_collision(t_sprite *sprites, double x, double y, int tex)
{
	int n;

	n = get_n(NULL);
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
