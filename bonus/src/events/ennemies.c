/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemies.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirty <dirty@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 15:43:58 by dirty             #+#    #+#             */
/*   Updated: 2020/07/14 18:57:55 by dirty            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

double  my_dist(double x0, double y0, double x1, double y1)
{    
    return (sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1)));
}

int		s_s_collision(t_sprite *sprites, t_sprite *curr, double x, double y)
{
	int		i;

	i = -1;
	while (sprites[++i].tex_num)
	{
		if (sprites[i].tex_num == ENNEMIES_TEX && sprites + i != curr)
		{
			if (my_dist(sprites[i].x + 0.5, sprites[i].y + 0.5, x, y)
				<= SPRITE_RADIUS)
				return (1);
		}
	}
	return (0);
}

int		sprite_collision(t_sprite *sprites, double x, double y)
{
	int		i;

	i = -1;
	while (sprites[++i].tex_num)
	{
		if (sprites[i].tex_num == ENNEMIES_TEX)
		{
			if (my_dist(sprites[i].x, sprites[i].y, x, y) <= SPRITE_RADIUS)
				return (1);
		}
	}
	return (0);
}

int		player_hit(t_camera *cam)
{
	static clock_t	t0 = 0;

	if ((clock() - t0) / CLOCKS_PER_SEC > DAMAGE_COOLDOWN)
	{
		t0 = clock();
		cam->hp--;
		return (1);
	}
	return (0);
}

void	move_ennemy(t_sprite *lst_sprites, t_sprite *sprite, t_camera *cam,
					char **map)
{
	double	new_pos[2];
	int		hit_x;
	int		hit_y;
		
	ft_bzero(new_pos, sizeof(new_pos));
	hit_x = 0;
	hit_y = 0;
	if (sprite->x != cam->x)
		new_pos[0] = sprite->x + EN_SPEED * ((sprite->x > cam->x) ? -1 : 1);
	if (sprite->y != cam->y)
		new_pos[1] = sprite->y + EN_SPEED * ((sprite->y > cam->y) ? -1 : 1);
	if (map[(int)(new_pos[0])][(int)(sprite->y)] == VOID
&& !(s_s_collision(lst_sprites, sprite, new_pos[0] + 0.5, sprite->y + 0.5))
&& !(hit_x = !(my_dist(new_pos[0], sprite->y, cam->x, cam->y) > SPRITE_RADIUS)))
		sprite->x = new_pos[0];
	if (map[(int)(sprite->x)][(int)(new_pos[1])] == VOID
&& !(s_s_collision(lst_sprites, sprite, sprite->x + 0.5, new_pos[1] + 0.5))
&& !(hit_y = !(my_dist(sprite->x, new_pos[1], cam->x, cam->y) > SPRITE_RADIUS)))
		sprite->y = new_pos[1];
	if (hit_x || hit_y)
		player_hit(cam);
}

int		ennemies_handler(t_sprite *sprites, t_camera *cam, char **map)
{
	int	i;

	i = -1;
	while (sprites[++i].tex_num)
	{
		if (sprites[i].tex_num == ENNEMIES_TEX)
			move_ennemy(sprites, sprites + i, cam, map);
	}
	return (0);
}
