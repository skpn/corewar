/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 14:56:31 by sikpenou          #+#    #+#             */
/*   Updated: 2020/02/27 18:49:23 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_head *head)
{
	int		i;
	t_lst	*elem;

	i = 0;
	ft_printf("--\nlist start\n--\n");
	ft_printf("head: %p, size: %u, first: %p, last: %p\n"
		, head, head->size, head->first, head->last);
	if (!(elem = head->first))
	{
		printf("--\nlist is empty\n--\n");
		return ;
	}
	ft_printf("first->prev: %p - last->next: %p\n--\n"
		, head->first->prev, head->last->next);
	while (elem)
	{
		ft_printf("link %d: %-14p, prev %-14p, content %-14p\n"
			, ++i, elem, elem->prev, elem->content);
		elem = elem->next;
	}
	ft_printf("--\nlist end\n--\n\n");
}
