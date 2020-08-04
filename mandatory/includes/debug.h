/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:30:19 by smaccary          #+#    #+#             */
/*   Updated: 2020/08/04 18:30:19 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H
# include "settings.h"

# define ERROR_CODE		-1
# define SUCCESS_CODE	0

# define FILE_INVALID_ERROR		-2
# define MAP_ERROR				-3
# define WRONG_EXTENSION_ERROR	-4
# define NULL_ERROR				-5
# define MALLOC_ERROR			-6
# define CONFIG_ERROR			-7
# define RESOLUTION_ERROR		-8
# define COLOR_ERROR			-9
# define TEXTURE_ERROR			-10
# define MLX_ERROR				-11

# define STDERR 2

void	print_map(char **array);
int		error_print(int error);
int		check_file(char *path);

#endif
