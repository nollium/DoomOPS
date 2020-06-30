/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 18:20:31 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/30 18:28:54 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

int	error_print(int error)
{
	static char	*errors[] = {
								"NO ERROR", "UNKNOWN ERROR",
								"FILE INVALID ERROR", "MAP ERROR",
								"WRONG FILE EXTENSION", "NULL ERROR",
								"MALLOC ERROR",
								"CONFIG ERROR", "RESOLUTION_ERROR",
								"COLOR ERROR", "MLX_ERROR"
							};

	if (error != SUCCESS_CODE)
		ft_putendl_fd(errors[-error], 2);
	return (error);
}
