/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 19:34:07 by user42            #+#    #+#             */
/*   Updated: 2020/07/20 19:42:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	format_map_line(char *line)
{
	int error;
	int i;

	i = -1;
	error = SUCCESS_CODE;
	if (!line || !*line)
		return ((line) ? SUCCESS_CODE : MAP_ERROR);
	while (line[++i])
	{
		if (ft_isspace(line[i]))
			line[i] = WALL;
		if (line[0] != WALL || !ft_strchr(VALID_MAP_CHARS, line[i]))
			return (MAP_ERROR);
	}
	if (!i || line[i - 1] != WALL)
		return (MAP_ERROR);
	return (error);
}

char		**parse_array(t_list *lst, int len)
{
	char	**array;
	int		error;

	error = 0;
	if (lst && (array = malloc(sizeof(char *) * (len + 1))))
	{
		len = 1;
		while ((lst->next && (!ft_isdigit(*(char *)lst->content)
			&& !ft_isspace(*(char *)lst->content))) || !*(char *)lst->content)
			lst = lst->next;
		array[0] = ft_strdup(lst->content);
		error |= format_map_line(array[0]);
		while ((lst = lst->next) && *(char *)lst->content
				&& !(error |= format_map_line(lst->content)))
			array[len++] = ft_strdup(lst->content);
		array[len] = NULL;
	}
	else
		array = NULL;
	if (error || len <= 2)
	{
		free_split(&array);
		return (NULL);
	}
	return (array);
}

int			find_spawn(char **map, t_spawn *spawn)
{
	char	*spawn_ptr;
	char	*last_ptr;
	int		x;
	int		y;

	y = -1;
	x = -1;
	*spawn = (t_spawn){-1, -1, 0};
	while (map && map[++x])
	{
		if ((spawn_ptr = ft_setchr(map[x], SPAWN_CHARS))
						!= (last_ptr = ft_setrchr(map[x], SPAWN_CHARS)))
			return (MAP_ERROR);
		else if (spawn_ptr)
		{
			if (spawn->x != -1 && spawn->y != -1)
				return (MAP_ERROR);
			*spawn = (t_spawn){.x = x + 0.5, .y = spawn_ptr - map[x] + 0.5,
								.dir = map[x][spawn_ptr - map[x]]};
			map[(int)(spawn->x - 0.5)][(int)(spawn->y - 0.5)] = VOID;
		}
	}
	if (spawn->x <= 0 || spawn->y <= 0 || !ft_strchr(SPAWN_CHARS, spawn->dir))
		return (MAP_ERROR);
	return (SUCCESS_CODE);
}

int			check_borders(char **map)
{
	int	y;
	int	x;

	y = -1;
	if (!map)
		return (MAP_ERROR);
	while (map[++y])
	{
		x = -1;
		if ((map[y][0] != WALL)
			|| map[y][ft_strlen(map[y]) - 1] != WALL)
			return (MAP_ERROR);
		while (y > 0 && map[y][++x] && map[y + 1])
			if (map[y][x] == VOID && (x >= (int)ft_strlen(map[y - 1])
									|| x >= (int)ft_strlen(map[y + 1])))
				return (MAP_ERROR);
	}
	if (ft_setchr(map[0], VOID_CHARS) || y <= 0
		|| ft_setchr(map[y - 1], VOID_CHARS))
		return (MAP_ERROR);
	return (SUCCESS_CODE);
}
