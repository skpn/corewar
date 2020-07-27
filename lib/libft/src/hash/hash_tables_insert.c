/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_tables_insert.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 14:48:23 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/07 13:01:08 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** this file manages element insertions, and monitors the table's state and
** resizes it if the number of collisions gets too high
** the key for an element must be a string, and if it is malloc'ed it must not
** be freed while the element is part of the table
** you can adjust the collisions rejection factors (the higher you set it, the
** less collisions are accepted) and the initial table size in the libft.h file,
** and resize the table yourself with the ft_h_resize_array function
*/

/*
** this function pops each element from its index's list, and uses its hash to
** add it to the correct new index
** hashes are never erased, so redispatching the elements only takes a modulo
** operation and a list add
*/

static void	transfer_hash_array(t_h_table *table, unsigned new_size
		, unsigned old_size, t_head *old_array)
{
	unsigned	index;
	t_head		*index_head;
	t_head		*rehashed_index_head;
	t_lst		*transfer;
	t_h_elem	*h_elem;

	index = 0;
	while (index < old_size)
	{
		index_head = &(old_array[index]);
		while (index_head->first)
		{
			transfer = ft_lstpop_elem(index_head, index_head->first);
			h_elem = transfer->content;
			h_elem->index = h_elem->hash % new_size;
			rehashed_index_head = &(table->array[h_elem->index]);
			if (rehashed_index_head->size > 0)
				table->collisions++;
			ft_lstadd(rehashed_index_head, transfer);
		}
		++index;
	}
}

int			ft_h_resize_array(t_h_table *table, unsigned new_size)
{
	t_head	*old_array;

	if (new_size >= H_ARRAY_MAX_SIZE)
		return (EXIT_FAILURE);
	old_array = table->array;
	if (!(table->array = (t_head *)gc_malloc(sizeof(t_head) * new_size)))
	{
		table->array = old_array;
		return (EXIT_FAILURE);
	}
	if (old_array)
	{
		table->collisions = 0;
		transfer_hash_array(table, new_size, table->size, old_array);
	}
	gc_free((void **)&old_array);
	table->size = new_size;
	table->collisions_limit = table->size / H_COLLISIONS_REJECTION_FACTOR;
	if (table->collisions_limit < 1)
		table->collisions_limit = 1;
	return (EXIT_SUCCESS);
}

static int	insert_hash_elem(t_h_table *table, t_h_elem *h_elem)
{
	unsigned	new_size;
	t_head		*index_head;

	index_head = &(table->array[h_elem->index]);
	if (!(ft_lstadd_new(index_head, h_elem)))
		return (EXIT_FAILURE);
	if (index_head->size > 1)
	{
		table->collisions++;
		while (table->collisions > table->collisions_limit)
		{
			new_size = ft_find_next_prime(table->size * 3 + 1);
			return (ft_h_resize_array(table, new_size));
		}
	}
	table->elems++;
	return (EXIT_SUCCESS);
}

/*
** if keys are not unique, retrieval of an element via its key is no longer
** possible
*/

static int	key_is_unique(t_lst *index_lst, char *key)
{
	t_h_elem	*h_elem;

	while (index_lst)
	{
		h_elem = index_lst->content;
		if (h_elem->key[0] == key[0] && !ft_strcmp(h_elem->key, key))
			return (EXIT_FAILURE);
		index_lst = index_lst->next;
	}
	return (EXIT_SUCCESS);
}

int			ft_h_add_elem(t_h_table *table, char *key, void *content)
{
	t_h_elem	*h_elem;

	if (!(h_elem = ft_h_alloc_new_elem()))
		return (EXIT_FAILURE);
	if (ft_h_init_elem(table, h_elem, key, content) != EXIT_SUCCESS)
		gc_free((void **)&h_elem);
	else if (key_is_unique(table->array[h_elem->index].first, key)
		!= EXIT_SUCCESS)
		ft_h_free_elem(table, &h_elem);
	else if (insert_hash_elem(table, h_elem) != EXIT_SUCCESS)
		ft_h_free_elem(table, &h_elem);
	else
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
