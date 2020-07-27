/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:28:06 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/21 22:11:45 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_asm.h"

/*
** this function reverses a set of bits in memory, to change the endianness of
** the string representation of an integer
*/

void	swap_endian(char *nb, unsigned size)
{
	unsigned	pos;
	char		tmp;

	pos = 0;
	while (pos < size / 2)
	{
		tmp = nb[pos];
		nb[pos] = nb[size - pos - 1];
		nb[size - pos - 1] = tmp;
		++pos;
	}
}

void	update_line_nb(t_cwr *cwr, char c)
{
	if (c == '\n')
		++cwr->line_nb;
	++cwr->pos;
	cwr->line_start = cwr->pos;
	cwr->prog_line_start = cwr->prog_pos;
}

int		cwr_eol(char c)
{
	return (c == '\n');
}
