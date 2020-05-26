/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 21:24:35 by smaccary          #+#    #+#             */
/*   Updated: 2020/05/26 18:51:19 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_raycast(t_vars *vars, int x, t_ray *ray)
{
	long double	camera_x;

	camera_x = 2 * x / (long double)WINDOW_WIDTH - 1.0;
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
	{
		ray->step_x = -1;
		ray->side_dist_x = (vars->cam.x - vars->map.x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x =
			(vars->map.x + 1.0 - vars->cam.x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (vars->cam.y - vars->map.y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y =
			(vars->map.y + 1.0 - vars->cam.y) * ray->delta_dist_y;
	}
}

static void	perform_dda(t_vars *vars, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			vars->map.x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			vars->map.y += ray->step_y;
			ray->side = 1;
		}
		if (vars->map.worldMap[vars->map.x][vars->map.y] - '0' > 0)
			ray->hit = 1;
	}
}
//w -0.15 e -0.05  side = 1|side = 0 n -0.91 s s-0.58
//0.72 1.03 /  0.73 1.10s
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
}

static int	get_wall_side(t_vars *vars, t_ray *ray)
{
	double		angle;
	double		diff;
	double		max;
	int			corner;
	static int	corner_angle[] = {45, 145, -55, -135};
	int			i;

//	printf("angle : %lf && ray->side = %d\n", angle, ray->ray->side);
	i = -1;
	angle = atan2(vars->map.y - (double)vars->cam.y, (double)vars->map.x - (double)vars->cam.x) * 180.0 / PI;
	max = DBL_MAX;
	while (++i <= 3)
		if (((diff = fabs(angle - (double)corner_angle[i])) < max))
		{
			max = diff;
			corner = corner_angle[i];
		}

	if (corner == 45)
		return ((ray->side) ? WEST : NORTH);
	else if (corner == 145)
		return ((ray->side) ? WEST : SOUTH);
	else if (corner == -55)
		return ((ray->side) ? EAST : NORTH);
	else if (corner == -135)
		return ((ray->side) ? EAST : SOUTH);
}

static void	get_texture_coords(t_vars *vars, t_ray *ray)
{
	double wallX; //where exactly the wall was hit
	int texNum;

	//texturing calculations
	texNum = vars->map.worldMap[vars->map.x][vars->map.x] - 1; //1 subtracted from it so that texture 0 can be used!

	//calculate value of wallX
	if (ray->side == 0)
		wallX = vars->cam.y + ray->perp_wall_dist * ray->dir_y;
	else
		wallX = vars->cam.x + ray->perp_wall_dist * ray->dir_x;
	(void)0;
	wallX -= floor((wallX));

	//x coordinate on the texture
	vars->text[ray->w_num].x = (int)(wallX * (double)(vars->text[ray->w_num].width));
	if(ray->side == 0 && ray->dir_x > 0)
		vars->text[ray->w_num].x = vars->text[ray->w_num].width - vars->text[ray->w_num].x - 1;
	if(ray->side == 1 && ray->dir_y < 0)
		vars->text[ray->w_num].x = vars->text[ray->w_num].width - vars->text[ray->w_num].x - 1;
}

void		raycast(t_ray *ray, t_vars *vars, int x)
{
	init_raycast(vars, x, ray);
	get_step(vars, ray);
	perform_dda(vars, ray);
	get_wall_dist(vars, ray);
	ray->w_num = get_wall_side(vars, ray);
	get_texture_coords(vars, ray);
}
