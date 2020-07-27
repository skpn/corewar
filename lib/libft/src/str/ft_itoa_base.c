/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 16:25:22 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/04 10:59:22 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_itoa_base(long int n, char *base_to)
{
	int		pos;
	char	*res;
	int		blen;

	if (!base_to || (blen = ft_check_base("", base_to)) < 2)
		return (NULL);
	pos = 0;
	while (n / ft_pow(blen, pos) != 0 && pos < blen)
		pos++;
	pos = pos + (n < 1 ? 1 : 0);
	if (!(res = (char *)gc_malloc(sizeof(*res) * (pos + 1))))
		return (NULL);
	res[pos] = '\0';
	res[0] = n < 0 ? '-' : 0;
	res[0] = n ? res[0] : '0';
	while (pos > 0 && n != 0)
	{
		res[pos - 1] = base_to[(n < 0 ? -(n % blen) : n % blen)];
		n /= blen;
		pos--;
	}
	return (res);
}
