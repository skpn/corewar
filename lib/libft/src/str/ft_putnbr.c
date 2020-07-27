/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:57:02 by sikpenou          #+#    #+#             */
/*   Updated: 2020/02/27 18:35:08 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr(long long n)
{
	char	nb_str[21];
	char	*pos;

	*nb_str = 0;
	n ? 0 : (nb_str[20] = '0');
	if (n < 0)
		*nb_str = '-';
	if (n - 1 > n)
	{
		nb_str[20] = n % 10;
		n /= 10;
		pos = nb_str + 19;
	}
	else
		pos = nb_str + 20;
	n = n < 0 ? -n : n;
	while (n)
	{
		*pos = n % 10 + 48;
		n /= 10;
		--pos;
	}
	if (*nb_str != 0)
		*pos = '-';
	write(1, pos, nb_str + 21 - pos);
}
