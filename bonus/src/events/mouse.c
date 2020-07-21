/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 15:57:06 by user42            #+#    #+#             */
/*   Updated: 2020/07/21 21:12:45 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int		mouse_press_handler(int keycode, int x, int y, t_vars *vars)
{
	(void)(x && y);
	if (keycode == 1)
		return (key_handler(LEFT_CLICK, vars));
	return (key_handler(-1, vars));
}

int		mouse_release_handler(int keycode, int x, int y, t_vars *vars)
{
	(void)(x && y);
	if (keycode == 1)
		return (release_handler(LEFT_CLICK, vars));
	return (release_handler(-1, vars));
}

int		click_handler(t_vars *vars)
{
	static clock_t	last_shot = 0;
	double			elapsed;
	static int		released = 1;

	elapsed = (double)(clock() - last_shot) / (double)CLOCKS_PER_SEC;
	if (!released && !key_chr(vars->keys, LEFT_CLICK, K_BUFF_SIZE))
		released = 1;
	if (key_chr(vars->keys, LEFT_CLICK, K_BUFF_SIZE)
		&& elapsed > (double)SHOT_DURATION && released)
	{
		released = 0;
		if (elapsed > (double)SHOT_DURATION + (double)SHOT_COOLDOWN)
		{
			last_shot = clock();
			vars->draw_shot = 1;
			system("(" PLAYER " " GUNSHOT_PATH BACKGROUND ") " OPTIONS);
			shoot_sprites(&(vars->sprites), &(vars->num_sprites));
			return (1);
		}
	}
	if (elapsed > (double)SHOT_DURATION && vars->draw_shot)
		vars->draw_shot = 0;
	return (0);
}
