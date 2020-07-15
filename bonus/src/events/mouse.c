/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 15:57:06 by user42            #+#    #+#             */
/*   Updated: 2020/07/15 15:59:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int		mouse_move_handler(t_vars *vars)
{
	int	win_x;
	int	win_y;
	int	returned;
	int	i;
	
	if (!vars->win_focus)
		return (0);
	returned = mlx_mouse_get_pos(vars->mlx, vars->win, &win_x, &win_y);
	if (((i = win_x - vars->game_screen.width / 2)) != 0)
	{
		if (i < 0)
			while (i++ <= 0)
				turn_left(vars, 0.0003);
		else if (i > 0)
			while (i-- >= 0)
				turn_right(vars, 0.0003);
	}
	if (win_x != vars->game_screen.width / 2
	|| win_y != vars->game_screen.height / 2)
		mlx_mouse_move(vars->mlx, vars->win,
		vars->game_screen.width / 2, vars->game_screen.height / 2);
	return (1);
}

int		mouse_press_handler(int keycode, int x, int y, t_vars *vars)
{
	(void)(x && y);
	return (key_handler(keycode, vars));
}

int		mouse_release_handler(int keycode, int x, int y, t_vars *vars)
{
	(void)(x && y);
	return (release_handler(keycode, vars));
}

int				click_handler(t_vars *vars)
{
	static clock_t	last_shot = 0;
	double			elapsed;
	static int		released = 1;
	
	elapsed = (double)(clock() - last_shot) / (double)CLOCKS_PER_SEC;
	if (!released && !key_chr(vars->keys, LEFT_CLICK, K_BUFF_SIZE))
		released = 1;
	if (key_chr(vars->keys, LEFT_CLICK, K_BUFF_SIZE)
		&& elapsed > (double)SHOT_DURATION && released)
	{
		released = 0;
		if (elapsed > (double)SHOT_DURATION + (double)SHOT_COOLDOWN)
		{
			last_shot = clock();
			vars->draw_shot = 1;
			system("(" PLAYER " " GUNSHOT_PATH BACKGROUND ") "  OPTIONS);
			shoot_sprites(&(vars->sprites), &(vars->num_sprites));
			return (1);
		}
	}
	if (elapsed > (double)SHOT_DURATION && vars->draw_shot)
	{
		vars->draw_shot = 0;
		return (1);
	}
	return (0);
}
