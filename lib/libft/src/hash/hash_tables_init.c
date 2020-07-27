/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_tables_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 14:48:39 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/07 13:05:20 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** the core of the table is an array of t_head structs (not pointers, to avoid
** having to manage each index in memory)
**
** the default key type is string (it must be a valid null-terminated string),
** and a duplicate of the key is made in case the original key is freed at some
** point
*/

int			ft_h_init_table(t_h_table *table)
{
	table->func_hash = &ft_h_func_hash;
	table->func_free = &ft_h_func_free;
	table->func_print = &ft_h_func_print;
	return (ft_h_resize_array(table, H_ARRAY_INITIAL_SIZE));
}

t_h_table	*ft_h_alloc_new_table(void)
{
	return ((t_h_table *)gc_malloc(sizeof(t_h_table)));
}

int			ft_h_init_elem(t_h_table *table, t_h_elem *elem, char *key,
	void *content)
{
	if (!(elem->key = ft_strdup(key)))
		return (EXIT_FAILURE);
	elem->hash = table->func_hash(key);
	elem->index = elem->hash % table->size;
	elem->content = content;
	return (EXIT_SUCCESS);
}

t_h_elem	*ft_h_alloc_new_elem(void)
{
	return ((t_h_elem *)gc_malloc(sizeof(t_h_elem)));
}
