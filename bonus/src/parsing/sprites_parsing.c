/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirty <dirty@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 19:38:01 by user42            #+#    #+#             */
/*   Updated: 2020/07/11 16:08:03 by dirty            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_sprite	*alloc_sprites(char **map, int *size)
{
	int			x;
	int			y;

	x = -1;
	y = -1;
	*size = 0;
	while (map[++x])
	{
		y = -1;
		while (map[x][++y])
			if (map[x][y] == '2' || map[x][y] == '3')
				(*size)++;
	}
	return (malloc(sizeof(t_sprite) * (1 + *size)));
}

int				parse_sprites(t_vars *vars, char **map, int *size)
{
	t_sprite	*array;
	int			x;
	int			y;
	int			i;

	if (!(array = alloc_sprites(map, size)))
		return (MALLOC_ERROR);
	x = -1;
	y = -1;
	i = 0;
	while (map[++x])
	{
		y = -1;
		while (map[x][++y])
			if (map[x][y] == '2' || map[x][y] == '3')
			{
				array[i++] = (t_sprite){(double)x + 0.5, (double)y + 0.5, 0, 2 + map[x][y] - '0'};
				map[x][y] = '0';
			}
	}
	vars->sprites = array;
	return (SUCCESS_CODE);
}
