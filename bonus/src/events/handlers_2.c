/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 15:58:15 by user42            #+#    #+#             */
/*   Updated: 2020/07/21 22:59:46 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int		focus_in_handler(t_vars *vars)
{
	vars->redraw = 1;
	vars->win_focus = 1;
	return (0);
}

int		focus_out_handler(t_vars *vars)
{
	vars->win_focus = 0;
	return (0);
}
