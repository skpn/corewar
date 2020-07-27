/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_vm_func_or.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 11:16:21 by sikpenou          #+#    #+#             */
/*   Updated: 2020/02/15 10:48:05 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

/*
** Usage : or S(RG/ID/D4), S(RG/ID/D4), D(RG)
** Effectue un OR logique entre les deux premiers paramametres et stocke
** le resultat dans le troisieme paramametre.
** Si la valeur resultante est egale a zero, alors le carry passe a l'etat un,
** sinon a l'etat zero.
*/

int		vm_func_or(t_vm *vm, t_process *process)
{
	convert_args_and_or_xor(vm, process);
	long_unsigned_to_reg(process->reg_tab[vm->op.arg[2]]
		, vm->op.arg[0] | vm->op.arg[1]);
	if ((vm->op.arg[0] | vm->op.arg[1]) == 0)
		process->carry = 1;
	else
		process->carry = 0;
	log_op_and_or_xor(vm, process);
	return (EXIT_SUCCESS);
}
