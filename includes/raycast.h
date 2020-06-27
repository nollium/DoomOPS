/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 14:55:33 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/27 18:28:44 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H
# include "structs/structs.h"
# include "settings.h"
# include "sprites.h"

/*
** RAYCAST
*/

void	raycast_walls(t_ray *ray, t_vars *vars, int x) __attribute__((hot));
void	cast_sprites(t_sprite *s, t_camera *c, t_vars *v) __attribute__((hot));

void	perform_dda(t_vars *vars, t_ray *ray);
void	get_texture_coords(t_vars *vars, t_ray *ray);
void	get_texture_coords(t_vars *vars, t_ray *ray);
void	get_step(t_vars *vars, t_ray *ray);
void	init_raycast(t_vars *vars, int x, t_ray *ray);
void		put_sprites(t_vars *vars, t_sprite *sprites,
						t_sprites_sorter *sprites_srt, t_camera *cam);

#endif
