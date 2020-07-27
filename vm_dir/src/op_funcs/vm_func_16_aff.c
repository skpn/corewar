/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_func_16_aff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 11:22:43 by sikpenou          #+#    #+#             */
/*   Updated: 2020/02/26 18:02:25 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"
#include <unistd.h>

/*
** Usage : aff S(RG)
** Affiche a l'ecran le char correspondant a la valeure du registre passé en
** parametre, modulo 256. Si ce char est NUL, alors le carry passe a l'etat
** 1, sinon a l'état 0.
*/

void	log_op_aff(t_vm *vm, char c)
{
	if (!vm->visu)
	{
		ft_printf("Aff: %c\n", c);
	}
}

void	convert_args_aff(t_vm *vm, t_process *process)
{
	(void)process;
	vm->op.arg[0] = reg_to_long_unsigned(process->reg_tab[vm->op.arg[0]]);
}

int		vm_func_aff(t_vm *vm, t_process *process)
{
	char	c;

	convert_args_aff(vm, process);
	c = vm->op.arg[0];
	if (vm->aff)
		log_op_aff(vm, c);
	return (EXIT_SUCCESS);
}
