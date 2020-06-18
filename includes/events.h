/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 14:52:42 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/18 17:15:33 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
 #define EVENTS_H
 
 #include "structs/structs.h"
 #include "settings.h"
 #include "frontend.h"

 #define T_BUFF_SIZE		8
 #define S_BUFF_SIZE		1

 #define FORWARD_KEY		122
 #define BACKWARD_KEY		115
 #define LEFT_KEY			113
 #define RIGHT_KEY			100
 #define CTRL_KEY			65507
 #define ALT_KEY			65513
 #define C_KEY				99
 
/*
** BACKEND 
*/

t_keys	*key_chr(t_keys *arr, int keycode, size_t size);


/*
** EVENT HANDLERS 
*/

int		keyboard_handler(t_vars *vars);
void    hooks(t_vars *vars);
int		loop_handler(t_vars *vars);
int		key_handler(int keycode, t_vars *vars);
int		mouse_handler(int button, int x, int y, t_vars *vars);
int		move_handler(void);
int		resize_handler(void);
int		enter_handler(void);
int		leave_handler(void);
int		release_handler(int keycode, t_vars *vars);
#endif