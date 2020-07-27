/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy_heap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 09:19:18 by skpn              #+#    #+#             */
/*   Updated: 2020/02/24 19:37:38 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	align_strcpy(char *dst, char *src)
{
	while (*src && (unsigned long)src & 7LU)
		*dst++ = *src++;
}

char	*ft_strcpy_heap(char *dst, char *src)
{
	long	*long_src;
	long	*long_dst;

	align_strcpy(dst, src);
	long_src = (long *)src;
	long_dst = (long *)dst;
	while ((char)(*long_src) && (char)(*long_src >> 8)
		&& (char)(*long_src >> 16) && (char)(*long_src >> 24)
		&& (char)(*long_src >> 32) && (char)(*long_src >> 40)
		&& (char)(*long_src >> 48) && (char)(*long_src >> 56))
	{
		*long_dst++ = *long_src++;
	}
	return (dst);
}
