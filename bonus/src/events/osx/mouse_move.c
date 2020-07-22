/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirty <dirty@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 20:09:46 by user42            #+#    #+#             */
/*   Updated: 2020/07/22 02:06:41 by dirty            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int		my_mouse_get_pos(void *mlx, void *win, int *x, int *y)
{
	(void)mlx;
	return (mlx_mouse_get_pos(win, x, y));
}

int		my_mouse_move(void *mlx, void *win, int x, int y)
{
	(void)mlx;
	return (mlx_mouse_move(win, x, y));
}
