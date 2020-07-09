/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:35:33 by smaccary          #+#    #+#             */
/*   Updated: 2019/12/11 01:15:53 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"
#include <stdlib.h>

static	char	*local_copy(char *num, int index)
{
	char	*dst;
	int		i;

	i = 0;
	if (!(dst = malloc(ft_strlen(&num[index + 1]) + 1)))
		return (NULL);
	while (num[++index])
	{
		dst[i] = num[index];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static	char	*transform(long long nb)
{
	int				index;
	long	long	n_bis;
	char			num[11];

	n_bis = nb;
	index = 9;
	num[10] = '\0';
	if (nb < 0)
		nb *= -1;
	while (nb > 0)
	{
		num[index] = nb % 10 + 48;
		nb /= 10;
		index--;
	}
	if (n_bis < 0)
		num[index--] = '-';
	return (local_copy(num, index));
}

char			*ft_itoa(int n)
{
	long long nb;

	nb = (long long)n;
	if (nb == 0)
		return (ft_strdup("0"));
	if (nb == 2147483647)
		return (ft_strdup("2147483647"));
	else if (nb == -2147483648)
		return (ft_strdup("-2147483648"));
	return (transform(n));
}
