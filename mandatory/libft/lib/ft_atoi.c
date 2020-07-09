/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 20:59:54 by smaccary          #+#    #+#             */
/*   Updated: 2019/11/17 16:46:21 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static	int	ft_numerical_strlen(char *str)
{
	int i;

	i = 0;
	while (('0' <= str[i] && str[i] <= '9') && str[i])
		i++;
	return (i);
}

int			ft_atoi(const char *str)
{
	int i;
	int sign;
	int number;
	int j;

	number = 0;
	i = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == ' ')
		i++;
	sign = (str[i] == '-') ? -1 : 1;
	i = (str[i] == '-' || str[i] == '+') ? i + 1 : i;
	j = ft_numerical_strlen((char *)&str[i]);
	while (j)
	{
		number = number * 10 + (str[i] - 48);
		i++;
		j--;
	}
	return (number * sign);
}
