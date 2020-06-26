/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 21:24:35 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/23 17:43:05 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

static void	init_raycast(t_vars *vars, int x, t_ray *ray)
{
	long double	camera_x;

	camera_x = 2 * x / (long double)vars->game_screen.width - 1.0;
	ray->dir_x = vars->cam.dir_x + vars->cam.plane.x * camera_x;
	ray->dir_y = vars->cam.dir_y + vars->cam.plane.y * camera_x;
	vars->map.x = (int)(vars->cam.x);
	vars->map.y = (int)(vars->cam.y);
	ray->delta_dist_x = fabsl(1 / ray->dir_x);
	ray->delta_dist_y = fabsl(1 / ray->dir_y);
	ray->hit = 0;
}

static void	get_step(t_vars *vars, t_ray *ray)
{
	if (ray->dir_x < 0)
		ray->side_dist_x = (vars->cam.x - vars->map.x) * ray->delta_dist_x;
	else
		ray->side_dist_x =
			(vars->map.x + 1.0 - vars->cam.x) * ray->delta_dist_x;
	if (ray->dir_y < 0)
		ray->side_dist_y = (vars->cam.y - vars->map.y) * ray->delta_dist_y;
	else
		ray->side_dist_y =
			(vars->map.y + 1.0 - vars->cam.y) * ray->delta_dist_y;
	ray->step_x = (ray->dir_x < 0) ? -1 : 1;
	ray->step_y = (ray->dir_y < 0) ? -1 : 1;
}

static void	perform_dda(t_vars *vars, t_ray *ray)
{
	while (ray->hit == 0)
	{
		ray->side = !(ray->side_dist_x < ray->side_dist_y);
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			vars->map.x += ray->step_x;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			vars->map.y += ray->step_y;
		}
		ray->hit = (((vars->map.array)[vars->map.x][vars->map.y] - '0' ) > 0);
	}
}

static void	get_wall_dist(t_vars *vars, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist =
			(vars->map.x - vars->cam.x + (1.0 - ray->step_x) / 2.0)
				/ ray->dir_x;
	else
		ray->perp_wall_dist =
			(vars->map.y - vars->cam.y + (1.0 - ray->step_y) / 2.0)
				/ ray->dir_y;
	if (ray->perp_wall_dist == 0)
		ray->perp_wall_dist = 0.01;
}

static double	get_corner(double angle)
{
	int				i;
	double			max;
	double			corner;
	static double	corner_angle[] = {36.0, 145.0, -39.0, -140.5};
	double			diff;


	i = -1;
	max = DBL_MAX;
	while (++i <= 3)
		if (((diff = fabs(angle - (double)corner_angle[i])) < max))
		{
			max = diff;
			corner = corner_angle[i];
		}
	return (corner);
}

static int	get_wall_side(t_vars *vars, t_ray *ray)
{
	double			corner;

	corner = get_corner(atan2((double)vars->map.y - (double)vars->cam.y,
						(double)vars->map.x - (double)vars->cam.x) * 180.0 / PI);
	if (corner == 36.0)
		return ((ray->side) ? WEST : NORTH);
	else if (corner == 145.0)
		return ((ray->side) ? WEST : SOUTH);
	else if (corner == -39.0)
		return ((ray->side) ? EAST : NORTH);
	else if (corner == -140.5)
		return ((ray->side) ? EAST : SOUTH);

	ft_putendl_fd("Weird", 2);
	return (4);
}

static void	get_texture_coords(t_vars *vars, t_ray *ray)
{
	double wall_x;

	if (ray->side == 0)
		wall_x = vars->cam.y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = vars->cam.x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor((wall_x));
	vars->text[ray->w_num].x = (int)
		(wall_x * (double)(vars->text[ray->w_num].width));
	if (ray->side == 0 && ray->dir_x > 0)
		vars->text[ray->w_num].x = vars->text[ray->w_num].width
									- vars->text[ray->w_num].x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		vars->text[ray->w_num].x = vars->text[ray->w_num].width
									- vars->text[ray->w_num].x - 1;
}

void		raycast_walls(t_ray *ray, t_vars *vars, int x)
{
	init_raycast(vars, x, ray);
	get_step(vars, ray);
	perform_dda(vars, ray);
	get_wall_dist(vars, ray);
	ray->w_num = get_wall_side(vars, ray);
	get_texture_coords(vars, ray);
	vars->z_buffer[x] = ray->perp_wall_dist;
}

void		cast_sprites(t_sprite *sprites, t_camera *cam, t_vars *vars)
{
	t_sprites_sorter	*sprites_srt;
	
	vars->seen_sprite = 0;
	if (!(sprites_srt = malloc(sizeof(t_sprites_sorter) * vars->num_sprites)))
		ft_putendl_fd("MALLOC ERROR", 2);
	init_sprites_info(vars, sprites_srt);
	put_sprites(vars, sprites, sprites_srt, cam);
	free(sprites_srt);
}