/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_func_06_and.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 11:15:36 by sikpenou          #+#    #+#             */
/*   Updated: 2020/02/26 22:24:33 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

/*
** Usage : and S(RG/ID/D4), S(RG/ID/D4), D(RG)
** Effectue un AND logique entre les deux premiers paramametres
** et stocke le resultat dans le troisieme parametre.
** Si la valeur resultante est egale a zero, alors le carry passe a l'etat un,
** sinon a l'etat zero.
*/

void	convert_args_and_or_xor(t_vm *vm, t_process *process)
{
	if (vm->op.arg_type[0] == T_REG)
		vm->op.arg[0] = reg_to_long_unsigned(process->reg_tab[vm->op.arg[0]]);
	else if (vm->op.arg_type[0] == T_IND)
	{
		get_address(&vm->op.arg[0]);
		convert_ind_to_dir(vm, process, &vm->op.arg[0]);
	}
	if (vm->op.arg_type[1] == T_REG)
		vm->op.arg[1] = reg_to_long_unsigned(process->reg_tab[vm->op.arg[1]]);
	else if (vm->op.arg_type[1] == T_IND)
	{
		get_address(&vm->op.arg[1]);
		convert_ind_to_dir(vm, process, &vm->op.arg[1]);
	}
}

void	log_op_and_or_xor(t_vm *vm, t_process *process)
{
	if (!vm->visu && vm->log & LOG_OP)
	{
		ft_printf("P %4d | %s %d %d r%d\n", process->id, vm->op.ref->name,
			vm->op.arg[0], vm->op.arg[1], vm->op.arg_raw[2]);
	}
}

int		vm_func_and(t_vm *vm, t_process *process)
{
	convert_args_and_or_xor(vm, process);
	long_unsigned_to_reg(process->reg_tab[vm->op.arg[2]]
		, vm->op.arg[0] & vm->op.arg[1]);
	if ((vm->op.arg[0] & vm->op.arg[1]) == 0)
		process->carry = 1;
	else
		process->carry = 0;
	log_op_and_or_xor(vm, process);
	return (EXIT_SUCCESS);
}
