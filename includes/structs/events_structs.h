/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_structs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 15:48:48 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/18 15:50:50 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_STRUCTS_H
 #define EVENTS_STRUCTS_H
 #include <time.h>

typedef struct  s_keys
{
	int         keycode;
	time_t      time;
}               t_keys;

#endif