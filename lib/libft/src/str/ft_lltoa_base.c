/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 15:35:29 by skpn              #+#    #+#             */
/*   Updated: 2020/02/27 18:24:13 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include "libft.h"

unsigned	ft_lltoa_base(long long nb, char *base_to, char result[32])
{
	unsigned	start;

	printf("nb: %lld\n", nb);
	if (nb == LLONG_MIN)
	{
		ft_strcpy(result, "−9223372036854775808");
		return (sizeof("−9223372036854775808"));
	}
	start = 0;
	if (nb < 0)
	{
		nb *= -1;
		result[0] = '-';
		start = 1;
	}
	return (ft_ulltoa_base(nb, base_to, result + start) + start);
}
