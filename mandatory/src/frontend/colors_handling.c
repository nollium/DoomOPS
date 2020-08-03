/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 12:58:15 by smaccary          #+#    #+#             */
/*   Updated: 2020/08/04 00:55:10 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frontend.h"

int	add_shade(double shade, int color)
{
	if (0 > shade || color == TRANS_COLOR)
		return (color);
	if (shade >= 1)
		return (0);
	((unsigned char *)&color)[0] *= (1.0 - shade);
	((unsigned char *)&color)[1] *= (1.0 - shade);
	((unsigned char *)&color)[2] *= (1.0 - shade);
	return (color);
}
