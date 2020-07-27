/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:50:03 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/18 15:25:32 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *b, unsigned char c, size_t len)
{
	long	*zone;
	char	*stop;
	long	pattern;

	if (!len)
		return (b);
	zone = (long *)b;
	stop = b + len;
	if (len % sizeof(long))
		stop -= sizeof(long);
	if (len >= sizeof(long))
	{
		pattern = c;
		while (c && !(pattern >> sizeof(long) * 7))
			pattern = (pattern << sizeof(long)) | c;
		while (zone < (long *)stop)
		{
			*zone = pattern;
			zone++;
		}
		len &= sizeof(long) - 1;
	}
	while (len)
		*((char *)zone + --len) = (unsigned char)c;
	return (b);
}
