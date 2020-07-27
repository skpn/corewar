/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_head.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 11:28:08 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/04 10:59:22 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_head	*ft_lstnew_head(void)
{
	t_head	*head;

	if (!(head = (t_head *)gc_malloc(sizeof(*head))))
		return (0);
	return (head);
}
