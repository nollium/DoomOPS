/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirty <dirty@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 13:37:22 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/11 21:18:10 by dirty            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "mlx_int.h"

int		focus_in_handler(t_vars *vars)
{
	vars->redraw = 1;
	vars->win_focus = 1;
	return (0);
}

int		focus_out_handler(t_vars *vars)
{
	vars->win_focus = 0;
	return (0);
}

void	hooks(t_vars *vars)
{
	mlx_mouse_hide(vars->mlx, vars->win);
	mlx_hook(vars->win, KEY_PRESS, KEYPRESS_MASK, key_handler, (void *)vars);
	mlx_hook(vars->win, KEY_RELEASE, KEYRELEASE_MASK, release_handler,
			(void *)vars);
	mlx_hook(vars->win, FOCUS_IN, FOCUS_CHANGE_MASK, focus_in_handler, (void *)vars);
	mlx_hook(vars->win, FOCUS_OUT, FOCUS_CHANGE_MASK, focus_out_handler, (void *)vars);
	mlx_loop_hook(vars->mlx, loop_handler, (void *)vars);
}

int		mouse_move_handler(t_vars *vars)
{
	int	win_x;
	int	win_y;
	int	returned;
	int	i;
	
	returned = mlx_mouse_get_pos(vars->mlx, vars->win, &win_x, &win_y);
	if (((i = win_x - vars->game_screen.width / 2)) != 0)
	{
		i *= 0.25;
		if (i < 0)
			while (i++ <= 0)
				turn_left(vars);
		else if (i > 0)
			while (i-- >= 0)
				turn_right(vars);
	}
	if (vars->win_focus && (win_x != vars->game_screen.width / 2
	|| win_y != vars->game_screen.height / 2)) 
		mlx_mouse_move(vars->mlx, vars->win,
		vars->game_screen.height / 2, vars->game_screen.width / 2);
	else
		return (0);
	return (1);
}

int		loop_handler(t_vars *vars)
{
	static int	img = 0;
	int			i;

	i = -1;
	vars->redraw |= keyboard_handler(vars);
	while (++i < vars->num_sprites)
		vars->redraw |= vars->sprites[i].seen;
	if (vars->redraw)
	{
		draw_scene(vars);
		mlx_put_image_to_window(vars->mlx, vars->win, (vars->img)->img, 0, 0);
		vars->img = vars->img2 + img;
		img = (img) ? 0 : 1;
		vars->redraw = 0;
	}
	return (0);
}
