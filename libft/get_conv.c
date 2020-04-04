/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 04:02:15 by smaccary          #+#    #+#             */
/*   Updated: 2020/02/15 15:11:22 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*get_conv(char *format)
{
	while (*format && !ft_strchr(CONV_TYPES, *format))
		format++;
	return ((*format) ? format : format - 1);
}

char	*get_format(char *format)
{
	while (*format && *format != '%')
		format++;
	return (format);
}
