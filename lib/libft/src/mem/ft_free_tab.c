/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 14:44:35 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/04 11:00:07 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_free_tab(void **tab, size_t len)
{
	unsigned int	pos;

	if (!tab)
		return (0);
	pos = 0;
	while (pos < len)
	{
		if (tab[pos])
			gc_free((void **)tab[pos]);
		tab[pos] = NULL;
		pos++;
	}
	gc_free((void **)tab);
	tab = NULL;
	return (pos);
}
