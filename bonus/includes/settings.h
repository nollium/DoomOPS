/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirty <dirty@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 16:13:08 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/13 18:42:36 by dirty            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H
# include <unistd.h>
# include "mlx.h"
# include <math.h>

# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <float.h>
# include "libftprintf.h"
# include "structs/structs.h"
# include "debug.h"

# define PI 3.141592653
# define WARNINGS		1
# define WARN_LEVEL		100000
# define DEBUG_MODE		1

# ifndef SHADOW_MODE
#  define SHADOW_MODE	1
# endif

# define SPAWN_CHARS		"NSEW"
# define VOID_CHARS			"NSEW02"
# define WALL				'1'
# define VOID				'0'
# define WHITESPACES		"\t\010\011\012\013 "

# define SPEED				0.04
# define TURN_SPEED			SPEED
# define ALT_MULT			4

# define NORTH	0
# define SOUTH	1
# define EAST	2
# define WEST	3

#endif
