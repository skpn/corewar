/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_tables_display.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 14:47:51 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/07 12:38:53 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** this is a small set of simple display functions
*/

void	h_print_elem(t_h_table *table, t_h_elem *elem)
{
	ft_printf("PRINTING ELEM %p\nhash :%p\nindex:%p\nkey  : '%s'\n",
		elem, elem->hash, elem->index, elem->key);
	table->func_print(elem);
}

void	h_print_index(t_h_table *table, unsigned index, int opt)
{
	t_lst	*index_lst;

	ft_printf("PRINTING INDEX %u\n", index);
	if (index >= table->size)
		ft_printf("index too high (size: %u, index: %u)\n", table->size, index);
	else if ((index_lst = table->array[index].first))
	{
		while (index_lst)
		{
			table->func_print(index_lst->content);
			index_lst = index_lst->next;
		}
	}
	else if (opt == VERBOSE)
		ft_printf("index empty\n");
	ft_printf("\n");
}

void	h_print_table(t_h_table *table, int opt)
{
	unsigned	index;

	h_print_table_data(table);
	index = -1;
	while (++index < table->size)
		h_print_index(table, index, opt);
}

void	h_print_table_data(t_h_table *table)
{
	ft_printf("PRINTING HASH TABLE %p\nsize : %u\nelems: %u\ncoll : %u\n"
		"limit: %u\n", table, table->size, table->elems, table->collisions
		, table->collisions_limit);
}
