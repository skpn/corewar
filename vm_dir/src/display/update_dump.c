/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_dump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 19:06:06 by sikpenou          #+#    #+#             */
/*   Updated: 2020/02/26 18:43:54 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"
#include <unistd.h>

unsigned	arena_pos_to_dump_pos(t_vm *vm, unsigned arena_pos)
{
	return ((arena_pos / vm->dump->octs_per_line) * vm->dump->line_size
				+ vm->dump->line_start
				+ (arena_pos % vm->dump->octs_per_line) * 3);
}

void		write_to_dump(t_dump *dump, char *oct, unsigned dump_pos
	, unsigned len)
{
	char		*stop;

	stop = oct + len;
	while (oct != stop)
	{
		if (dump->buf[dump_pos + (ZAZ_MODE == -1 ? 1 : 0)] != '\n')
		{
			dump->buf[++dump_pos] = dump->base[(*oct >> 4) & 15];
			dump->buf[++dump_pos] = dump->base[*oct & 15];
			++oct;
			++dump_pos;
		}
		else
		{
			if (dump_pos == dump->size)
			{
				oct -= MEM_SIZE;
				stop -= MEM_SIZE;
				dump_pos = dump->line_start;
			}
			else
				dump_pos += dump->line_start + (ZAZ_MODE == -1 ? 1 : 0);
		}
	}
}

void		update_dump_zone(t_vm *vm, unsigned arena_pos, unsigned update_len)
{
	unsigned	dump_pos;

	dump_pos = arena_pos_to_dump_pos(vm, arena_pos) - 1;
	write_to_dump(vm->dump, vm->arena + arena_pos, dump_pos, update_len);
}

void		print_dump_zone(t_vm *vm, unsigned arena_pos, unsigned print_len)
{
	unsigned	dump_pos;
	unsigned	to_end_of_line;
	unsigned	adv;

	dump_pos = arena_pos_to_dump_pos(vm, arena_pos) - 1;
	write_to_dump(vm->dump, vm->arena + arena_pos, dump_pos, print_len);
	while (print_len)
	{
		to_end_of_line = vm->dump->octs_per_line
			- arena_pos % (vm->dump->octs_per_line);
		if (to_end_of_line > print_len)
			to_end_of_line = print_len;
		adv = write(1, vm->dump->buf + dump_pos, to_end_of_line * 3);
		dump_pos = (dump_pos + adv + 1 + vm->dump->line_start) % vm->dump->size;
		print_len -= to_end_of_line;
		arena_pos += to_end_of_line;
	}
}

void		update_dump(t_vm *vm)
{
	write_to_dump(vm->dump, vm->arena, vm->dump->line_start - 1, MEM_SIZE);
}
