/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 09:54:49 by skpn              #+#    #+#             */
/*   Updated: 2020/04/04 10:59:22 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	int		len1;
	int		len2;

	new = NULL;
	if (s1 && s2)
	{
		len1 = ft_strlen((char *)s1);
		len2 = ft_strlen((char *)s2);
		if (!(new = (char *)gc_malloc(sizeof(*new) * (len1 + len2 + 1))))
			return (NULL);
		ft_strcpy(new, (char *)s1);
		ft_strcpy(new + len1, (char *)s2);
	}
	else if (s1 || s2)
	{
		return (ft_strdup(s1 ? s1 : s2));
	}
	return (new);
}
