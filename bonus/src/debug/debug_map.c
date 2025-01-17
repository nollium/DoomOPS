/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 15:18:36 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/27 15:28:29 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_map(char **array)
{
	int len;

	len = -1;
	if (!array)
		ft_putendl_fd("(NULL)", 2);
	while (array && array[++len])
		ft_putendl_fd(array[len], 2);
}
