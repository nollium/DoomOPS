/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 14:24:16 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/16 18:47:40 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int format_map_line(char *line)
{
	int error;
	int i;

	i = -1;
	error = SUCCESS_CODE;
	printf("\e[31m%p: %s\e[0m\n", line, line);
	if (!line || !*line)
		return ((line) ? 0 : 1);
	while (line[++i])
	{
		if (ft_isspace(line[i]))
			line[i] = '0';
		if (!ft_strchr(VALID_MAP_CHARS, line[i]))
			return (MAP_ERROR);
	}
	printf("\e[32m%p: %s\e[0m\n", line, line);
	return (error);
}



char **parse_array(t_list *lst, int len)
{
	char **array;
	int error;

	error = 0;
	if (lst && (array = malloc(sizeof(char *) * (len + 1))))
	{
		len = 1;
		while (lst->next && !ft_isdigit(*(char *)lst->content)
						 && !ft_isspace(*(char *)lst->content))
			lst = lst->next;
		array[0] = lst->content;
		error |= format_map_line(array[0]);
		while ((lst = lst->next) && !(error |= format_map_line(lst->content)))
			array[len++] = lst->content;
		array[len] = NULL;
	}
	else
		array = NULL;
	ft_lstclear(&lst, NULL);
	if (error)
	{
		free(array);
		return (NULL);
	}
	len = -1;
	while (DEBUG_MODE && array && array[++len]) // print map
		ft_putendl_fd(array[len], 2);
	return (array);
}

int parse_resolution(char *line, t_screen *screen)
{
	char **split __attribute__((cleanup(free_split)));
	int i;
	int j;

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


static int  check_color(char *line)
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

int parse_color(char *line)
{
	char    		**split __attribute__((cleanup(free_split)));
	int    			i;
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