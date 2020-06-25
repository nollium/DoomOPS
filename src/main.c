/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 15:49:02 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/25 18:02:09 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	while (++draw->y < draw->screen->height)
	{
		if (draw->start <= draw->y && draw->y <= draw->end)
		{
			get_color(draw, &(vars->text[draw->side]));
			//draw->color = (vars->w_color) ? vars->w_color : draw->color;
			if (SHADOW_MODE)	
				draw->color = add_shade(((double)draw->dist / 16 * 2), draw->color);
		}
		if (draw->y > draw->end)
		{
			draw->color = FLOOR_COLOR;
			if (SHADOW_MODE)
				draw->color = add_shade(1.05 / ((double)draw->y * 2.15 / (double)((draw->screen->height))) , draw->color);
		}
		my_mlx_pixel_put(vars->img, draw->x, draw->y, draw->color);
	}
}

void		init_drawer(t_drawer *draw, t_ray *ray, int text_height)
{
	draw->line_height = (int)(draw->screen->height / ray->perp_wall_dist);
	draw->start = -(draw->line_height) / 2 + draw->screen->height / 2;
	draw->end = (draw->line_height) / 2 + draw->screen->height / 2;
	draw->color = ROOF_COLOR;
	draw->y = -1;
	draw->dist = ray->perp_wall_dist;
	draw->side = ray->w_num;
	draw->start = (draw->start < 0) ? 0 : draw->start;
	draw->end = (draw->end >= draw->screen->height) ? draw->screen->height - 1 : draw->end;
	draw->step = 1.0 * text_height / draw->line_height;
	draw->tex_pos = (draw->start - draw->screen->height / 2 + draw->line_height / 2) * draw->step;
}

/*	used variables :
**		vars->num_sprites; vars->cam; vars->sprite[]; v
** 
*/

void		draw_scene(t_vars *vars)
{
	t_ray		ray;
	t_drawer	draw;

	draw.x = -1;
	draw.screen = &(vars->game_screen);
	while (++(draw.x) < draw.screen->width)
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


int			main(int argc, char **argv)
{
	t_vars	vars;
	int		i = -1;

	vars = (t_vars){0};
	if (argc != 2)
	{
		ft_putendl_fd("ERROR: WRONG ARGUMENTS\nUSAGE : ./cub3D config.cub", 2);
		return (1);
	}
	if ((init_vars(argv[1], &vars)) != SUCCESS_CODE)
		return (1);
	vars.img = vars.img2;
	//my_mlx_pixel_put(vars.img, 5, 5, 0x00FF0000);
	//my_line_put(vars.img, 1, 1, 1000, 1000, 0xFF);
	//drawcircle(vars.img, 500, 500, 100, 0x00FFFFFF);
	//drawRectangle(vars.img, (int []){200, 200}, (int []){400, 0});
//	mlx_do_sync(vars.mlx);
	draw_gradient(vars.img);
	hooks(&vars);
	t_texture text;
	load_texture(&text, "pics/shrek.xpm", vars.mlx);
	while ((vars.text)[++i].array)
		draw_text(&(vars.text[i]), vars.img, 0, 0);
//	draw_text(&text, vars.img, 64, 0);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img->img, 0, 0);
	DEBUG_PRINT("AHHAHAHAIUHDZAHLIDHALIHDLIHLDAHLZDHLAZLDAKZJZADZMJADMLMLZAMMJZLAJMZJMA");
	//printf("Z:%d\n", FORWARD_KEY)
	mlx_loop(vars.mlx);
}