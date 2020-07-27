/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charge_players.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 18:45:00 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/24 23:45:28 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"
#include <unistd.h>

t_player	*get_player(t_vm *vm, t_process *process)
{
	unsigned	nb_player;

	nb_player = reg_to_long_unsigned(process->reg_tab[0]);
	nb_player *= ZAZ_MODE;
	if (nb_player > MAX_PLAYERS)
		return (NULL);
	return (&vm->player[nb_player]);
}

void		set_player_tab(t_vm *vm)
{
	unsigned	pos;
	unsigned	new_pos;

	pos = MAX_PLAYERS;
	while (++pos <= MAX_PLAYERS + vm->nb_players)
	{
		if (vm->player[pos].id)
		{
			new_pos = 1;
			while (vm->player[new_pos].id)
				new_pos++;
			ft_memcpy(vm->player + new_pos, vm->player + pos, sizeof(t_player));
		}
	}
	pos = 1;
	while (++pos <= MAX_PLAYERS + vm->nb_players)
	{
		if (vm->player[pos].id && !vm->player[pos - 1].id)
		{
			new_pos = 1;
			while (vm->player[new_pos].id)
				new_pos++;
			ft_memcpy(vm->player + new_pos, vm->player + pos, sizeof(t_player));
		}
	}
}

int			charge_player(t_vm *vm, t_player *player, size_t pos)
{
	t_process	*process;

	ft_memcpy(vm->arena + pos, player->prog, player->prog_size);
	if ((add_process(vm, pos)) != EXIT_SUCCESS)
		return (ft_error("Malloc error\n"));
	process = vm->processes->first->content;
	long_unsigned_to_reg(process->reg_tab[0], player->id);
	return (EXIT_SUCCESS);
}

int			charge_players(t_vm *vm)
{
	size_t		distance;
	size_t		pos;
	unsigned	charged;

	set_player_tab(vm);
	distance = MEM_SIZE / vm->nb_players;
	charged = 1;
	pos = 0;
	if (!(vm->processes = ft_lstnew_head()))
		return (ft_error("Malloc error\n"));
	while (charged <= vm->nb_players)
	{
		vm->player[charged].id = charged * ZAZ_MODE;
		if (charge_player(vm, &vm->player[charged], pos) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		pos += distance;
		++charged;
	}
	vm->winner = vm->player[charged - 1].id;
	return (EXIT_SUCCESS);
}
