/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 15:17:52 by smaccary          #+#    #+#             */
/*   Updated: 2020/02/25 15:57:27 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			print_space_str(char c, int size,
ssize_t (*my_write)(int, const void *, size_t))
{
	char	*str;
	int		count;

	if (size <= 0)
		return (0);
	str = malloc(sizeof(char) * size + 1);
	ft_memset(str, c, (size_t)size);
	str[size] = '\0';
	count = my_write(1, str, size);
	free(str);
	return (count);
}

/*
** infos->pos == 'r' if no '-' flag is used
*/

static int	print_right(t_infos *infos, t_infos *infos_cpy,
	va_list *list)
{
	va_list	copy;
	int		count;

	va_copy(copy, *list);
	if (ft_strchr("di", infos->conv) && infos->space == '0'
		&& get_curr_int(list) < 0)
	{
		return (wp_ft_vprintf("-%0*u", infos->printer, infos->width,
				-1 * (int)va_arg(*list, int)));
	}
	if ((infos->width - (count = handler(swp_printer(*infos_cpy, no_write),
		&copy))) > 0)
	{
		count += print_space_str(infos->space, infos->width - count,
			infos->printer);
	}
	handler(*infos_cpy, list);
	va_end(copy);
	return (count);
}

int			print_space(t_infos *infos, va_list *list)
{
	int		count;
	t_infos	infos_cpy;

	infos_cpy = *infos;
	infos_cpy.width = infos_cpy.precision;
	infos_cpy.precision = 0;
	infos_cpy.space = '0';
	infos_cpy.pos = (ft_strchr(NUMERIC_TYPES, infos_cpy.conv))
		? 'r' : infos_cpy.pos;
	*infos = check_infos(*infos, list);
	if (infos->pos == 'l'
		&& (infos->width - (count = handler(infos_cpy, list))) > 0)
		count += print_space_str(' ',
			infos->width - count, infos->printer);
	else if (infos->pos == 'r')
		count = print_right(infos, &infos_cpy, list);
	return (count);
}
