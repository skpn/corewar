/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_tables_funcs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 09:51:54 by skpn              #+#    #+#             */
/*   Updated: 2020/04/07 16:16:29 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** these functions are assigned to the table's function pointers and are
** used internally in hash tables functions
**
** you can modify the element's hashing, freeing and printing patterns directly
** in this file, or reassign your own functions to the table's function pointer
** variables (you may have to modify the header file's typedefs to match your
** function prototypes)
*/

unsigned	ft_h_func_hash(void *void_key)
{
	unsigned	hash;
	char		*key;

	hash = 0;
	key = (char *)void_key;
	while (*key)
	{
		hash = hash * 97 + *key;
		++key;
	}
	return (hash);
}

int		ft_h_func_print(t_h_elem *elem)
{
	ft_printf("%p\n", elem->content);
	return (EXIT_SUCCESS);
}

void	ft_h_func_free(t_h_elem *elem)
{
	gc_free((void **)&elem->content);
}
