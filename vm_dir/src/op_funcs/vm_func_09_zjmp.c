/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_func_09_zjmp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 11:17:35 by sikpenou          #+#    #+#             */
/*   Updated: 2020/02/26 22:24:28 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

/*
** Usage : zjmp S(D2)
** Saute a l'adresse passé en parametre si le carry est a l'etat un.
** L'adresse devient alors celle de la prochaine instruction.
** Si le carry est a l'etat zero, rien ne se passe
** et le flot continue normalement jusqu'a l'instruction suivante.
*/

void	log_op_zjmp(t_vm *vm, t_process *process)
{
	if (!vm->visu && vm->log & LOG_OP)
	{
		ft_printf("P %4d | %s %hd %s\n", process->id, vm->op.ref->name
			, (short)vm->op.arg_raw[0], process->carry == 1 ? "OK" : "FAILED");
	}
}

int		vm_func_zjmp(t_vm *vm, t_process *process)
{
	if (process->carry == 1)
	{
		get_address(&vm->op.arg[0]);
		move_pc(&process->pc, vm->op.arg[0]);
		vm->op.move = 0;
	}
	log_op_zjmp(vm, process);
	return (EXIT_SUCCESS);
}
