/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prog.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 18:20:45 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/21 10:08:16 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_asm.h"

/*
** this is the core of the file : here the pseudo assembly code from the .s file
** gets split into tokens (parse_line_tokens), the syntax is checked
** (check_tokens), the tokens are "compiled" to numerical values and they are
** written to the program buffer
*/

int		parse_line(t_cwr *cwr)
{
	ft_memset(cwr->line, 0, sizeof(*cwr->line));
	if (parse_line_tokens(cwr, cwr->line, cwr->line->token) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	else if (check_tokens(cwr, cwr->line) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	else if (get_tokens_contents(cwr, cwr->line) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	else if (line_to_prog(cwr, cwr->line) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
** this function uses end of line as delimiters to parse the .s file line by
** line, first getting the length of the line and then parsing its tokens
** backwards (this simplifies syntax checking a lot) until it reaches the end of 
** the previous line, then moving on to the next line
*/

int		parse_prog(t_cwr *cwr)
{
	while (cwr->pos < cwr->file_len)
	{
		skip_to_eol(cwr);
		if (!cwr_eol(cwr->file[cwr->pos]) && cwr->file[cwr->pos]
			!= COMMENT_CHAR)
		{
			if (parse_line(cwr) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
		}
		if (cwr->line_len != 0)
			cwr->pos += cwr->line_len + 1;
		if (cwr->file[cwr->pos] == COMMENT_CHAR)
			skip_comment(cwr);
		if (cwr->file[cwr->pos] != 0 && !cwr_eol(cwr->file[cwr->pos]))
		{
			return (cwr_error(cwr,
				"wrong pos after go_to_endline / get_tokens", CWR_ERR_NONE));
		}
		update_line_nb(cwr, cwr->file[cwr->pos]);
	}
	return (EXIT_SUCCESS);
}
