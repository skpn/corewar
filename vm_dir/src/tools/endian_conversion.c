/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endian_conversion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 17:43:58 by sikpenou          #+#    #+#             */
/*   Updated: 2020/02/26 18:23:46 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"
#include <stdio.h>

void			long_unsigned_to_arena(t_vm *vm, short pos, long unsigned nb
	, unsigned size)
{
	unsigned	oct;

	oct = size;
	move_pc(&pos, oct);
	while (oct)
	{
		move_pc(&pos, -1);
		vm->arena[pos] = nb >> (8 * (size - oct));
		oct--;
	}
}

void			arena_to_reg(t_vm *vm, short pos, char reg[REG_SIZE])
{
	reg[3] = vm->arena[pos];
	move_pc(&pos, 1);
	reg[2] = vm->arena[pos];
	move_pc(&pos, 1);
	reg[1] = vm->arena[pos];
	move_pc(&pos, 1);
	reg[0] = vm->arena[pos];
}

void			swap_endian(char *nb, unsigned size)
{
	unsigned	pos;
	char		tmp;

	if (!FT_BIG_ENDIAN)
		return ;
	pos = 0;
	while (pos < size / 2)
	{
		tmp = nb[pos];
		nb[pos] = nb[size - pos - 1];
		nb[size - pos - 1] = tmp;
		++pos;
	}
}

long unsigned	reg_to_long_unsigned(char reg[REG_SIZE])
{
	char			*oct;
	long unsigned	ret;

	ret = 0;
	oct = reg + REG_SIZE - 1;
	while (oct >= reg)
	{
		ret = (ret << 8) | (*oct & 0xFF);
		--oct;
	}
	return (ret);
}

void			long_unsigned_to_reg(char reg[REG_SIZE], long unsigned nb)
{
	unsigned	pos;

	pos = 0;
	while (pos < REG_SIZE)
	{
		reg[pos] = nb & 0x000000FF;
		nb >>= 8;
		++pos;
	}
}
