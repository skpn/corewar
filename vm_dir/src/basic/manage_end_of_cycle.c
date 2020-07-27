/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_end_of_cycle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 14:44:36 by sikpenou          #+#    #+#             */
/*   Updated: 2020/02/26 22:23:26 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"
#include <unistd.h>

void	dump_memory(t_vm *vm)
{
	vm->cycles_since_dump = 0;
	update_dump(vm);
	write(1, vm->dump->buf, vm->dump->size);
}

void	pop_dead_processes(t_vm *vm)
{
	t_lst		*process_lst;
	t_lst		*tmp_elem;
	t_process	*process;

	process_lst = vm->processes->first;
	while (process_lst)
	{
		process = process_lst->content;
		tmp_elem = process_lst;
		process_lst = process_lst->next;
		if (!process->is_alive || vm->cycles_to_die < 1)
		{
			log_death(vm, process);
			ft_lstpop_elem(vm->processes, tmp_elem);
			ft_lstfree_elem(&tmp_elem, FREE_BOTH);
		}
		else
			process->is_alive = 0;
	}
}

void	manage_end_of_cycle(t_vm *vm)
{
	if (++vm->cycles_since_check == (unsigned)vm->cycles_to_die
		|| vm->cycles_to_die < 1)
	{
		pop_dead_processes(vm);
		vm->cycles_since_check = 0;
		if (vm->lives >= NBR_LIVE || ++vm->checks == MAX_CHECKS)
		{
			vm->cycles_to_die -= CYCLE_DELTA;
			log_cycles_to_die(vm);
			vm->checks = 0;
		}
		vm->lives = 0;
	}
}
