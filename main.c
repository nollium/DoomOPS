/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 12:50:24 by slutymeme         #+#    #+#             */
/*   Updated: 2020/04/19 17:56:44 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		draw_col(t_data *img, int i, int line_height, int color)
{
	int	draw_start;
	int	draw_end;

	draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
	draw_start = (draw_start < 0) ? 0 : draw_start;
	draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
	draw_end = (draw_end >= WINDOW_HEIGHT) ? WINDOW_HEIGHT - 1 : draw_end; 
	my_line_put(img, i, 0, i, draw_start, ROOF_COLOR);
	my_line_put(img, i, draw_start, i, draw_end, color);
	my_line_put(img, i, draw_end, i, WINDOW_HEIGHT, FLOOR_COLOR);
}

void		draw_scene(t_vars *vars)
{
	int		i;
	int		color;
	t_ray	ray;

	i = -1;
	while (++i < WINDOW_WIDTH)
	{
		ray = raycast(vars, i);
		draw_col(vars->img, i, (int)(WINDOW_HEIGHT / ray.perp_wall_dist), (ray.side) ? WALL_SIDE_COLOR : WALL_COLOR);
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
//	mlx_do_key_autorepeatoff(vars.mlx);
//	mlx_put_image_to_window(vars.mlx, vars.win, (vars.img)->img, 0, 0);
	hooks(&vars);
	//printf("x%f y%f\n", vars.cam.x, vars.cam.y);
	draw_scene(&vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img->img, 0, 0);
	mlx_loop(vars.mlx);
}