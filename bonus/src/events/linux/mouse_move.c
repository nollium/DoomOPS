/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linux.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 20:08:48 by user42            #+#    #+#             */
/*   Updated: 2020/07/20 20:09:04 by user42           ###   ########.fr       */
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
	returned = mlx_mouse_get_pos(vars->mlx, vars->win, &win_x, &win_y);
	if (((i = (double)win_x - (double)vars->game_screen.width / 2.0)) != 0.0)
	{
		turn_right(vars, i * 2.0 / vars->game_screen.width);
		mlx_mouse_move(vars->mlx, vars->win,
		vars->game_screen.width / 2, vars->game_screen.height / 2);
	}
	return (1);
}
