/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 16:13:08 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/25 18:06:05 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H
# include <unistd.h>
# include <mlx.h>
# include <math.h>

# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <float.h>
# include "libftprintf.h"
# include "structs/structs.h"

# define DEBUG_PRINT(txt) printf("\n\n%s\n", txt)
# define PI 3.141592653
# define WARNINGS 		1
# define WARN_LEVEL		100000
# define DEBUG_MODE		1
# define SHADOW_MODE	0
# define SPAWN_CHARS		"NSEW"
# define WHITESPACES		"\t\010\011\012\013 "

# define ERROR_CODE		-1
# define SUCCESS_CODE	0

# define FILE_INVALID_ERROR -2
# define MAP_ERROR -3
# define WRONG_EXTENSION_ERROR -4
# define NULL_ERROR -5
# define MALLOC_ERROR -6
# define CONFIG_ERROR -7
# define RESOLUTION_ERROR -8
# define COLOR_ERROR -9

# define SPEED				0.04
# define TURN_SPEED			SPEED
# define ALT_MULT			2

# define NORTH	0
# define SOUTH	1
# define EAST	2
# define WEST	3

#endif
