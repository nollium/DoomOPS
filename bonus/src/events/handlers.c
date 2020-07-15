/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 13:45:37 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/15 15:58:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "garbage_collection.h"

int		key_handler(int keycode, t_vars *vars)
{
	int i;

	if (keycode == ESC_KEY)
	{
		free_vars(vars);
		exit(0);
	}
	i = -1;
	while (i < K_BUFF_SIZE && (((vars->keys)[i]).keycode != -1))
		i++;
	if (((vars->keys)[i]).keycode != -1)
		return (0);
	((vars->keys)[i]).keycode = keycode;
	while (++i < K_BUFF_SIZE)
		if (((vars->keys)[i]).keycode == keycode)
			((vars->keys)[i]).keycode = -1;
	return (0);
}

int		release_handler(int keycode, t_vars *vars)
{
	int				i;

	i = -1;
	while (++i < K_BUFF_SIZE)
	{
		if ((vars->keys[i]).keycode == keycode)
		{
			if (i >= K_BUFF_SIZE)
				return (0);
			((vars->keys)[i]).keycode = -1;
			((vars->keys)[i]).time = 0;
		}
	}
	return (0);
}

t_keys	*key_chr(t_keys *arr, int keycode, size_t size)
{
	size_t	i;

	i = -1;
	while (++i < size)
		if (arr[i].keycode == keycode)
			return (arr + i);
	return (NULL);
}
