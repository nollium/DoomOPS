/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 12:50:24 by slutymeme         #+#    #+#             */
/*   Updated: 2020/06/06 21:24:11 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	get_color(t_drawer *draw, t_texture *tex)
{
	tex->y = (int)draw->tex_pos & (tex->height - 1);
	draw->tex_pos += draw->step;
	if (!tex->array || (tex->height * tex->y + tex->x) > tex->height * tex->width)
		return;//printf("WOOPSIE DOOPSY I DID A LITTLE FUCKY WUCKY\n");
	else
		draw->color = tex->array[tex->height * tex->y + tex->x];
	//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
	
}

void		draw_col(t_vars *vars, t_drawer *draw)
{
	while (++draw->y < WINDOW_HEIGHT)
	{
		if (draw->start <= draw->y && draw->y <= draw->end)
		{
			get_color(draw, &(vars->text[draw->side]));
			//draw->color = (vars->w_color) ? vars->w_color : draw->color;
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
	draw->side = ray->w_num;
	draw->start = (draw->start < 0) ? 0 : draw->start;
	draw->end = (draw->end >= WINDOW_HEIGHT) ? WINDOW_HEIGHT - 1 : draw->end;
	draw->step = 1.0 * text_height / draw->line_height;
	draw->tex_pos = (draw->start - WINDOW_HEIGHT / 2 + draw->line_height / 2) * draw->step;
}

/*	used variables :
**		vars->num_sprites; vars->cam; vars->sprite[]; v
** 
*/

void		draw_scene(t_vars *vars)
{
	t_ray		ray;
	t_drawer	draw;
	int			i;

	draw.x = -1;
	while (++(draw.x) < WINDOW_WIDTH)
	{
		raycast_walls(&ray, vars, draw.x);
		init_drawer(&draw, &ray, vars->text[ray.w_num].height);
		draw_col(vars, &draw);
	}
	cast_sprites(vars->sprites, &(vars->cam), vars);
}

void		draw_text(t_texture *text, t_data *img, int x0, int y0)
{
	int	x;
	int	y;
	x = -1;
	while (++x < text->width)
	{
		y = -1;
		while (++y < text->height)
			//my_mlx_pixel_put(img, x, y, 0x00FFFFFF);
			my_mlx_pixel_put(img, x + x0, y + y0, text->array[text->width * y + x]);
	}
}


int			main(void)
{
	t_vars	vars;
	int		i = -1;
	
	DEBUG_PRINT("hello");
	init_vars(WINDOW_WIDTH, WINDOW_HEIGHT, &vars);
	DEBUG_PRINT("hi");
	vars.img = &vars.img2;
	//my_mlx_pixel_put(vars.img, 5, 5, 0x00FF0000);
	//my_line_put(vars.img, 1, 1, 1000, 1000, 0xFF);
	//drawcircle(vars.img, 500, 500, 100, 0x00FFFFFF);
	//drawRectangle(vars.img, (int []){200, 200}, (int []){400, 0});
	draw_gradient(vars.img);
	hooks(&vars);
	t_texture text;
	load_texture(&text, "pics/shrek.xpm", vars.mlx);
	while ((vars.text)[++i].array)
		draw_text(&(vars.text[i]), vars.img, 0, 0);
//	draw_text(&text, vars.img, 64, 0);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img->img, 0, 0);
	mlx_loop(vars.mlx);
}