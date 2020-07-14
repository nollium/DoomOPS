/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirty <dirty@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 13:37:22 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/14 23:41:14 by dirty            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "mlx_int.h"
#include "parsing.h"

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
	mlx_hook(vars->win, BUTTON_PRESS, BUTTONPRESS_MASK,
			mouse_press_handler, (void *)vars);
	mlx_hook(vars->win, BUTTON_RELEASE, BUTTONRELEASE_MASK,
			mouse_release_handler, (void *)vars);
	mlx_hook(vars->win, FOCUS_IN, FOCUS_CHANGE_MASK, focus_in_handler, vars);
	mlx_hook(vars->win, FOCUS_OUT, FOCUS_CHANGE_MASK, focus_out_handler, vars);
	mlx_loop_hook(vars->mlx, loop_handler, (void *)vars);
}

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
		i *= 0.25;
		if (i < 0)
			while (i++ <= 0)
				turn_left(vars);
		else if (i > 0)
			while (i-- >= 0)
				turn_right(vars);
	}
	if (win_x != vars->game_screen.width / 2
	|| win_y != vars->game_screen.height / 2)
		mlx_mouse_move(vars->mlx, vars->win,
		vars->game_screen.width / 2, vars->game_screen.height / 2);
	return (1);
}

int		refresh(t_vars *vars)
{
	static clock_t	t0 = 0;
	static int		img = 0;

	if (clock() - t0 < CLOCKS_PER_SEC / FRAME_CAP || !(vars->frame_ready))
		return (0);
	t0 = clock();
	mlx_put_image_to_window(vars->mlx, vars->win, (vars->img)->img, 0, 0);
	vars->img = vars->img2 + img;
	img = (img) ? 0 : 1;
	vars->redraw = 0;
	vars->frame_ready = 0;
	return (1);
}

int		loop_handler(t_vars *vars)
{
	static char *str[] = {"cub3D", "maps/map.cub"};

	if (!(vars->frame_ready))
	{
		vars->redraw |= keyboard_handler(vars);
		vars->redraw = 1;
		ennemies_handler(vars->sprites, &(vars->cam), vars->map.array,
							vars->num_sprites);
		if (vars->cam.hp < 0)
		{
			free_vars(vars);
			main(2, str);
			exit(0);
		}
		draw_scene(vars);
		if (vars->draw_shot)
			draw_text(&(vars->flash), vars->img, vars->flash.x, vars->flash.y);
		draw_text(&(vars->gun), vars->img, vars->gun.x, vars->gun.y);
		draw_text(vars->health_bars + vars->cam.hp, vars->img, 0, 0);
		vars->frame_ready = 1;
	}
	if (vars->redraw)
		refresh(vars);
	return (0);
}
