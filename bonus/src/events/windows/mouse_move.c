/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirty <dirty@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 20:08:48 by user42            #+#    #+#             */
/*   Updated: 2020/07/22 02:02:18 by dirty            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int		my_mouse_get_pos(void *mlx, void *win, int *x, int *y)
{
	return (mlx_mouse_get_pos(mlx, win, x, y));
}

int		my_mouse_move(void *mlx, void *win, int x, int y)
{
	return (mlx_mouse_move(mlx, win, x, y));
}
