/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 14:34:19 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/18 16:17:33 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_H
 #define SPRITES_H

 #include "structs/structs.h"
 #include "settings.h"
 
void	sort_sprites(int n, t_sprites_sorter *arr);
void	init_sprites_info(t_vars *vars, t_sprites_sorter *sprites_srt);
void	init_sprite_drawing(t_sprite_drawer *, t_camera *,
							t_sprite *, t_texture *, t_screen *);
void	cast_sprites(t_sprite *sprites, t_camera *, t_vars *);

#endif