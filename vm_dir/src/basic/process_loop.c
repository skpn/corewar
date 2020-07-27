/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 17:03:47 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/24 22:10:04 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"
#include <unistd.h>

int		exec_func(t_vm *vm, t_process *process)
{
	int		check_ret;

	parse_op(vm, process);
	process->code = 0;
	if (vm->op.is_valid == 1
		&& (check_ret = vm->func[vm->op.code](vm, process)) != EXIT_SUCCESS)
		return (check_ret);
	log_pc(vm, process);
	move_pc(&process->pc, vm->op.move);
	ft_memset(&vm->op, 0, sizeof(vm->op));
	return (EXIT_SUCCESS);
}

int		exec_process(t_vm *vm, t_process *process)
{
	if (process->wait > 0)
		--process->wait;
	if (process->code == 0)
	{
		if (vm->arena[process->pc] <= NB_FUNCS && vm->arena[process->pc] > 0)
		{
			process->code = vm->arena[process->pc];
			process->wait = vm->op_tab[process->code].wait;
			if (process->wait == 0)
				return (exec_func(vm, process));
			--process->wait;
		}
		else
			move_pc(&process->pc, 1);
	}
	else if (process->wait == 0)
	{
		return (exec_func(vm, process));
	}
	return (EXIT_SUCCESS);
}

int		execute_cycle(t_vm *vm)
{
	t_lst	*process_lst;
	int		check_ret;

	process_lst = vm->processes->first;
	while (process_lst)
	{
		if ((check_ret = exec_process(vm, process_lst->content))
			!= EXIT_SUCCESS)
			return (check_ret);
		process_lst = process_lst->next;
	}
	return (EXIT_SUCCESS);
}

int		process_loop(t_vm *vm)
{
	int		check_ret;

	while (vm->processes->first)
	{
		++vm->cycle;
		++vm->cycles_since_dump;
		if (vm->cycle > vm->dump_cycles)
		{
			dump_memory(vm);
			if (vm->exit_after_dump)
				return (EXIT_SUCCESS);
		}
		log_cycle(vm);
		if ((check_ret = execute_cycle(vm)) != EXIT_SUCCESS)
			return (check_ret);
		manage_end_of_cycle(vm);
	}
	return (EXIT_SUCCESS);
}
