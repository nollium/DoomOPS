/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printconv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:06:07 by smaccary          #+#    #+#             */
/*   Updated: 2020/02/24 15:18:30 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdio.h>
#include <stdarg.h>

static int	print_p(void *ptr, t_infos infos)
{
	infos.printer(1, "0x", 2);
	return (ft_putnbr_base_u((size_t)ptr, HEX_BASE_LOW, infos.printer) + 2);
}

static int	print_s(char *str, t_infos infos)
{
	size_t	len;

	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	return (infos.printer(1, str,
		((int)len < infos.trunc || !infos.dot) ? len : infos.trunc));
}

static int	print_conv_2(char c, va_list *list, t_infos infos)
{
	int printed;

	printed = 0;
	if (c == 'p')
		printed += print_p((void *)va_arg(*list, void *), infos);
	if (c == 'd' || c == 'i')
		printed += ft_putnbr_base_int((long long)va_arg(*list, int),
			DEC_BASE, infos.printer);
	else if (c == 'u')
		printed += ft_putnbr_base_u(
			(unsigned int)va_arg(*list, unsigned int), DEC_BASE, infos.printer);
	else if (c == 'x')
		printed += ft_putnbr_base_u(
			(size_t)va_arg(*list, unsigned int), HEX_BASE_LOW, infos.printer);
	else if (c == 'X')
		printed += ft_putnbr_base_u(
			(size_t)va_arg(*list, unsigned int), HEX_BASE_UP, infos.printer);
	return (printed);
}

int			print_conv(t_infos infos, va_list *list)
{
	if (!ft_strchr(CONV_TYPES, infos.conv) && infos.conv != '%')
		return (0);
	if (infos.conv == 'c')
		return (my_putchar((char)va_arg(*list, int), infos.printer));
	else if (infos.conv == 's')
		return (print_s((char *)va_arg(*list, char *), infos));
	else if (infos.conv == '%')
		return (infos.printer(1, "%", 1));
	else
		return (print_conv_2(infos.conv, list, infos));
}
