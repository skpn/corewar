/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 11:39:46 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/17 12:15:09 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strncpy(char *dst, char *src, size_t len)
{
	long	*long_src;
	long	*long_dst;
	char	*end;
	size_t	ret;

	ret = len;
	long_src = (long *)src;
	long_dst = (long *)dst;
	while (len >= 8 && !(!(char)(*long_src) || !(char)(*long_src >> 8)
		|| !(char)(*long_src >> 16) || !(char)(*long_src >> 24)
		|| !(char)(*long_src >> 32) || !(char)(*long_src >> 40)
		|| !(char)(*long_src >> 48) || !(char)(*long_src >> 56)))
	{
		*long_dst++ = *long_src++;
		len -= 8;
	}
	end = (char *)long_dst;
	src = (char *)long_src;
	while (len-- && *src)
		*end++ = *src++;
	ret -= len;
	while (len--)
		*end++ = 0;
	return (ret);
}
