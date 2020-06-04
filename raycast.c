/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 21:24:35 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/04 18:10:21 by smaccary         ###   ########.fr       */
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

/*
static void swap_sprites(t_sprite *sprite_1, t_sprite *sprite_2)
{
	t_sprite	tmp;
	
	tmp = *sprite_1;
	*sprite_1 = *sprite_2;
	*sprite_2 = tmp;
}*/
/* Function to sort an array using insertion sort*/
void 		sort_sprites(int n, t_sprites_sorter *arr) 
{ 
	register int	i;
	register int	j; 
	double 			key;

	for (i = 1; i < n; i++) 
	{ 
		key = arr[i].sprite_distance; 
		j = i - 1; 

		/* Move elements of arr[0..i-1], that are 
		greater than key, to one position ahead 
		of their current position */
		while (j >= 0 && arr[j].sprite_distance < key) 
		{ 
			arr[j + 1] = arr[j]; 
			j = j - 1; 
		} 
		arr[j + 1].sprite_distance = key; 
	} 
} 

static int	init_sprites_info(t_sprites_sorter *sprites_srt, t_vars *vars)
{
	register int i;

	sprites_srt = malloc(sizeof(t_sprites_sorter) * vars->num_sprites);
	if (!sprites_srt)
		return (ERROR_CODE);
	i = -1;
	while (++i < vars->num_sprites)
		sprites_srt[i] = (t_sprites_sorter){i, ((vars->cam.x - vars->sprites[i].x) * (vars->cam.x - vars->sprites[i].x)
							+ (vars->cam.y - vars->sprites[i].y) * (vars->cam.y - vars->sprites[i].y))};
	sort_sprites(vars->num_sprites, sprites_srt);
	for (size_t j = 0; j < vars->num_sprites; j++)
		printf("%lf ", sprites_srt[j].sprite_distance);
	return (SUCCESS_CODE);
}

void		cast_sprites(t_ray *ray, t_sprite *sprites, t_camera *cam, t_vars *vars)
{
	t_sprites_sorter *sprites_srt;

	if (!init_sprites_info(sprites_srt, vars))
		ft_putendl_fd("MALLOC ERROR", 2);
	free(sprites_srt);
}