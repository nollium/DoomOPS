/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 14:24:16 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/27 16:31:04 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int			parse_resolution(char *line, t_screen *screen)
{
	char	**split __attribute__((cleanup(free_split)));
	int		i;
	int		j;

	if (!(split = ft_split(line, ' ')))
		return (MALLOC_ERROR);
	i = -1;
	while (split[++i])
	{
		if (i > 1)
			return (RESOLUTION_ERROR);
		j = -1;
		while (split[i][++j])
			if (!ft_isdigit(split[i][j]) && !ft_isspace(split[i][j]))
				return (RESOLUTION_ERROR);
	}
	screen->width = ft_atoi(split[0]);
	screen->height = ft_atoi(split[1]);
	if (screen->width <= 0 || screen->height <= 0)
		return (RESOLUTION_ERROR);
	return (SUCCESS_CODE);
}

static int	check_color(char *line)
{
	int		i;
	char	*trimmed __attribute__((cleanup(free_str)));

	i = -1;
	if (!line || !(trimmed = ft_strtrim(line, WHITESPACES)))
		return (MALLOC_ERROR);
	if (!*line)
		return (COLOR_ERROR);
	while (trimmed[++i])
		if (i > 3 || !ft_isdigit(trimmed[i]))
			return (COLOR_ERROR);
	return (SUCCESS_CODE);
}

int			parse_color(char *line)
{
	char			**split __attribute__((cleanup(free_split)));
	int				i;
	int				error;
	unsigned char	rgb[3];

	if (!(split = ft_split(line, ',')))
		return (MALLOC_ERROR);
	i = -1;
	while (split[++i])
	{
		if (i > 2)
			return (COLOR_ERROR);
		if ((error = check_color(split[i])) != SUCCESS_CODE)
			return (error);
		if ((rgb[i] = ft_atoi(split[i])) < 0)
			return (COLOR_ERROR);
	}
	if (i != 3)
		return (COLOR_ERROR);
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}
