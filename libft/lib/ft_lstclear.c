/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:51:15 by smaccary          #+#    #+#             */
/*   Updated: 2019/11/17 16:53:52 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	if (!lst)
		return ;
	if (*lst && del)
	{
		next = (*lst)->next;
		while (next)
		{
			next = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = next;
		}
	}
	lst = NULL;
}
