/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_func_11_sti.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 11:19:59 by sikpenou          #+#    #+#             */
/*   Updated: 2020/02/26 18:20:49 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

/*
** Usage : sti S(RG), S(RG/ID/D2), S(RG/ID/D2)
** Transfert indirect Registre > RAM.
** Charge la valeur contenue dans le registre passé en premier parametre
** à l'adresse resultante de l'addition des deux derniers parametres.
** Si cette valeur est nulle,
** alors le carry passe a l'etat un, sinon a l'etat zero.
*/

void	convert_args_sti(t_vm *vm, t_process *process)
{
	vm->op.arg[0] = reg_to_long_unsigned(process->reg_tab[vm->op.arg[0]]);
	if (vm->op.arg_type[1] == T_IND)
	{
		get_address(&vm->op.arg[1]);
		convert_ind_to_dir(vm, process, &vm->op.arg[1]);
	}
	else if (vm->op.arg_type[1] == T_REG)
		vm->op.arg[1] = reg_to_long_unsigned(process->reg_tab[vm->op.arg[1]]);
	if (vm->op.arg_type[2] == T_IND)
	{
		get_address(&vm->op.arg[1]);
		convert_ind_to_dir(vm, process, &vm->op.arg[2]);
	}
	else if (vm->op.arg_type[2] == T_REG)
		vm->op.arg[2] = reg_to_long_unsigned(process->reg_tab[vm->op.arg[2]]);
	if (vm->op.arg_type[1] == T_DIR)
		vm->op.arg[1] = (short)vm->op.arg[1];
	if (vm->op.arg_type[2] == T_DIR)
		vm->op.arg[2] = (short)vm->op.arg[2];
}

void	log_op_sti(t_vm *vm, t_process *process, unsigned addr)
{
	if (!vm->visu && vm->log & LOG_OP)
	{
		ft_printf("P %4d | %s r%d %d %d\n"
			"       | -> store to %d + %d = %d (with pc and mod %d)\n"
			, process->id, vm->op.ref->name,
			(short)vm->op.arg_raw[0], vm->op.arg[1], vm->op.arg[2],
			(int)vm->op.arg[1], (int)vm->op.arg[2],
			(int)(vm->op.arg[1] + vm->op.arg[2]), (int)addr);
	}
}

int		vm_func_sti(t_vm *vm, t_process *process)
{
	short	addr;
	int		sum;

	convert_args_sti(vm, process);
	sum = (int)(vm->op.arg[1] + vm->op.arg[2]) % IDX_MOD;
	addr = process->pc + sum;
	long_unsigned_to_arena(vm, addr, vm->op.arg[0], REG_SIZE);
	log_op_sti(vm, process, addr);
	return (EXIT_SUCCESS);
}
