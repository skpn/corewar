/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_heap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 09:22:09 by skpn              #+#    #+#             */
/*   Updated: 2020/02/27 18:52:12 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	return_len(long val, size_t dist)
{
	if (!((char)(val)))
		return (dist);
	else if (!((char)(val >> 8)))
		return (dist + 1);
	else if (!((char)(val >> 16)))
		return (dist + 2);
	else if (!((char)(val >> 24)))
		return (dist + 3);
	else if (!((char)(val >> 32)))
		return (dist + 4);
	else if (!((char)(val >> 40)))
		return (dist + 5);
	else if (!((char)(val >> 48)))
		return (dist + 6);
	else
		return (dist + 7);
}

size_t	ft_strlen_heap(char *str)
{
	long	*long_str;
	long	val;

	if (sizeof(str) != 8)
		return (sizeof(str));
	long_str = (long *)str;
	while ((val = *long_str) && (char)(val) && (char)(val >> 8)
		&& (char)(val >> 16) && (char)(val >> 24) && (char)(val >> 32)
		&& (char)(val >> 40) && (char)(val >> 48) && (char)(val >> 56))
		long_str++;
	return (return_len(val, (char *)long_str - str));
}
