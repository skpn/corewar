/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 09:45:23 by skpn              #+#    #+#             */
/*   Updated: 2020/02/27 18:21:08 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			get_nb_len_in_base(long long nb, unsigned base_len)
{
	unsigned	nb_len;

	nb_len = 0;
	while (nb >= base_len)
	{
		++nb_len;
		nb /= base_len;
	}
	return (nb_len);
}

unsigned	ft_ulltoa_base(unsigned long long nb, char *base_to, char *result)
{
	unsigned	base_len;
	unsigned	nb_len;
	unsigned	start_pos;

	if (nb == 0)
	{
		ft_strcpy(result, "0");
		return (sizeof("0"));
	}
	base_len = ft_strlen(base_to);
	nb_len = get_nb_len_in_base(nb, base_len);
	start_pos = nb_len;
	while (nb)
	{
		result[start_pos] = base_to[nb % base_len];
		nb /= base_len;
		--start_pos;
	}
	return (nb_len);
}
