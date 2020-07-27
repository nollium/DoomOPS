/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemies.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 15:43:58 by dirty             #+#    #+#             */
/*   Updated: 2020/07/27 13:02:43 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int		player_hit(t_camera *cam)
{
	static clock_t	t0 = 0;

	if ((clock() - t0) / CLOCKS_PER_SEC > DAMAGE_COOLDOWN)
	{
		system("(" PLAYER " " HIT_SOUND BACKGROUND ") " OPTIONS);
		t0 = clock();
		cam->hp--;
		return (1);
	}
	return (0);
}

void	get_sprite_path(t_camera *cam, t_sprite *sprite, double new_pos[2])
{
	ft_bzero(new_pos, sizeof(double) * 2);
	if (cam->x - EN_ALIGN <= sprite->x && sprite->x <= cam->x + EN_ALIGN)
		new_pos[0] = cam->x;
	else
		new_pos[0] = sprite->x + EN_SPEED * ((sprite->x > cam->x) ? -1 : 1);
	if (cam->y - EN_ALIGN <= sprite->y && sprite->y <= cam->y + EN_ALIGN)
		new_pos[1] = cam->y;
	else
		new_pos[1] = sprite->y + EN_SPEED * ((sprite->y > cam->y) ? -1 : 1);
}

void	move_ennemy(t_sprite *lst_sprites, t_sprite *sprite, t_camera *cam,
					char **map)
{
	double	new_pos[2];
	int		hit_x;
	int		hit_y;

	hit_x = 0;
	hit_y = 0;
	get_sprite_path(cam, sprite, new_pos);
	if (map[(int)(new_pos[0])][(int)(sprite->y)] == VOID
	&& map[(int)(new_pos[0] + 0.4)][(int)(sprite->y + 0.4)] == VOID
	&& !s_s_collision(lst_sprites, sprite, new_pos[0] + 0.5, sprite->y + 0.5)
	&& !(hit_x = !(my_dist(new_pos[0], sprite->y, cam->x, cam->y)
					> SPRITE_RADIUS)))
		sprite->x = new_pos[0];
	if (map[(int)(sprite->x)][(int)(new_pos[1])] == VOID
	&& map[(int)(sprite->x + 0.4)][(int)(new_pos[1] + 0.4)] == VOID
	&& !s_s_collision(lst_sprites, sprite, sprite->x + 0.5, new_pos[1] + 0.5)
	&& !(hit_y = !(my_dist(sprite->x, new_pos[1], cam->x, cam->y)
					> SPRITE_RADIUS)))
		sprite->y = new_pos[1];
	if (!GOD_MODE && (hit_x || hit_y))
		player_hit(cam);
}

int		ennemies_handler(t_sprite *sprites, t_camera *cam, char **map)
{
	int	n;

	n = get_n(NULL);
	while (n >= 0)
	{
		if (sprites[n].tex_num == ENNEMIES_TEX)
			move_ennemy(sprites, sprites + n, cam, map);
		n--;
	}
	return (0);
}

void	play_death_sound(int n)
{
	static int last = 0;

	if (last == n)
		n = (n + 1) % 6;
	last = n;
	if (n == 0)
		system("(" PLAYER " " EN_DEATH_00 BACKGROUND ") " OPTIONS);
	if (n == 1)
		system("(" PLAYER " " EN_DEATH_01 BACKGROUND ") " OPTIONS);
	if (n == 2)
		system("(" PLAYER " " EN_DEATH_02 BACKGROUND ") " OPTIONS);
	if (n == 3)
		system("(" PLAYER " " EN_DEATH_03 BACKGROUND ") " OPTIONS);
	if (n == 4)
		system("(" PLAYER " " EN_DEATH_04 BACKGROUND ") " OPTIONS);
	if (n == 5)
		system("(" PLAYER " " EN_DEATH_05 BACKGROUND ") " OPTIONS);
}
