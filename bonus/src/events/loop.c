/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 13:37:22 by smaccary          #+#    #+#             */
/*   Updated: 2020/08/03 19:09:13 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "parsing.h"
#include "sprites.h"

void	hooks(t_vars *vars)
{
	mlx_mouse_hide(vars->mlx, vars->win);
	my_mouse_move(vars->mlx, vars->win, vars->game_screen.width / 2,
	(LINUX) ? vars->game_screen.height / 2 : 0);
	mlx_hook(vars->win, KEY_PRESS, KEYPRESS_MASK, key_handler, (void *)vars);
	mlx_hook(vars->win, KEY_RELEASE, KEYRELEASE_MASK, release_handler,
			(void *)vars);
	mlx_hook(vars->win, BUTTON_PRESS, BUTTONPRESS_MASK,
			mouse_press_handler, (void *)vars);
	mlx_hook(vars->win, BUTTON_RELEASE, BUTTONRELEASE_MASK,
			mouse_release_handler, (void *)vars);
	mlx_hook(vars->win, FOCUS_IN, FOCUS_CHANGE_MASK, focus_in_handler, vars);
	mlx_hook(vars->win, FOCUS_OUT, FOCUS_CHANGE_MASK, focus_out_handler, vars);
	mlx_hook(vars->win, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, leave, vars);
	mlx_expose_hook(vars->win, focus_in_handler, vars);
	mlx_loop_hook(vars->mlx, loop_handler, (void *)vars);
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

int		pickup_handler(t_sprite **sprites, t_camera *cam, int *n)
{
	int	i;

	if (cam->hp < 5
		&& (i = sprite_collision(*sprites, cam->x, cam->y, PICKUP_TEX)))
	{
		system("(" PLAYER " " DRINK_SOUND BACKGROUND ") " OPTIONS);
		cam->hp++;
		swap_sprites(*sprites, *sprites + i - 1);
		(*n)--;
		(*sprites)++;
		return (1);
	}
	return (0);
}

void	redraw(t_vars *vars)
{
	draw_scene(vars);
	if (vars->draw_shot)
		draw_text(&(vars->flash), vars->img, vars->flash.x, vars->flash.y);
	draw_text(&(vars->gun), vars->img, vars->gun.x, vars->gun.y);
	draw_text(vars->health_bars + vars->cam.hp, vars->img,
	vars->game_screen.width / 2 - vars->health_bars->width / 2, 0);
	vars->frame_ready = 1;
}

int		loop_handler(t_vars *vars)
{
	mlx_mouse_hide(vars->mlx, vars->win);
	if (!(vars->frame_ready))
	{
		vars->redraw |= keyboard_handler(vars);
		get_n(&(vars->num_sprites));
		ennemies_handler(vars->sprites, &(vars->cam), vars->map.array);
		pickup_handler(&(vars->sprites), &(vars->cam), &(vars->num_sprites));
		sort_sprites(&(vars->cam), vars->sprites, vars->num_sprites);
		if (vars->cam.hp < 0)
		{
			free_vars(vars);
			exit(0);
		}
		if (vars->redraw)
			redraw(vars);
	}
	if (vars->frame_ready)
		refresh(vars);
	return (0);
}
