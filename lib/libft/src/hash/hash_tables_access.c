/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_tables_access.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 14:47:21 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/07 15:06:41 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** these functions can pop an element or its contents, return it, or iter over
** the table
*/

int			ft_h_iter(t_h_table *table, t_func_h_iter iter_func)
{
	unsigned	index;
	t_lst		*index_lst;

	index = 0;
	while (index < table->size)
	{
		if (table->array[index].first)
		{
			index_lst = table->array[index].first;
			while (index_lst)
			{
				if (iter_func(index_lst->content) != EXIT_SUCCESS)
					return (EXIT_FAILURE);
				index_lst = index_lst->next;
			}
		}
		index++;
	}
	return (EXIT_SUCCESS);
}

t_h_elem	*ft_h_get_elem(t_h_table *table, char *key)
{
	unsigned	index;
	t_h_elem	*hash_elem;
	t_lst		*index_lst;

	index = table->func_hash(key) % table->size;
	index_lst = table->array[index].first;
	while (index_lst)
	{
		hash_elem = index_lst->content;
		if (!ft_strcmp(hash_elem->key, key))
			return (hash_elem);
		index_lst = index_lst->next;
	}
	return (NULL);
}

void		*ft_h_get_content(t_h_table *table, char *key)
{
	t_h_elem	*hash_elem;

	hash_elem = ft_h_get_elem(table, key);
	if (hash_elem)
		return (hash_elem->content);
	return (NULL);
}

t_lst	*ft_h_pop_elem(t_h_table *table, t_h_elem *pop_elem)
{
	t_head		*pop_head;

	pop_head = &table->array[pop_elem->hash % table->size];
	if (pop_head->size > 1)
		table->collisions--;
	table->elems--;
	return (ft_lstpop(pop_head, pop_elem));
}

t_lst	*ft_h_pop_elem_by_key(t_h_table *table, char *pop_key)
{
	t_h_elem	*pop_elem;

	if ((pop_elem = ft_h_get_elem(table, pop_key)))
		return (ft_h_pop_elem(table, pop_elem));
	return (NULL);
}
