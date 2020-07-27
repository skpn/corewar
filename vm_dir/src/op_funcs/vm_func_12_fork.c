/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_func_12_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 11:20:39 by sikpenou          #+#    #+#             */
/*   Updated: 2020/02/26 18:26:29 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

/*
** Usage : fork S(D2)
** Genere un nouveau processus a l'adresse passée en parametre par copie
** du processus appelant. Le nouveau processus garde donc l'etat de tous les
** registres et du carry, seul le PC differe ( sauf dans le cas d'un fork %0)
*/

void	log_op_fork(t_vm *vm, t_process *process)
{
	if (!vm->visu && vm->log & LOG_OP)
	{
		ft_printf("P %4d | %s %hd (%d)\n", process->id, vm->op.ref->name
			, (short)vm->op.arg_raw[0]
			, process->pc + (short)vm->op.arg[0] % IDX_MOD);
	}
}

int		vm_func_fork(t_vm *vm, t_process *process)
{
	t_process	*new_process;
	short		test_short;

	test_short = (short)vm->op.arg[0];
	if (add_process(vm, 0) != EXIT_SUCCESS)
		return (ft_error("Malloc error\n"));
	new_process = vm->processes->first->content;
	ft_memcpy(new_process, process, sizeof(*process));
	new_process->id = vm->last_id_process;
	test_short = (short)vm->op.arg[0] % IDX_MOD;
	move_pc(&new_process->pc, test_short);
	ft_memcpy(new_process->reg_tab, process->reg_tab, sizeof(process->reg_tab));
	log_op_fork(vm, process);
	return (EXIT_SUCCESS);
}
