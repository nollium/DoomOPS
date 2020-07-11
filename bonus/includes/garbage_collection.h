/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collection.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 14:59:21 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/04 18:14:44 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTION_H
# define GARBAGE_COLLECTION_H

# include "structs/structs.h"
# include "libftprintf.h"
# include "mlx.h"

/*
** Useful garbage collection functions
*/

void	free_str(char **str);
void	free_split(char ***split);
void	free_textures(t_texture **t);

/*
** Cub3D specific functions
*/

void	free_vars(t_vars *vars);
void	free_cub(t_list **alst);

#endif
