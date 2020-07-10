/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 18:20:31 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/11 00:05:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

int	check_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd <= 0)
		return (FILE_INVALID_ERROR);
	return (SUCCESS_CODE);
}

int	error_print(int error)
{
	static char	*errors[] = {
								"NO ERROR", "UNKNOWN ERROR",
								"FILE INVALID ERROR", "MAP ERROR",
								"WRONG FILE EXTENSION", "NULL ERROR",
								"MALLOC ERROR",
								"CONFIG ERROR", "RESOLUTION_ERROR",
								"COLOR ERROR", "TEXTURE_ERROR", "MLX_ERROR", 0
							};
	int			i;

	i = -1;
	if (error == SUCCESS_CODE)
		return (SUCCESS_CODE);
	while (errors[++i])
	{
		if (i == -error)
		{
			ft_putendl_fd(errors[-error], STDERR);
			return (error);
		}
	}
	ft_putendl_fd("UNKNOWN ERROR", STDERR);
	return (error);
}
