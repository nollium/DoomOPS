/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 14:49:50 by smaccary          #+#    #+#             */
/*   Updated: 2019/12/10 21:27:59 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include "../libftprintf.h"

static long long	is_newline(char *str)
{
	size_t i;

	i = 0;
	if (!str)
		return (-1);
	if (str[0] == '\n')
		return (0);
	while (str[i] != '\n')
	{
		if (!str[i])
			return (-2);
		if (str[i] == -1)
			return (-1);
		i++;
	}
	return (i);
}

static int			readline(char **ptr_rest, char **line, int fd)
{
	char		*buff;
	long long	red;
	char		*tmp;

	red = (size_t)BUFFER_SIZE;
	while (is_newline(*ptr_rest) < 0 && (red == (size_t)BUFFER_SIZE))
	{
		if (!(buff = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1))))
			return (0);
		if ((red = read(fd, buff, (size_t)BUFFER_SIZE)) == -1)
			return ((*line = NULL) ? 0 : 0);
		buff[red] = '\0';
		tmp = (char *)ft_strjoin(*ptr_rest, buff);
		free(buff);
		free(*ptr_rest);
		*ptr_rest = tmp;
	}
	return ((*ptr_rest) ? 1 : 0);
}

static	char		**get_rest(int fd, t_gnllist **storage)
{
	t_gnllist	*prev;

	prev = NULL;
	while (*storage && (*storage)->fd != fd)
	{
		prev = *storage;
		*storage = (*storage)->next;
	}
	if (*storage)
		return (&((*storage)->rest));
	if (!(*storage = malloc(sizeof(t_gnllist))))
		return (NULL);
	(*storage)->next = NULL;
	(*storage)->fd = fd;
	(*storage)->rest = NULL;
	if (prev)
		prev->next = *storage;
	return (&((*storage)->rest));
}

static	void		del_rest(int fd, t_gnllist **storage)
{
	t_gnllist	*prev;

	if (!*storage)
		return ;
	if (fd == (*storage)->fd)
	{
		free((*storage)->rest);
		prev = (*storage)->next;
		free(*storage);
		*storage = prev;
		return ;
	}
	while ((*storage)->fd != fd)
	{
		prev = *storage;
		storage = &(*storage)->next;
	}
	prev->next = (*storage)->next;
	free((*storage)->rest);
	free(*storage);
	*storage = NULL;
	return ;
}

int					get_next_line(int fd, char **line)
{
	char				**rest;
	char				*tmp;
	static t_gnllist	*storage = NULL;

	if (!line || BUFFER_SIZE <= 0)
		return (-1);
	rest = get_rest(fd, &storage);
	*rest = (*rest) ? *rest : ft_strdup("");
	if (!line || readline(rest, line, fd) != 1)
		return (-1);
	if (is_newline(*rest) >= 0)
	{
		if (!(*line = ft_strndup(*rest, is_newline(*rest))))
			return (-1);
		tmp = ft_strdup(*rest + is_newline(*rest) + 1);
		free(*rest);
		return ((*rest = tmp) ? 1 : 1);
	}
	*line = ft_strdup(*rest);
	del_rest(fd, &storage);
	return ((line) ? 0 : -1);
}
