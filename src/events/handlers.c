/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 13:45:37 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/27 19:10:40 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "garbage_collection.h"

int		key_handler(int keycode, t_vars *vars)
{
	int i;

	i = -1;
	if (keycode == 65307)
		free_vars(vars);
	i = -1;
	while (i < K_BUFF_SIZE && (((vars->keys)[i]).keycode != -1))
		i++;
	if (((vars->keys)[i]).keycode != -1)
		return (0);
	((vars->keys)[i]).keycode = keycode;
	return (0);
}

int		enter_handler(void)
{
	if (DEBUG_MODE)
		ft_printf("Entering window\n");
	return (0);
}

int		leave_handler(void)
{
	if (DEBUG_MODE)
		ft_printf("Leaving window\n");
	return (0);
}

int		release_handler(int keycode, t_vars *vars)
{
	int				i;
	time_t			elapsed;

	i = -1;
	while (++i < K_BUFF_SIZE)
	{
		if ((vars->keys[i]).keycode == keycode)
		{
			if (i >= K_BUFF_SIZE)
				return (0);
			elapsed = (time(NULL) - ((vars->keys)[i]).time);
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
