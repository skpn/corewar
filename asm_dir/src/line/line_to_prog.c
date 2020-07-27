/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_prog.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 11:28:13 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/21 21:00:39 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_asm.h"
#include <unistd.h>
#include <fcntl.h>

/*
** a line can be empty, contain only a label, or contain a label and/or an
** instruction and its arguments ; label are only used as pointers to a position
** in the program, but instructions, encoding bytes and arguments have
** corresponding numerical values that must be encoded in the program buffer
*/

/*
** the encoding byte's first three bit pairs can be used to indicate argument
** types: 11 is an indirect, 10 is a direct, 01 is a register; we use binary
** shifts and binary OR operations to encode the bit pairs;
*/

void	write_encoding_byte(t_cwr *cwr, t_line *line)
{
	int bit_pair;

	bit_pair = 0;
	while (bit_pair < 3)
	{
		if (line->arg_type[bit_pair] == T_IND)
			line->encoding_byte |= 0b11;
		else if (line->arg_type[bit_pair] == T_DIR)
			line->encoding_byte |= 0b10;
		else if (line->arg_type[bit_pair] == T_REG)
			line->encoding_byte |= 0b01;
		line->encoding_byte <<= 2;
		++bit_pair;
	}
	cwr->prog[cwr->prog_pos++] = (char)line->encoding_byte;
}

/*
** we write the argument backwards from its last byte by casting it as a char
** and use binary shifts to access the correct byte for the int variable
*/

int		write_args(t_cwr *cwr, t_line *line, unsigned arg)
{
	int		arg_size;
	int		arg_end;
	char	content;

	arg_size = line->token[line->arg_index_token[arg]].byte_size;
	arg_end = (arg_size + cwr->prog_pos) - 1;
	if (arg_end > CHAMP_MAX_SIZE)
		return (cwr_error(cwr, "program too long:", CWR_ERR_LINE));
	while (arg_end >= cwr->prog_pos)
	{
		content = (char)line->arg[arg];
		cwr->prog[arg_end] = (char)content;
		line->arg[arg] >>= 8;
		--arg_end;
	}
	cwr->prog_pos += arg_size;
	return (EXIT_SUCCESS);
}

/*
** before writing the opcode, there must be at least two bytes left, one for the
** opcode and one for a single byte argument (all instructions have at least
** one argument of at least one byte);
** before writing the arguments we check again in case the byte after the opcode
** was used for an encoding byte
*/

int		line_to_prog(t_cwr *cwr, t_line *line)
{
	int		arg;

	arg = 0;
	if (line->rules == NULL)
		return (EXIT_SUCCESS);
	if (cwr->prog_pos + 2 > CHAMP_MAX_SIZE)
		return (cwr_error(cwr, "program too long:", CWR_ERR_LINE));
	cwr->prog[cwr->prog_pos++] = (char)line->op_code;
	if (line->rules->encoding_byte != 0)
		write_encoding_byte(cwr, line);
	while (arg < line->arg_nb)
	{
		if (write_args(cwr, line, arg) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		++arg;
	}
	return (EXIT_SUCCESS);
}
