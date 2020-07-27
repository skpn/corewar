/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 15:33:11 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/25 16:16:45 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

int		usage_cwr_vm(void)
{
	char	*usage;

	usage = "usage: ./vm [options] path/to/file[s].cor\noptions:\n"
		"'-n X'\t : the following fighter will be in position X\n"
		"'-v X'\t : set verbosity level cumulatively: lives 1, cycles 2,\n"
			"\tops 4, deaths 8, PC 16, 31 for ecverything, 29 for\n"
			"\teverything but cycles, 18 for PC and cycles, etc\n"
		"'-dump X': dump after X cycles\n"
		"'-d X'\t : dump then exit after X cycles\n"
		"'-a X'\t : display 'aff' op output\n";
	write(1, usage, ft_strlen(usage));
	return (EXIT_FAILURE);
}

void	exit_vm(t_vm vm)
{
	t_process	*process;
	t_lst		*process_lst;

	if (vm.processes)
	{
		process_lst = vm.processes->first;
		while (process_lst)
		{
			process = process_lst->content;
			process_lst = process_lst->next;
			 gc_free((void **)&process);
		}
		ft_lstfree(&vm.processes, FREE_STRUCT, LST_FREE_HEAD);
	}
}
