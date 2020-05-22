/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 12:50:24 by slutymeme         #+#    #+#             */
/*   Updated: 2020/05/22 17:42:24 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	get_color(t_drawer *draw, t_texture *tex)
{
	 // How much to increase the texture coordinate per screen pixel
    double step = 1.0 * TEX_HEIGHT / draw->line_height;
      // Starting texture coordinate
    double texPos = (draw->start - WINDOW_HEIGHT / 2 + draw->line_height / 2) * step;
	// Cast the texture coordinate to integer, and mask with (TEX_HEIGHT - 1) in case of overflow
	tex->y = (int)texPos & (TEX_HEIGHT - 1);
	texPos += step;
	draw->color = tex->array[TEX_HEIGHT * tex->y + tex->x];
	//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
	if (draw->side == 1)
		draw->color = (draw->color >> 1) & 8355711;
	draw->color = rgb_to_trgb(0, draw->color);
}

void		draw_col(t_vars *vars, t_drawer *draw)
{
    draw->start = -(draw->line_height) / 2 + WINDOW_HEIGHT / 2;
	draw->start = (draw->start < 0) ? 0 : draw->start;
	draw->end = (draw->line_height) / 2 + WINDOW_HEIGHT / 2;
	draw->end = (draw->end >= WINDOW_HEIGHT) ? WINDOW_HEIGHT - 1 : draw->end;
	draw->color = ROOF_COLOR;
	draw->y = -1;
	while (++draw->y < WINDOW_HEIGHT)
	{
		if (draw->start <= draw->y && draw->y <= draw->end)
		{
			get_color(draw, &(vars->text));
			if (SHADOW_MODE)	
				draw->color = add_shade(((double)draw->dist / MAP_HEIGHT * 2), draw->color);
		}
		if (draw->y > draw->end)
		{
			draw->color = FLOOR_COLOR;
			if (SHADOW_MODE)
				draw->color = add_shade(1.05 / ((double)draw->y * 2.15 / (double)((WINDOW_WIDTH))) , draw->color);
		}
		mlx_pixel_put(vars->mlx, vars->win, draw->x, draw->y, draw->color);
	}
}

void		draw_scene(t_vars *vars)
{
	t_ray		ray;
	t_drawer	draw;

	draw.x = -1;
	while (++(draw.x) < WINDOW_WIDTH)
	{
		raycast(&ray, vars, draw.x);
		draw = (t_drawer){-(draw.line_height) / 2 + WINDOW_HEIGHT / 2,
						(draw.line_height) / 2 + WINDOW_HEIGHT / 2, ROOF_COLOR,
						(int)(WINDOW_HEIGHT / ray.perp_wall_dist),
						draw.x, 0, ray.perp_wall_dist, ray.side};

		draw.start = (draw.start < 0) ? 0 : draw.start;
		draw.end = (draw.end >= WINDOW_HEIGHT) ? WINDOW_HEIGHT - 1 : draw.end;
		draw_col(vars, &draw);
	}
}

int			main(void)
{
	t_vars	vars;

	init_vars(WINDOW_WIDTH, WINDOW_HEIGHT, &vars);
	vars.img = &vars.img2;
	//my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	//my_line_put(&img, 1, 1, 1000, 1000);
	//drawcircle(&img, 500, 500, 100, 0x00FFFFFF);
	//drawRectangle(&img, (int []){200, 200}, (int []){400, 0});
	//draw_gradient(vars.img);
	//draw_rainbow(vars.img);
	//mlx_do_key_autorepeatoff(vars.mlx);
	//mlx_put_image_to_window(vars.mlx, vars.win, (vars.img)->img, 0, 0);
	hooks(&vars);
	//printf("x%f y%f\n", vars.cam.x, vars.cam.y);
	draw_scene(&vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img->img, 0, 0);
	mlx_loop(vars.mlx);
}