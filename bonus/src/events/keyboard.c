/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirty <dirty@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 17:13:04 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/13 01:01:24 by dirty            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "garbage_collection.h"

int				click_handler(t_vars *vars)
{
	static clock_t	last_shot = 0;
	double			elapsed;
	static int		released = 1;
	
	elapsed = (double)(clock() - last_shot) / (double)CLOCKS_PER_SEC;
	if (!key_chr(vars->keys, LEFT_CLICK, K_BUFF_SIZE))
		released = 1;
	if (key_chr(vars->keys, LEFT_CLICK, K_BUFF_SIZE) && elapsed > (double)SHOT_DURATION
	&& released)
	{
		released = 0;
		if (elapsed > (double)SHOT_DURATION + (double)SHOT_COOLDOWN)
		{
			last_shot = clock();
			vars->draw_shot = 1;
			return (1);
		}
		
	}
	if (elapsed > (double)SHOT_DURATION && vars->draw_shot)
	{
		vars->draw_shot = 0;
		return (1);
	}
	return (0);
}

int				keyboard_handler(t_vars *vars)
{
	int redraw;

	redraw = (int)(forward_handler(vars) | backward_handler(vars)
					| right_handler(vars) | left_handler(vars)
					| alt_handler(vars) | mouse_move_handler(vars)
					| click_handler(vars));
	if (key_chr(vars->keys, CTRL_KEY, K_BUFF_SIZE))
	{
		if (key_chr(vars->keys, C_KEY, K_BUFF_SIZE))
		{
			free_vars(vars);
			exit(0);
		}
	}
	return (redraw);
}
