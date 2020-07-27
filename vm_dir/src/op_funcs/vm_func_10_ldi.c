/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_func_10_ldi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 11:19:01 by sikpenou          #+#    #+#             */
/*   Updated: 2020/02/26 22:24:22 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

/*
** Usage : ldi S(RG/ID/D2), S(ID/D2/RG), D(RG)
** Transfert indirect RAM > Registre. Charge la valeur a l'adresse resultante
** de l'addition des deux premiers paramametres, dans le registre passé en
** troisieme parametre.
*/

void	convert_args_ldi(t_vm *vm, t_process *process)
{
	if (vm->op.arg_type[0] == T_REG)
		vm->op.arg[0] = reg_to_long_unsigned(process->reg_tab[vm->op.arg[0]]);
	else if (vm->op.arg_type[0] == T_IND)
	{
		get_address(&vm->op.arg[0]);
		convert_ind_to_dir(vm, process, &vm->op.arg[0]);
	}
	else if (vm->op.arg_type[0] == T_DIR)
		vm->op.arg[0] = (short)vm->op.arg[0];
	if (vm->op.arg_type[1] == T_IND)
	{
		get_address(&vm->op.arg[1]);
		convert_ind_to_dir(vm, process, &vm->op.arg[1]);
	}
	else if (vm->op.arg_type[1] == T_REG)
		vm->op.arg[1] = reg_to_long_unsigned(process->reg_tab[vm->op.arg[1]]);
	else if (vm->op.arg_type[1] == T_DIR)
		vm->op.arg[1] = (short)vm->op.arg[1];
}

void	log_op_ldi(t_vm *vm, t_process *process, short log_addr)
{
	if (!vm->visu && vm->log & LOG_OP)
	{
		ft_printf("P %4d | %s %d %d r%d\n"
			"       | -> load from %d + %d = %d (with pc and mod %d)\n"
			, process->id, vm->op.ref->name
			, vm->op.arg[0], vm->op.arg[1], vm->op.arg_raw[2]
			, vm->op.arg[0], vm->op.arg[1]
			, (vm->op.arg[0] + vm->op.arg[1]), log_addr + process->pc);
	}
}

int		vm_func_ldi(t_vm *vm, t_process *process)
{
	short	final_addr;
	short	log_addr;

	convert_args_ldi(vm, process);
	final_addr = (int)(vm->op.arg[0] + vm->op.arg[1]) % IDX_MOD;
	log_addr = final_addr;
	move_pc(&final_addr, process->pc);
	arena_to_reg(vm, final_addr, process->reg_tab[vm->op.arg[2]]);
	log_op_ldi(vm, process, log_addr);
	return (EXIT_SUCCESS);
}
