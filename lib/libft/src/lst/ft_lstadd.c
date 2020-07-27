/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:03:41 by sikpenou          #+#    #+#             */
/*   Updated: 2020/03/27 13:49:37 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_head *head, t_lst *new_link)
{
	head->size++;
	new_link->next = head->first;
	head->first = new_link;
	if (new_link->next)
	{
		new_link->next->prev = new_link;
	}
	else
	{
		head->last = new_link;
	}
}
