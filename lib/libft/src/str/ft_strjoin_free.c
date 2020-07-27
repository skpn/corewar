/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 09:55:08 by skpn              #+#    #+#             */
/*   Updated: 2020/02/11 09:55:13 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin_free(char **s1, char **s2, int opt)
{
	int		len1;
	int		len2;
	char	*new;

	new = NULL;
	if (*s1 && *s2)
	{
		len1 = ft_strlen_heap(*s1);
		len2 = ft_strlen_heap(*s2);
		if (!(new = (char *)malloc(len1 + len2 + 1)))
			return (NULL);
		ft_strcpy_heap(new, *s1);
		ft_strcpy_heap(new + len1, *s2);
	}
	else if (*s1 || *s2)
		new = ft_strdup(*s1 ? *s1 : *s2);
	opt == BOTH || opt == LEFT ? ft_free((void **)s1) : 0;
	opt == BOTH || opt == RIGHT ? ft_free((void **)s2) : 0;
	return (new);
}
