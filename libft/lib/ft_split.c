/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 11:02:31 by smaccary          #+#    #+#             */
/*   Updated: 2019/11/16 18:35:40 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libftprintf.h"

static	int		ft_word_count(const char *s, char c)
{
	int	count;
	int i;

	count = 1;
	i = 0;
	if (s[0] == c || !s[0])
		count = 0;
	while (s[0] && s[++i])
		if (s[i - 1] == c && s[i] != c)
			count++;
	return (count);
}

static	int		ft_word_size(const char *str, char c)
{
	int size;

	size = 0;
	while (str[size] && str[size] != c)
		size++;
	return (size);
}

static	int		free_tab(char **tab, int n)
{
	while (n--)
		free(tab[n]);
	free(tab);
	return (0);
}

static	int		real_split(char *s, char **tab, char c)
{
	int	wc;
	int	i;
	int	j;
	int size;

	wc = ft_word_count(s, c);
	i = -1;
	while (++i < wc)
	{
		j = 0;
		while (*s == c)
			s++;
		size = ft_word_size(&s[j], c);
		if (!(tab[i] = malloc(sizeof(char) * (size + 1))))
			return (free_tab(tab, i));
		while (j < size)
			tab[i][j++] = *s++;
		tab[i][j] = '\0';
	}
	return (1);
}

char			**ft_split(char const *s, char c)
{
	char	**tab;
	int		wcount;

	if (!s)
		return (NULL);
	if (!s[0])
	{
		tab = malloc(sizeof(char *));
		tab[0] = NULL;
		return (tab);
	}
	wcount = ft_word_count(s, c);
	if (!(tab = malloc(sizeof(char *) * (wcount + 1))))
		return (NULL);
	tab[wcount] = NULL;
	real_split((char *)s, tab, c);
	return (tab);
}
