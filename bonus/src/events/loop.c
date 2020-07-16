/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 13:37:22 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/16 19:54:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "mlx_int.h"
#include "parsing.h"
#include "sprites.h"

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
	static char *str[] = {"cub3D", "maps/map.cub"};

	if (!(vars->frame_ready))
	{
		vars->redraw |= keyboard_handler(vars);
		vars->redraw = 1;
		get_n(&(vars->num_sprites));
		ennemies_handler(vars->sprites, &(vars->cam), vars->map.array);
		pickup_handler(&(vars->sprites), &(vars->cam), &(vars->num_sprites));
		sort_sprites(&(vars->cam), vars->sprites, vars->num_sprites);
		if (vars->cam.hp < 0)
		{
			free_vars(vars);
			main(2, str);
			exit(0);
		}
		redraw(vars);
	}
	if (vars->redraw)
		refresh(vars);
	return (0);
}
