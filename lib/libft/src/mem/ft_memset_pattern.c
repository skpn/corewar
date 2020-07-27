/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset_pattern.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:50:03 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/18 15:25:32 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset_pattern(void *b, long pattern, size_t len)
{
	long	*zone;
	char	*stop;

	if (!len)
		return (b);
	zone = (long *)b;
	stop = b + len;
	if (len % sizeof(long))
		stop -= sizeof(long);
	if (len >= sizeof(long))
	{
		while (zone < (long *)stop)
		{
			*zone = pattern;
			zone++;
		}
		len &= sizeof(long);
	}
	stop = (char *)b + len;
	while (len--)
		*((char *)zone + len) = *stop--;
	return (b);
}
