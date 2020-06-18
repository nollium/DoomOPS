/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collection.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 14:59:21 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/18 16:11:36 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTION_H
 #define GARBAGE_COLLECTION_H

 #include "structs/structs.h"
 #include <mlx.h>

void	free_str(char **str);
void    free_split(char ***split);
int		free_garbage(t_vars *vars);

#endif