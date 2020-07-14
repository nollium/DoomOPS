/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirty <dirty@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 14:34:19 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/13 23:32:07 by dirty            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_H
# define SPRITES_H

# include "structs/structs.h"
# include "settings.h"
# include "frontend.h"

void	swap_sprites(t_sprite *s1, t_sprite *s2);
void	sort_sprites(int n, t_sprites_sorter *arr) __attribute__((hot));
void	init_sprites_info(t_vars *vars, t_sprites_sorter *sprites_srt)\
 __attribute__((hot));
void	init_sprite_drawing(t_sprite_drawer *d, t_camera *c,
				t_sprite *s, t_texture *t) __attribute__((hot));

#endif
