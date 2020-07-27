/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_func_15_lfork.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 11:22:26 by sikpenou          #+#    #+#             */
/*   Updated: 2020/02/26 18:05:28 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

/*
** Usage : lfork S(D2)
** Identique a Fork mais sans restriction de l'adressage.
*/

void	log_op_lfork(t_vm *vm, t_process *process)
{
	if (!vm->visu && vm->log & LOG_OP)
	{
		ft_printf("P %4d | %s %hd (%d)\n", process->id, vm->op.ref->name,
			(short)vm->op.arg_raw[0], (short)(process->pc + vm->op.arg[0]));
	}
}

int		vm_func_lfork(t_vm *vm, t_process *process)
{
	t_process	*new_process;

	if (add_process(vm, 0) != EXIT_SUCCESS)
		return (ft_error("Malloc error\n"));
	new_process = vm->processes->first->content;
	ft_memcpy(new_process, process, sizeof(*process));
	new_process->id = vm->last_id_process;
	move_pc(&new_process->pc, vm->op.arg[0]);
	ft_memcpy(new_process->reg_tab, process->reg_tab, sizeof(process->reg_tab));
	log_op_lfork(vm, process);
	return (EXIT_SUCCESS);
}
