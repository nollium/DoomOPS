/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 20:08:48 by user42            #+#    #+#             */
/*   Updated: 2020/08/04 17:02:28 by smaccary         ###   ########.fr       */
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
