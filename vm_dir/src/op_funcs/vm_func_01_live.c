/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_func_01_live.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 11:12:59 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/24 23:08:17 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

/*
** Usage : live S(D4)
** Rapporte le joueur designé par le premier parametre comme etant en vie.
** L'instruction ecrit sur la sortie standard un message du type
** "Le joueur $player_name ($player_id), a été rapporté comme étant en vie".
** Un joueur ne vie que tant qu'au moins un processus effectue un live avec
** son id, et ce au minimun une fois tout les CYCLE_TO_DIE.
** Si le parametre passé ne correspond a l'id d'aucun joueurs,
** l'instruction ne fait rien et on passe a la suite.
*/

void	log_op_live(t_vm *vm, t_process *process)
{
	if (!vm->visu && vm->log & LOG_OP)
	{
		ft_printf("P %4d | %s %d\n", process->id, vm->op.ref->name,
			vm->op.arg_raw[0]);
	}
}

int		vm_func_live(t_vm *vm, t_process *process)
{
	process->is_alive = 1;
	process->last_live_cycle = vm->cycle;
	vm->lives++;
	vm->op.arg[0] *= ZAZ_MODE;
	log_op_live(vm, process);
	if (vm->op.arg[0] <= vm->nb_players && vm->op.arg[0] != 0)
	{
		vm->winner = vm->player[vm->op.arg[0]].id;
		log_live(vm, &vm->player[vm->op.arg[0]]);
	}
	return (EXIT_SUCCESS);
}
