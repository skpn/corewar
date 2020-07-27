/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree_elem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 12:00:23 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/04 11:00:07 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstfree_elem(t_lst **elem, int opt)
{
	if (opt == FREE_BOTH || opt == FREE_CONTENT)
		gc_free((void **)&(*elem)->content);
	if (opt == FREE_BOTH || opt == FREE_STRUCT)
		gc_free((void **)elem);
}
