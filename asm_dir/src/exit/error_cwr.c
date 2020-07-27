/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cwr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 14:51:45 by skpn              #+#    #+#             */
/*   Updated: 2020/04/25 16:08:03 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_asm.h"

/*
** this file manages error messages
*/

int		usage_cwr_asm(void)
{
	ft_printf("usage: ./asm path/to/file.s\n");
	return (EXIT_FAILURE);
}

/*
** there are four context options that help understand the source of the error:
** whole line (up to end of line), current token, current character, no context
*/

void	set_context(t_cwr *cwr, char **context, int *context_len,
	int context_opt)
{
	t_token		token;

	if (context_opt == CWR_ERR_LINE)
	{
		*context_len = cwr->line_len;
		*context = cwr->file + cwr->line_start;
	}
	else if (context_opt == CWR_ERR_CHR)
	{
		*context_len = 1;
		*context = cwr->file + cwr->pos;
	}
	else if (context_opt == CWR_ERR_TOKEN)
	{
		token = cwr->line->token[cwr->line->token_pos];
		*context_len = token.len;
		*context = token.content;
	}
	else
	{
		*context = "";
		*context_len = 0;
	}
}

int		cwr_error(t_cwr *cwr, char *msg, int context_opt)
{
	char	*context;
	int		context_len;

	set_context(cwr, &context, &context_len, context_opt);
	if (context_opt == CWR_ERR_NO_POS)
		ft_dprintf(2, "error - %s\n", msg, context_len, context);
	else
		ft_dprintf(2, "error at [%d][%d] - %s '%.*s'\n", cwr->line_nb,
			cwr->pos - cwr->line_start + 1, msg, context_len, context);
	return (EXIT_FAILURE);
}
