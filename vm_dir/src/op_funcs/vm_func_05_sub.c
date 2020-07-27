/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_func_05_sub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 11:15:24 by sikpenou          #+#    #+#             */
/*   Updated: 2020/02/26 22:24:36 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

/*
** Usage : sub S(RG), S(RG), D(RG)
** Soustrait le second parametre au premier parametre,
** et stocke le resultat dans le troisieme parametre.
** Si la valeur resultante est egale a zero, alors le carry passe a l'etat un,
** sinon a l'etat zero.
*/

int		vm_func_sub(t_vm *vm, t_process *process)
{
	convert_args_add_sub(vm, process);
	long_unsigned_to_reg(process->reg_tab[vm->op.arg[2]]
		, vm->op.arg[0] - vm->op.arg[1]);
	if (vm->op.arg[0] - vm->op.arg[1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	log_op_add_sub(vm, process);
	return (EXIT_SUCCESS);
}
