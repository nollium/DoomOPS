/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 13:37:22 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/09 00:13:57 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		ennemies_handler(t_vars *vars, t_sprite *sprites)
{
	static int left = 1;
	
	if (sprites[1].x > 6)
    {
		left = 0;
        sprites[1].tex_num = 5;
    }
	else if (sprites[1].x < 2.0)
    {
		left = 1;
        sprites[1].tex_num = 4;
    }	
    if (left)
		sprites[1].x += 0.1;
	else
		sprites[1].x -= 0.1;
	return (0);
}

int		loop_handler(t_vars *vars)
{
	clock_t	t0;
	static int img = 0;
// 4.0 10.0
	vars->redraw |= keyboard_handler(vars);
	//vars->redraw |= ennemies_handler(vars, vars->sprites);
	vars->redraw |= vars->seen_sprite;
	if (vars->redraw || 1)
	{
		draw_scene(vars);
	//	draw_text(&(vars->text[7]), vars->img, 0, 0);
		mlx_put_image_to_window(vars->mlx, vars->win, (vars->img)->img, 0, 0);
		vars->img = vars->img2 + img;
		img = (img) ? 0 : 1;
		if (DEBUG_MODE)
			printf("DRAWING : x%Lf y%Lf\ndir_x:%Lf dir_y:%Lf\n", vars->cam.x, vars->cam.y, vars->cam.dir_x, vars->cam.dir_y);
		//t0 = clock();
		//while (clock() - t0 < CLOCKS_PER_SEC / 120);
		vars->redraw = 0;
	}
	return (0);
}