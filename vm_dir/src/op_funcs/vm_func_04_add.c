/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_func_04_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 11:14:56 by sikpenou          #+#    #+#             */
/*   Updated: 2020/02/26 18:00:07 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

/*
** Usage : add S(RG), S(RG), D(RG)
** Ajoute le second parametre au premier parametre,
** et stocke le resultat dans le troisieme parametre.
** Si la valeur resultante est égale a zero, alors le carry passe a l'etat un,
** sinon a l'etat zero.
*/

void	convert_args_add_sub(t_vm *vm, t_process *process)
{
	vm->op.arg[0] = reg_to_long_unsigned(process->reg_tab[vm->op.arg[0]]);
	vm->op.arg[1] = reg_to_long_unsigned(process->reg_tab[vm->op.arg[1]]);
}

void	log_op_add_sub(t_vm *vm, t_process *process)
{
	if (!vm->visu && vm->log & LOG_OP)
	{
		ft_printf("P %4d | %s r%d r%d r%d\n", process->id, vm->op.ref->name,
			vm->op.arg_raw[0], vm->op.arg_raw[1], vm->op.arg_raw[2]);
	}
}

int		vm_func_add(t_vm *vm, t_process *process)
{
	convert_args_add_sub(vm, process);
	long_unsigned_to_reg(process->reg_tab[vm->op.arg[2]]
		, vm->op.arg[0] + vm->op.arg[1]);
	if (vm->op.arg[0] + vm->op.arg[1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	log_op_add_sub(vm, process);
	return (EXIT_SUCCESS);
}
