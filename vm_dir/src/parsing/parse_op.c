/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:15:34 by sikpenou          #+#    #+#             */
/*   Updated: 2020/02/27 17:29:26 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

int		get_type(unsigned char coding_byte)
{
	if ((coding_byte & MASK_INDIRECT) == MASK_INDIRECT)
		return (T_IND);
	else if ((coding_byte & MASK_DIRECT) == MASK_DIRECT)
		return (T_DIR);
	else if ((coding_byte & MASK_REGISTER) == MASK_REGISTER)
		return (T_REG);
	return (0);
}

void	get_args_type(t_vm *vm, t_vm_op *op)
{
	if (op->has_coding_byte)
	{
		op->move++;
		op->coding_byte = vm->arena[op->tmp_pc];
		op->arg_type[0] = get_type(op->coding_byte);
		op->arg_type[1] = get_type(op->coding_byte << 2);
		op->arg_type[2] = get_type(op->coding_byte << 4);
		move_pc(&op->tmp_pc, 1);
	}
	else
		op->arg_type[0] = op->ref->arg_type[0];
}

int		get_size(t_vm_op *op, unsigned arg)
{
	if (op->arg_type[arg] == T_REG)
		return (1);
	else if (op->arg_type[arg] == T_IND)
		return (IND_SIZE);
	else if (op->arg_type[arg] == T_DIR)
		return (op->ref->dir_size);
	else
		return (0);
}

int		check_valid_op_arg(t_vm_op *op)
{
	unsigned	arg;
	unsigned	ret;

	arg = 0;
	ret = EXIT_SUCCESS;
	while (arg < op->ref->nb_args)
	{
		if (!(op->ref->arg_type[arg] & op->arg_type[arg]))
		{
			ret = EXIT_FAILURE;
		}
		op->move += get_size(op, arg);
		arg++;
	}
	return (ret);
}

void	parse_op(t_vm *vm, t_process *process)
{
	vm->op.move = 1;
	vm->op.tmp_pc = process->pc;
	vm->op.code = process->code;
	vm->op.ref = (t_op *)&vm->op_tab[process->code];
	vm->op.has_coding_byte = vm->op.ref->coding_byte;
	move_pc(&vm->op.tmp_pc, 1);
	get_args_type(vm, &vm->op);
	if (check_valid_op_arg(&vm->op) == EXIT_SUCCESS
		&& get_args_value(vm, &vm->op) == EXIT_SUCCESS)
	{
		vm->op.is_valid = 1;
	}
	vm->op.tmp_pc = process->pc;
}
