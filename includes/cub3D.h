/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/* 	  cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 12:51:48 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/09 07:28:40 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
 #define CUB3D_H
 // to be removed

 #include "libftprintf.h"


 #include "sprites.h"
 #include "parsing.h"
 #include "frontend.h"
 #include "events.h"
 #include "raycast.h"
 #include "garbage_collection.h"
 #include "settings.h"


 //5 2.9 | 3.9 4
 //#define WINDOW_WIDTH		800
 //#define WINDOW_HEIGHT		800
 //#define MAP_WIDTH 			8
 //#define MAP_HEIGHT 		16
 //#define MAP_PATH			"./map.cub"

 //#define SPAWN_DIR			'W'
 //#define SPAWN_X			2
 //#define SPAWN_Y			3

/*
** SCREEN_DIST = (SCREEN_WIDTH) / (tan(FOV / 2) * 2)
*/

 #define SCREEN_DIST 277

#endif