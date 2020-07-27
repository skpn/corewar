/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dump.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 12:46:44 by sikpenou          #+#    #+#             */
/*   Updated: 2020/02/26 16:08:59 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"
#include <unistd.h>

void	get_line_numbers_size(t_dump *dump)
{
	size_t	tmp_memsize;

	dump->line_numbers_size = 0;
	tmp_memsize = MEM_SIZE;
	while (tmp_memsize)
	{
		++dump->line_numbers_size;
		tmp_memsize /= 16;
	}
}

void	init_dump_variables(t_dump *dump)
{
	dump->base = BASE_HEX;
	get_line_numbers_size(dump);
	dump->line_start = dump->line_numbers_size + 5;
	dump->octs_per_line = ZAZ_MODE == -1 ? 64 : 32;
	dump->lines = MEM_SIZE / dump->octs_per_line;
	if (MEM_SIZE > dump->octs_per_line - 1)
		dump->line_size = dump->line_start + dump->octs_per_line * 3;
	else
		dump->line_size = dump->line_start + MEM_SIZE * 3;
	dump->line_size += ZAZ_MODE == -1 ? 1 : 0;
	dump->size = dump->line_size * dump->lines;
}

void	set_first_line(t_dump *dump)
{
	unsigned	pos;

	ft_memset(dump->buf, '0', dump->line_size);
	dump->buf[1] = 'x';
	dump->buf[dump->line_numbers_size + 2] = ' ';
	dump->buf[dump->line_numbers_size + 3] = ':';
	pos = dump->line_numbers_size + 4;
	while (pos < dump->line_size)
	{
		dump->buf[pos] = ' ';
		pos += 3;
	}
	dump->buf[dump->line_size - 1] = '\n';
}

void	set_line_numbers(t_dump *dump)
{
	unsigned	line_number;
	unsigned	tmp_line_number;
	unsigned	line;
	unsigned	max_line;
	unsigned	pos;

	max_line = MEM_SIZE / dump->octs_per_line;
	line = 1;
	line_number = dump->octs_per_line;
	while (line < max_line)
	{
		pos = dump->line_numbers_size + 1;
		tmp_line_number = line_number;
		while (tmp_line_number)
		{
			dump->buf[line * dump->line_size + pos] = dump->base[tmp_line_number
				& 15];
			tmp_line_number >>= 4;
			pos--;
		}
		line_number += dump->octs_per_line;
		++line;
	}
}

void	set_dump(t_dump *dump)
{
	unsigned	current_line;

	init_dump_variables(dump);
	set_first_line(dump);
	current_line = dump->lines;
	while (current_line)
	{
		current_line--;
		ft_memcpy(dump->buf + dump->line_size * current_line, dump->buf
			, dump->line_size);
	}
	set_line_numbers(dump);
}
