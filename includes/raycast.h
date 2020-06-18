/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 14:55:33 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/18 16:15:13 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
 #define RAYCAST_H
 #include "structs/structs.h"
 #include "settings.h"

/*
** RAYCAST 
*/

void	raycast_walls(t_ray *ray, t_vars *vars, int x);

#endif