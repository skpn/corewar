/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_cycles_vm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 14:40:51 by sikpenou          #+#    #+#             */
/*   Updated: 2020/02/27 18:47:27 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

void	log_cycles_to_die(t_vm *vm)
{
	if (!vm->visu && vm->log & LOG_CYCLE)
	{
		ft_printf("Cycle to die is now %d\n", vm->cycles_to_die);
	}
}

void	log_cycle(t_vm *vm)
{
	if (!vm->visu && vm->log & LOG_CYCLE)
	{
		ft_printf("It is now cycle %d\n", (int)vm->cycle);
	}
}
