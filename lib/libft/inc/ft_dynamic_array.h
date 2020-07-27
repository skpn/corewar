/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dynamic_array.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 10:57:38 by skpn              #+#    #+#             */
/*   Updated: 2020/04/08 18:35:35 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DYNAMIC_ARRAY_H
# define FT_DYNAMIC_ARRAY_H

# define D_ARRAY_LINE_SIZE 500

#include "libft.h"

typedef int		(*t_func_tabmap)(void **, unsigned);

typedef struct	s_d_array
{
	unsigned	parent_size;
	unsigned	pos;
	void		***parent_array;
}				t_d_array;

unsigned		ft_d_array_add(t_d_array *d_array, void *content);
t_d_array		*ft_d_array_alloc(void);
void			ft_d_array_free(t_d_array **d_array);
void			*ft_d_array_get_by_content(t_d_array *d_array,void *content);
void			*ft_d_array_get_by_index(t_d_array *d_array, unsigned index);

#endif
