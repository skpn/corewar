/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   address_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:57:14 by sikpenou          #+#    #+#             */
/*   Updated: 2020/02/26 22:23:38 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

void	convert_ind_to_dir(t_vm *vm, t_process *process, unsigned *ind)
{
	short		ind_pc;
	unsigned	oct;

	ind_pc = process->pc;
	move_pc(&ind_pc, *ind);
	oct = 0;
	*ind = 0;
	while (oct < 4)
	{
		*ind <<= 8;
		*ind |= (unsigned char)vm->arena[ind_pc];
		move_pc(&ind_pc, 1);
		oct++;
	}
}

void	move_pc(short *pc, unsigned len)
{
	*pc += len;
	*pc %= MEM_SIZE;
	if (*pc < 0)
	{
		*pc = MEM_SIZE + *pc;
	}
}

void	get_address(unsigned *arg)
{
	*arg = (short)*arg % MEM_SIZE;
	if ((short)*arg <= -IDX_MOD || (short)*arg >= IDX_MOD)
		*arg = (short)*arg % IDX_MOD;
}
