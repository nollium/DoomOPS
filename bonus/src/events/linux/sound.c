/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 17:00:02 by smaccary          #+#    #+#             */
/*   Updated: 2020/08/04 19:08:22 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int	stop_sounds(void)
{
	return (system("(" KILL_COMMAND " " PLAYER " )" OPTIONS));
}

int	play_sound(char *path)
{
	char	command[1000];

	ft_bzero(command, 1000);
	ft_strlcat(command, "(" PLAYER " ", 1000);
	ft_strlcat(command, path, 1000);
	ft_strlcat(command, BACKGROUND ") " OPTIONS, 1000);
	return (system(command));
}
