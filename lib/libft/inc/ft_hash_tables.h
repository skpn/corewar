/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_tables.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 12:18:04 by skpn              #+#    #+#             */
/*   Updated: 2020/04/07 16:16:15 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HASH_TABLES_H
# define FT_HASH_TABLES_H

# define H_COLLISIONS_REJECTION_FACTOR 10
# define H_ARRAY_INITIAL_SIZE 4999
# define H_ARRAY_MAX_SIZE 2147483647

#include "ft_lst.h"

typedef struct		s_h_elem
{
	unsigned		hash;
	unsigned		index;
	char			*key;
	void			*content;
}					t_h_elem;

typedef void		(*t_func_h_free)(t_h_elem *);
typedef unsigned	(*t_func_h_hash)(void *);
typedef int			(*t_func_h_iter)(t_h_elem *);
typedef int			(*t_func_h_print)(t_h_elem *);

typedef struct		s_h_table
{
	unsigned		size;
	unsigned		elems;
	unsigned		collisions;
	unsigned		collisions_limit;
	t_func_h_hash	func_hash;
	t_func_h_free	func_free;
	t_func_h_print	func_print;
	t_head			*array;
}					t_h_table;

int					ft_h_add_elem(t_h_table *table, char *key, void *content);
t_h_elem			*ft_h_alloc_new_elem(void);
t_h_table			*ft_h_alloc_new_table(void);

void				ft_h_free_elem(t_h_table *table, t_h_elem **h_elem);
void				ft_h_free_elem_by_key(t_h_table *table, char *key);
void				ft_h_free_table(t_h_table *table);
void				ft_h_func_free(t_h_elem *elem);
unsigned			ft_h_func_hash(void *void_key);
int					ft_h_func_print(t_h_elem *elem);

void				*ft_h_get_content(t_h_table *table, char *key);
t_h_elem			*ft_h_get_elem(t_h_table *table, char *key);

int					ft_h_iter(t_h_table *table, t_func_h_iter iter_func);
int					ft_h_init_table(t_h_table *table);
int					ft_h_init_elem(t_h_table *table, t_h_elem *elem, char *key,
	void *content);

t_lst				*ft_h_pop_elem(t_h_table *table, t_h_elem *pop_elem);
t_lst				*ft_h_pop_elem_by_key(t_h_table *table, char *pop_key);

int					ft_h_resize_array(t_h_table *table,
	unsigned new_size);

void				h_print_index(t_h_table *table, unsigned index, int opt);
void				h_print_table(t_h_table *table, int opt);
void				h_print_table_data(t_h_table *table);

#endif