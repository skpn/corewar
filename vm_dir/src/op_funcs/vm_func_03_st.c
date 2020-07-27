/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_func_03_st.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 11:14:20 by sikpenou          #+#    #+#             */
/*   Updated: 2020/02/26 18:21:37 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

/*
** Usage : st S(RG), D(RG/ID)
** Transfert direct Registre > RAM / Registre.
** Charge le contenu du registre passé en premier parametre
** dans le second parametre.
*/

void	convert_args_st(t_vm *vm, t_process *process)
{
	vm->op.arg[0] = reg_to_long_unsigned(process->reg_tab[vm->op.arg[0]]);
	if (vm->op.arg_type[1] == T_IND)
	{
		get_address(&vm->op.arg[1]);
	}
}

void	log_op_st(t_vm *vm, t_process *process)
{
	short	addr;

	if (!vm->visu && vm->log & LOG_OP)
	{
		addr = (short)vm->op.arg_raw[1];
		ft_printf("P %4d | %s r%d %hd\n", process->id, vm->op.ref->name,
			(int)vm->op.arg_raw[0], addr);
	}
}

int		vm_func_st(t_vm *vm, t_process *process)
{
	convert_args_st(vm, process);
	if (vm->op.arg_type[1] == T_REG)
		long_unsigned_to_reg(process->reg_tab[vm->op.arg[1]], vm->op.arg[0]);
	else
	{
		vm->op.tmp_pc = process->pc;
		move_pc(&vm->op.tmp_pc, vm->op.arg[1]);
		long_unsigned_to_arena(vm, vm->op.tmp_pc, vm->op.arg[0]
			, vm->op_tab[vm->op.code].dir_size);
	}
	log_op_st(vm, process);
	return (EXIT_SUCCESS);
}
