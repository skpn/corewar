/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moving_atoi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 12:22:31 by sikpenou          #+#    #+#             */
/*   Updated: 2020/03/07 12:24:02 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi_deref(char **str)
{
	int				flip;
	int				nb;
	const char		*src;

	src = *str;
	nb = 0;
	while (ft_isspace(*src) && *src != '-' && *src != '+' && *src)
		src++;
	flip = *src == '-' ? -1 : 1;
	src = *src == '-' || *src == '+' ? src + 1 : src;
	while (*src >= '0' && *src <= '9')
	{
		nb = nb * 10 + *src - 48;
		src++;
	}
	*str = src;
	return (nb * flip);
}
