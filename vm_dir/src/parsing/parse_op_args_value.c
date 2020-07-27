/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_op_args_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:27:56 by sikpenou          #+#    #+#             */
/*   Updated: 2020/02/27 17:25:52 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

int		get_raw_value(t_vm *vm, t_vm_op *op, unsigned arg)
{
	unsigned	size;
	unsigned	oct;

	if (!(size = get_size(op, arg)))
		return (EXIT_FAILURE);
	oct = 0;
	op->arg_raw[arg] = 0;
	while (oct < size)
	{
		op->arg_raw[arg] <<= 8;
		op->arg_raw[arg] |= (unsigned char)vm->arena[op->tmp_pc];
		move_pc(&op->tmp_pc, 1);
		++oct;
	}
	op->arg[arg] = op->arg_raw[arg];
	if (op->arg_type[arg] == T_REG)
	{
		if (--op->arg[arg] >= REG_NUMBER)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int		get_args_value(t_vm *vm, t_vm_op *op)
{
	unsigned		arg;

	arg = 0;
	while (arg < op->ref->nb_args)
	{
		if (get_raw_value(vm, op, arg) != EXIT_SUCCESS)
		{
			return (EXIT_FAILURE);
		}
		arg++;
	}
	return (EXIT_SUCCESS);
}
