/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 22:08:40 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/23 17:33:46 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collection.h"
#include "libftprintf.h"
#include "events.h"

void	free_str(char **str)
{
	if (!*str)
		return ;
	free(*str);
	*str = NULL;
}

void	free_split(char ***split)
{
	char **array;

	if (!*split)
		return ;
	array = *split - 1;
	while (*(++array))
	{
		free(*array);
		*array = NULL;
	}
	free(*split);
	*split = NULL;
}

void	free_textures(t_texture *text)
{
	int			i;

	if (!(text))
		return ;
	i = -1;
	while (text[++i].array)
	{
		free(text[i].array);
		text[i].array = NULL;
	}
}

void	free_vars(t_vars *vars)
{
	int	i;

	i = -1;
	if (vars->mlx && vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx && vars->img2[0].img)
		mlx_destroy_image(vars->mlx, vars->img2[0].img);
	if (vars->mlx && vars->img2[1].img)
		mlx_destroy_image(vars->mlx, vars->img2[1].img);
	free_split(&(vars->map.array));
	free_textures(&(vars->text));
	free(vars->sprite_ptr);
	free(vars->gun.array);
	free(vars->flash.array);
	free(vars->z_buffer);
	while (++i < N_BARS)
		free((vars->health_bars[i]).array);
	i = -1;
	while (vars->text_paths[++i])
		free(vars->text_paths[i]);
	*vars = (t_vars){0};
	system("(" KILL_COMMAND " " PLAYER " )" OPTIONS);
	system("(" PLAYER " " DEATH_SOUND BACKGROUND ") " OPTIONS);
}

void	free_cub(t_list **alst)
{
	if (!*alst)
		return ;
	ft_lstclear(alst, free);
	*alst = NULL;
}
