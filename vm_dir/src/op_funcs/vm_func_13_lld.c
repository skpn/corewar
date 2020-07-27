/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_func_13_lld.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 11:21:17 by sikpenou          #+#    #+#             */
/*   Updated: 2020/02/26 18:01:50 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

/*
** Usage : lld S(ID/D4), D(RG)
** Identique a Indirect Load mais sans restriction de l'adressage.
*/

void	convert_args_lld(t_vm *vm, t_process *process)
{
	if (vm->op.arg_type[0] == T_IND)
	{
		convert_ind_to_dir(vm, process, &vm->op.arg[0]);
	}
}

void	log_op_lld(t_vm *vm, t_process *process)
{
	if (!vm->visu && vm->log & LOG_OP)
	{
		ft_printf("P %4d | %s %d r%d\n", process->id, vm->op.ref->name,
			(int)vm->op.arg[0], vm->op.arg_raw[1]);
	}
}

int		vm_func_lld(t_vm *vm, t_process *process)
{
	convert_args_lld(vm, process);
	if (vm->op.arg[1] <= REG_NUMBER)
	{
		long_unsigned_to_reg(process->reg_tab[vm->op.arg[1]]
		, vm->op.arg[0]);
		if (reg_to_long_unsigned(process->reg_tab[vm->op.arg[1]]) == 0)
			process->carry = 1;
		else
			process->carry = 0;
	}
	log_op_lld(vm, process);
	return (EXIT_SUCCESS);
}
