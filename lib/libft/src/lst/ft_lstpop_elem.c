/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 14:19:29 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/22 14:36:43 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	isolate_lst_elem(t_lst *elem)
{
	elem->next = NULL;
	elem->prev = NULL;
}

void	pop_lst_elem(t_head *head, t_lst *elem)
{
	if (head->first == elem)
		head->first = elem->next;
	else
		elem->prev->next = elem->next;
	if (head->last == elem)
		head->last = elem->prev;
	else
		elem->next->prev = elem->prev;
}

t_lst	*ft_lstpop_elem(t_head *head, t_lst *elem)
{
	head->size--;
	pop_lst_elem(head, elem);
	isolate_lst_elem(elem);
	return (elem);
}
