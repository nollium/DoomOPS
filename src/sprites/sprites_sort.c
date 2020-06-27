/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 21:43:54 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/27 17:31:06 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprites.h"

static void swap_sprites(t_sprites_sorter *sprite_1, t_sprites_sorter *sprite_2)
{
	t_sprites_sorter	tmp;
	
	tmp = *sprite_1;
	*sprite_1 = *sprite_2;
	*sprite_2 = tmp;
}

/*
**	Insertion sort 
*/

void	    sort_sprites(int n, t_sprites_sorter *arr)
{
	int	i;
	int	j;

	i = 1;
	while (i < n)
	{
		j = i;
		while (j > 0 && arr[j - 1].sprite_distance < arr[j].sprite_distance)
		{
			swap_sprites(arr + j, arr + j - 1);
			j--;
		}
		i++;
	}
}