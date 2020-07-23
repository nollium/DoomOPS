/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 21:43:54 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/23 01:19:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprites.h"

int		get_n(int *init)
{
	static int	*n = NULL;

	if (init)
		n = init;
	return (*n);
}

void		swap_sprites(t_sprite *s1, t_sprite *s2)
{
	t_sprite	tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

double		s_dist(t_camera *cam, t_sprite *sprite)
{
	return ((cam->x - sprite->x) * (cam->x - sprite->x)
			+ (cam->y - sprite->y) * (cam->y - sprite->y));
}

/*
**	Insertion sort
*/

void		sort_sprites(t_camera *cam, t_sprite *arr, int n)
{
	int	i;
	int	j;

	i = 1;
	while (i < n)
	{
		j = i;
		while (j > 0 && s_dist(cam, arr + j - 1) < s_dist(cam, arr + j))
		{
			swap_sprites(arr + j, arr + j - 1);
			j--;
		}
		i++;
	}
}
