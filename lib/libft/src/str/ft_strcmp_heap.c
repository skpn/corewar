/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_heap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 09:23:16 by skpn              #+#    #+#             */
/*   Updated: 2020/02/11 09:23:17 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp_heap(char *s1, char *s2)
{
	long	*long_s1;
	long	*long_s2;

	long_s1 = (long *)s1;
	long_s2 = (long *)s2;
	while (!(*long_s1 ^ *long_s2) && !(!(char)(*long_s1) || !(char)(*long_s2)
		|| !(char)(*long_s1 >> 8) || !(char)(*long_s2 >> 8)
		|| !(char)(*long_s1 >> 16) || !(char)(*long_s2 >> 16)
		|| !(char)(*long_s1 >> 24) || !(char)(*long_s2 >> 24)
		|| !(char)(*long_s1 >> 32) || !(char)(*long_s2 >> 32)
		|| !(char)(*long_s1 >> 40) || !(char)(*long_s2 >> 40)
		|| !(char)(*long_s1 >> 48) || !(char)(*long_s2 >> 48)
		|| !(char)(*long_s1 >> 56) || !(char)(*long_s2 >> 56)))
	{
		long_s1++;
		long_s2++;
	}
	s1 = (char *)long_s1;
	s2 = (char *)long_s2;
	while (*s1 && *s2 && !(*s1 ^ *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
