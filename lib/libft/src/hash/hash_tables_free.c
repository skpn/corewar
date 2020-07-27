/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_tables_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 11:35:49 by skpn              #+#    #+#             */
/*   Updated: 2020/04/07 16:06:14 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_h_free_elem(t_h_table *table, t_h_elem **h_elem)
{
	t_lst	*elem_lst;

	// table->func_print(*elem);
	elem_lst = ft_h_pop_elem(table, *h_elem);
	table->func_free(*h_elem);
	if ((*h_elem)->key)
		gc_free((void **)&(*h_elem)->key);
	gc_free((void **)h_elem);
	ft_lstfree_elem(&elem_lst, FREE_STRUCT);
}

void		ft_h_free_elem_by_key(t_h_table *table, char *key)
{
	t_h_elem	*h_elem;

	h_elem = ft_h_get_elem(table, key);
	ft_h_free_elem(table, &h_elem);
}

void		ft_h_free_table(t_h_table *table)
{
	unsigned	index;
	t_head		*index_head;

	index = 0;
	while (index < table->size)
	{
		index_head = &(table->array[index]);
		while (index_head->first)
			ft_h_free_elem(table, (t_h_elem **)&index_head->first->content);
		++index;
	}
	gc_free((void **)&table->array);
	gc_free((void **)&table);
}

