/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 14:24:16 by smaccary          #+#    #+#             */
/*   Updated: 2020/08/03 19:30:31 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	get_parsed_res(char **split, t_screen *screen)
{
	int		i;
	int		j;

	i = -1;
	while (split[++i])
	{
		if (i > 1)
			return (RESOLUTION_ERROR);
		j = -1;
		while (split[i][++j])
		{
			if (!ft_isdigit(split[i][j]))
				return (RESOLUTION_ERROR);
			if (j > 9 || (j == 9 && split[i][0] > 2))
			{
				screen->width = INT_MAX;
				screen->height = INT_MAX;
				return (SUCCESS_CODE);
			}
		}
	}
	screen->width = ft_atoi(split[0]);
	screen->height = ft_atoi(split[1]);
	return (SUCCESS_CODE);
}

int			parse_resolution(char *line, t_screen *screen)
{
	char	**split __attribute__((cleanup(free_split)));

	if (!(split = ft_split(line, ' ')))
		return (MALLOC_ERROR);
	if (get_parsed_res(split, screen) != SUCCESS_CODE)
		return (RESOLUTION_ERROR);
	if (screen->width <= 0 || screen->height <= 0)
		return (RESOLUTION_ERROR);
	return (SUCCESS_CODE);
}

static int	check_color(char *line, unsigned char *dst)
{
	int		i;
	char	*trimmed __attribute__((cleanup(free_str)));
	int		nbr;

	i = -1;
	if (!line || !(trimmed = ft_strtrim(line, WHITESPACES)))
		return (MALLOC_ERROR);
	if (!*line)
		return (COLOR_ERROR);
	while (trimmed[++i])
		if (i > 3 || !ft_isdigit(trimmed[i]))
			return (COLOR_ERROR);
	nbr = ft_atoi(trimmed);
	if (nbr < 0 || nbr > 255)
		return (COLOR_ERROR);
	*dst = (unsigned char)nbr;
	return (SUCCESS_CODE);
}

static int	count_char(char *str, char c)
{
	int i;
	int	count;

	i = -1;
	count = 0;
	if (!str)
		return (-1);
	while (str[++i])
		if (str[i] == c)
			count++;
	return (count);
}

int			parse_color(char *line)
{
	char			**split __attribute__((cleanup(free_split)));
	int				i;
	int				error;
	unsigned char	rgb[3];

	split = NULL;
	if (count_char(line, ',') != 2)
		return (COLOR_ERROR);
	if (!(split = ft_split(line, ',')))
		return (MALLOC_ERROR);
	i = -1;
	while (split[++i])
	{
		if (i > 2)
			return (COLOR_ERROR);
		if ((error = check_color(split[i], rgb + i)) != SUCCESS_CODE)
			return (error);
	}
	if (i != 3)
		return (COLOR_ERROR);
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}
