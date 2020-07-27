/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_vm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 14:40:51 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/24 23:44:15 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

void	log_players(t_vm *vm)
{
	unsigned	idx;
	t_player	*player;

	idx = 1;
	player = vm->player;
	if (!vm->visu)
	{
		ft_printf("Introducing contestants...\n");
		while (idx <= vm->nb_players)
		{
			ft_printf("* Player %u, weighing %u bytes, \"%s\" (\"%s\") !\n"
				, idx, player[idx].prog_size, player[idx].name
				, player[idx].comment);
			idx++;
		}
	}
}

void	log_winner(t_vm *vm)
{
	if (!vm->visu && (!vm->exit_after_dump || vm->cycle < vm->dump_cycles))
	{
		ft_printf("Contestant %d, \"%s\", has won !\n", vm->winner * ZAZ_MODE,
			vm->player[vm->winner * ZAZ_MODE].name);
	}
}

void	log_live(t_vm *vm, t_player *player)
{
	if (!vm->visu && vm->log & LOG_LIVE)
	{
		ft_printf("Player %u (%s) is said to be alive\n"
			, player->id * ZAZ_MODE, player->name);
	}
}

void	log_death(t_vm *vm, t_process *process)
{
	if (!vm->visu && vm->log & LOG_DEATH)
	{
		ft_printf("Process %u hasn't lived for %u cycles (CTD %d)\n"
			, process->id, vm->cycle - process->last_live_cycle
			, vm->cycles_to_die);
	}
}

void	log_pc(t_vm *vm, t_process *process)
{
	if (!vm->visu && vm->log & LOG_PC && vm->op.move)
	{
		vm->op.tmp_pc = process->pc;
		vm->op.tmp_pc += vm->op.move;
		ft_printf("ADV %u (0x%.4x -> 0x%.4x)", vm->op.move, process->pc
			, vm->op.tmp_pc);
		print_dump_zone(vm, process->pc, vm->op.move);
		ft_printf(" \n");
	}
}
