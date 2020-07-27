/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs_vm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:11:28 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/20 15:07:10 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

int		add_process(t_vm *vm, unsigned pos)
{
	t_process	*process;

	process = (t_process *) gc_malloc(sizeof(*process));
	if (!process)
		return (ft_error("Malloc error\n"));
	if (!(ft_lstadd_new(vm->processes, process)))
		return (ft_error("Malloc error\n"));
	process->id = ++vm->last_id_process;
	process->pc = pos;
	return (EXIT_SUCCESS);
}

void	init_tab_func(t_vm *vm)
{
	vm->func[LIVE] = &vm_func_live;
	vm->func[LD] = &vm_func_ld;
	vm->func[ST] = &vm_func_st;
	vm->func[ADD] = &vm_func_add;
	vm->func[SUB] = &vm_func_sub;
	vm->func[AND] = &vm_func_and;
	vm->func[OR] = &vm_func_or;
	vm->func[XOR] = &vm_func_xor;
	vm->func[ZJMP] = &vm_func_zjmp;
	vm->func[LDI] = &vm_func_ldi;
	vm->func[STI] = &vm_func_sti;
	vm->func[FORK] = &vm_func_fork;
	vm->func[LLD] = &vm_func_lld;
	vm->func[LLDI] = &vm_func_lldi;
	vm->func[LFORK] = &vm_func_lfork;
	vm->func[AFF] = &vm_func_aff;
}

void	init_options_tab(t_vm *vm)
{
	t_options	*option;

	option = vm->option;
	option[NB_OPTIONS].opt_name = "";
	option[NB_OPTIONS].parse_func = &parse_champion;
	option[0].opt_name = "-n";
	option[0].parse_func = &parse_champion;
	option[1].opt_name = "-d";
	option[1].parse_func = &parse_dump_option;
	option[2].opt_name = "-dump";
	option[2].parse_func = &parse_dump_option;
	option[3].opt_name = "-visu";
	option[3].parse_func = &parse_visu_option;
	option[4].opt_name = "-v";
	option[4].parse_func = &parse_verbose_option;
	option[5].opt_name = "-a";
	option[5].parse_func = &parse_aff_option;
}

void	init_op_tab(t_vm *vm)
{
	int		op;

	ft_memset(vm->op_tab, 0, sizeof(vm->op_tab));
	ft_memcpy(&vm->op_tab[1], g_op_tab, sizeof(g_op_tab));
	op = 0;
	while (++op < 17)
		vm->op_tab[op].dir_size = DIR_SIZE / (vm->op_tab[op].dir_size + 1);
}

void	init_structs_vm(t_vm *vm, t_dump *dump)
{
	set_dump(dump);
	vm->dump = dump;
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->dump_cycles = -1;
	init_op_tab(vm);
	init_tab_func(vm);
	init_options_tab(vm);
}
