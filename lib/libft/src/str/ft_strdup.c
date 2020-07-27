/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 14:13:27 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/04 10:59:22 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1) + 1;
	if (!(str = (char*)gc_malloc(sizeof(*str) * len)))
		return (NULL);
	ft_memcpy(str, s1, len);
	return (str);
}
