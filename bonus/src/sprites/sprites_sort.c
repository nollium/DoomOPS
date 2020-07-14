/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirty <dirty@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 21:43:54 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/13 23:31:34 by dirty            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprites.h"

void		swap_sprites(t_sprite *s1, t_sprite *s2)
{
	t_sprite	tmp;
	
	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void		swap_sprites_sorter(t_sprites_sorter *sprite_1, t_sprites_sorter *sprite_2)
{
	t_sprites_sorter	tmp;

	tmp = *sprite_1;
	*sprite_1 = *sprite_2;
	*sprite_2 = tmp;
}

/*
**	Insertion sort
*/

void		sort_sprites(int n, t_sprites_sorter *arr)
{
	int	i;
	int	j;

	i = 1;
	while (i < n)
	{
		j = i;
		while (j > 0 && arr[j - 1].sprite_distance < arr[j].sprite_distance)
		{
			swap_sprites_sorter(arr + j, arr + j - 1);
			j--;
		}
		i++;
	}
}
