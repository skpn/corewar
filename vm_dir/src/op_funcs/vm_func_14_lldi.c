/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_func_14_lldi.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 11:21:39 by sikpenou          #+#    #+#             */
/*   Updated: 2020/02/26 18:20:38 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

/*
** Usage : lldi S(RG/ID/D2), S(RG/ID/D2), D(RG)
** Identique a Indirect Load mais sans restriction de l'adressage.
*/

void	convert_args_lldi(t_vm *vm, t_process *process)
{
	if (vm->op.arg_type[0] == T_REG)
		vm->op.arg[0] = reg_to_long_unsigned(process->reg_tab[vm->op.arg[0]]);
	else if (vm->op.arg_type[0] == T_DIR)
		vm->op.arg[0] = (short)vm->op.arg[0];
	else if (vm->op.arg_type[0] == T_IND)
	{
		get_address(&vm->op.arg[0]);
		convert_ind_to_dir(vm, process, &vm->op.arg[0]);
	}
	if (vm->op.arg_type[1] == T_REG)
		vm->op.arg[1] = reg_to_long_unsigned(process->reg_tab[vm->op.arg[1]]);
	else if (vm->op.arg_type[1] == T_DIR)
		vm->op.arg[1] = (short)vm->op.arg[1];
	else if (vm->op.arg_type[1] == T_IND)
	{
		get_address(&vm->op.arg[1]);
		convert_ind_to_dir(vm, process, &vm->op.arg[1]);
	}
}

void	log_op_lldi(t_vm *vm, t_process *process, short addr)
{
	(void)addr;
	if (!vm->visu && vm->log & LOG_OP)
	{
		ft_printf("P %4d | %s %d %d r%d\n"
			"       | -> load from %d + %d = %d (with pc %d)\n"
			, process->id, vm->op.ref->name,
			(int)vm->op.arg[0], (int)vm->op.arg[1], vm->op.arg_raw[2],
			vm->op.arg[0], vm->op.arg[1], vm->op.arg[0] + vm->op.arg[1],
			process->pc + vm->op.arg[0] + vm->op.arg[1]);
	}
}

int		vm_func_lldi(t_vm *vm, t_process *process)
{
	short	addr;

	convert_args_lldi(vm, process);
	if (vm->op.arg[2] <= REG_NUMBER)
	{
		addr = process->pc;
		move_pc(&addr, vm->op.arg[0] + vm->op.arg[1]);
		arena_to_reg(vm, addr, process->reg_tab[vm->op.arg[2]]);
		if (reg_to_long_unsigned(process->reg_tab[vm->op.arg[2]]) == 0)
			process->carry = 1;
		else
			process->carry = 0;
		log_op_lldi(vm, process, addr);
	}
	return (EXIT_SUCCESS);
}
