/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 22:08:40 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/18 16:24:37 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collection.h"

void	free_str(char **str)
{
	free(*str);
    *str = NULL;
}

void    free_split(char ***split)
{
    char **array;

    array = *split - 1;
    while (*(++array))
    {
        free(*array);
        *array = NULL;
    }
    free(*split);
    *split = NULL;
}