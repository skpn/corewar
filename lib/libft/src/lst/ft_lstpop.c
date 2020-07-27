/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:06:05 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/22 14:20:42 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstpop(t_head *head, void *match)
{
	t_lst	*elem;

	elem = ft_lstfind(head, match);
	if (!elem)
		return (0);
	return (ft_lstpop_elem(head, elem));
}
