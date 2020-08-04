/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:30:19 by smaccary          #+#    #+#             */
/*   Updated: 2020/08/04 18:30:19 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "events.h"

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
			if ('2' <= map[x][y] && map[x][y] <= '4')
				(*size)++;
	}
	return (ft_calloc(1 + *size, sizeof(t_sprite)));
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
			if ('2' <= map[x][y] && map[x][y] <= '4')
			{
				array[i++] = (t_sprite){(double)x + 0.5, (double)y + 0.5,
				0, 2 + map[x][y] - '0', .hp = EN_HEALTH};
				map[x][y] = VOID;
			}
	}
	vars->sprites = array;
	vars->sprite_ptr = array;
	return (SUCCESS_CODE);
}
