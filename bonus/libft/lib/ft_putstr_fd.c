/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 19:46:38 by smaccary          #+#    #+#             */
/*   Updated: 2019/12/19 12:27:12 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../libftprintf.h"

int	ft_putstr_fd(char *s, int fd)
{
	int len;

	if (!s)
		return (0);
	len = ft_strlen(s);
	write(fd, s, len);
	return (len);
}
