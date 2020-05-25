/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 12:50:24 by slutymeme         #+#    #+#             */
/*   Updated: 2020/05/25 21:23:32 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	get_color(t_drawer *draw, t_texture *tex)
{
	tex->y = (int)draw->tex_pos & (tex->height - 1);
	draw->tex_pos += draw->step;
	draw->color = tex->array[tex->height * tex->y + tex->x];
	//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
	if (draw->side == 1)
		draw->color = add_shade(0.2, draw->color);
}

void		draw_col(t_vars *vars, t_drawer *draw)
{
	while (++draw->y < WINDOW_HEIGHT)
	{
		if (draw->start <= draw->y && draw->y <= draw->end)
		{
			get_color(draw, &(vars->text));
			draw->color = (vars->w_color) ? vars->w_color : draw->color;
			if (SHADOW_MODE)	
				draw->color = add_shade(((double)draw->dist / MAP_HEIGHT * 2), draw->color);
		}
		if (draw->y > draw->end)
		{
			draw->color = FLOOR_COLOR;
			if (SHADOW_MODE)
				draw->color = add_shade(1.05 / ((double)draw->y * 2.15 / (double)((WINDOW_WIDTH))) , draw->color);
		}
		my_mlx_pixel_put(vars->img, draw->x, draw->y, draw->color);
	}
}

void		init_drawer(t_drawer *draw, t_ray *ray, int text_height)
{
	draw->line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);
	draw->start = -(draw->line_height) / 2 + WINDOW_HEIGHT / 2;
	draw->end = (draw->line_height) / 2 + WINDOW_HEIGHT / 2;
	draw->color = ROOF_COLOR;
	draw->y = -1;
	draw->dist = ray->perp_wall_dist;
	draw->side = ray->side;
	draw->start = (draw->start < 0) ? 0 : draw->start;
	draw->end = (draw->end >= WINDOW_HEIGHT) ? WINDOW_HEIGHT - 1 : draw->end;

	draw->step = 1.0 * text_height / draw->line_height;
	draw->tex_pos = (draw->start - WINDOW_HEIGHT / 2 + draw->line_height / 2) * draw->step;
}

void		draw_scene(t_vars *vars)
{
	t_ray		ray;
	t_drawer	draw;

	draw.x = -1;
	while (++(draw.x) < WINDOW_WIDTH)
	{
		raycast(&ray, vars, draw.x);
		init_drawer(&draw, &ray, vars->text.height);
		draw_col(vars, &draw);
	}
}

void		draw_text(t_texture *text, t_data *img)
{
	int	x;
	int	y;
	x = -1;
	while (++x < text->width)
	{
		y = -1;
		while (++y < text->height)
			//my_mlx_pixel_put(img, x, y, 0x00FFFFFF);
			my_mlx_pixel_put(img, x, y, text->array[text->width * y + x]);
	}
}

void		load_xpm(t_data *data, char *path, t_vars *vars)
{
	data->img = mlx_xpm_file_to_image(vars->mlx, path, &(data->width), &(data->height));
	data->addr = mlx_get_data_addr(data->img, &(data->bits_per_pixel), &(data)->line_length,
								 &(data)->endian);
}

void		img_to_text(t_data *data, t_texture *text)
{
	int	x;
	int	y;
	
	x = -1;
	text->array = malloc(sizeof(int) * data->width * data->height);
	text->width = data->width;
	text->height = data->height;
	while (++x < text->width)
	{
		y = -1;
		while (++y < text->height)
			text->array[text->width * y + x] = *(unsigned int *)(data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8)));
	}
}


int			main(void)
{
	t_vars	vars;

	init_vars(WINDOW_WIDTH, WINDOW_HEIGHT, &vars);
	vars.img = &vars.img2;
	//my_mlx_pixel_put(vars.img, 5, 5, 0x00FF0000);
	//my_line_put(vars.img, 1, 1, 1000, 1000, 0xFF);
	//drawcircle(vars.img, 500, 500, 100, 0x00FFFFFF);
	//drawRectangle(vars.img, (int []){200, 200}, (int []){400, 0});
	draw_gradient(vars.img);
	//draw_rainbow(vars.img);
	//mlx_do_key_autorepeatoff(vars.mlx);
	//mlx_put_image_to_window(vars.mlx, vars.win, (vars.img)->img, 0, 0);
	hooks(&vars);
	//printf("x%f y%f\n", vars.cam.x, vars.cam.y);
	//draw_scene(&vars);
	draw_text(&(vars.text), vars.img);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img->img, 0, 0);
	t_data data;
	t_texture text;
	load_xpm(&data, "pics/128x128.xpm", &vars);
	img_to_text(&data, &text);
	draw_text(&text, vars.img);
	vars.text = text;
	/*if (data.img)
		mlx_put_image_to_window(vars.mlx, vars.win, data.img, 0, 0);
	else
		ft_putendl_fd("\e[31mImage couldn't load\e[0m", 1);
	*/
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img->img, 0, 0);
	mlx_loop(vars.mlx);
}