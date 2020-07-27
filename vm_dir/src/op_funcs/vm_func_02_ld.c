/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_func_02_ld.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 11:13:17 by sikpenou          #+#    #+#             */
/*   Updated: 2020/02/26 18:21:37 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

/*
** Usage : ld S(ID/D4), D(RG)
** Transfert direct RAM > Registre.
** Charge le premier parametre dans le registre passé en second parametre.
** Si la valeur du premier parametre est egale a zero,
** alors le carry passe a l'etat un, sinon a l'etat zero.
*/

void	convert_args_ld(t_vm *vm, t_process *process)
{
	if (vm->op.arg_type[0] == T_IND)
	{
		get_address(&vm->op.arg[0]);
		convert_ind_to_dir(vm, process, &vm->op.arg[0]);
	}
}

void	log_op_ld(t_vm *vm, t_process *process)
{
	if (!vm->visu && vm->log & LOG_OP)
	{
		ft_printf("P %4d | %s %d r%d\n", process->id, vm->op.ref->name,
			(int)vm->op.arg[0], vm->op.arg_raw[1]);
	}
}

int		vm_func_ld(t_vm *vm, t_process *process)
{
	convert_args_ld(vm, process);
	long_unsigned_to_reg(process->reg_tab[vm->op.arg[1]], vm->op.arg[0]);
	if (vm->op.arg[0] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	log_op_ld(vm, process);
	return (EXIT_SUCCESS);
}
