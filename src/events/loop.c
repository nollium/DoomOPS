/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 13:37:22 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/18 16:24:52 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

void 	hooks(t_vars *vars)
{
	mlx_hook(vars->win, KeyPress, KeyPressMask, key_handler, (void *)vars);
	mlx_mouse_hook(vars->win, mouse_handler, vars);
	mlx_hook(vars->win, ResizeRequest, 1, resize_handler, (void *)0);
	mlx_hook(vars->win, EnterNotify, EnterWindowMask, enter_handler, NULL);
	mlx_hook(vars->win, LeaveNotify, LeaveWindowMask, leave_handler, NULL);
	mlx_hook(vars->win, KeyRelease, KeyReleaseMask, release_handler, (void *)vars);
	mlx_loop_hook(vars->mlx, loop_handler, (void *)vars);
}

int		ennemies_handler(t_vars *vars, t_sprite *sprites)
{
	static int left = 1;
	
	if (sprites[0].x > 6)
		left = 0;
	else if (sprites[0].x < 2.0)
		left = 1;
    if (left)
		sprites[0].x += SPEED;
	else
		sprites[0].x -= SPEED;
	return (0);
}

int		loop_handler(t_vars *vars)
{
	clock_t	t0;
	static int img = 0;
	int i = -1;
// 4.0 10.0
	vars->redraw |= keyboard_handler(vars);
	vars->redraw |= ennemies_handler(vars, vars->sprites);
	while (++i < vars->num_sprites)
		vars->redraw |= vars->sprites[i].seen;
	if (vars->redraw)
	{
		draw_scene(vars);
	//	draw_text(&(vars->text[7]), vars->img, 0, 0);
		mlx_put_image_to_window(vars->mlx, vars->win, (vars->img)->img, 0, 0);
		vars->img = vars->img2 + img;
		img = (img) ? 0 : 1;
		if (DEBUG_MODE)
			printf("DRAWING : x%Lf y%Lf\ndir_x:%Lf dir_y:%Lf\n", vars->cam.x, vars->cam.y, vars->cam.dir_x, vars->cam.dir_y);
		/*t0 = clock();
		while (clock() - t0 < CLOCKS_PER_SEC / 70);*/
		vars->redraw = 0;
	}
	return (0);
}