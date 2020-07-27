/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 12:39:17 by sikpenou          #+#    #+#             */
/*   Updated: 2020/02/27 18:33:20 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int		ft_tabmap(void **tab, unsigned size, t_func_tabmap func)
{
	int		check_ret;

	while (size)
	{
		--size;
		if ((check_ret = func(tab, size)) != EXIT_SUCCESS)
			return (check_ret);
	}
	return (EXIT_SUCCESS);
}
