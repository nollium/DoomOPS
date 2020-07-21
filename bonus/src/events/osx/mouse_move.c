/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 20:09:46 by user42            #+#    #+#             */
/*   Updated: 2020/07/21 22:56:21 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int		mouse_move_handler(t_vars *vars)
{
	int		win_x;
	int		win_y;
	int		returned;
	double	i;

	if (!vars->win_focus)
		return (0);
	mlx_mouse_hide(vars->mlx, vars->win);
	returned = mlx_mouse_get_pos(vars->win, &win_x, &win_y);
	if (((i = (double)win_x - vars->game_screen.width / 2)
			!= vars->game_screen.width / 2))
	{
		turn_right(vars, i / vars->game_screen.width);
		mlx_mouse_move(vars->win, vars->game_screen.width / 2, 0);
	}
	return (1);
}
