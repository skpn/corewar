/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_skip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 15:53:12 by user42            #+#    #+#             */
/*   Updated: 2020/04/20 17:34:07 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_asm.h"

void	skip_comment(t_cwr *cwr)
{
	char	c;

	while ((c = cwr->file[cwr->pos]) != '\0' && !cwr_eol(c))
		++cwr->pos;
}

/*
** skips space (' ', '\t', '\n', '\r', '\v', '\f') backward or forward
*/

void	skip_space(t_cwr *cwr, int opt)
{
	char	c;

	if (opt == FORWARD)
	{
		while ((c = cwr->file[cwr->pos]) != '\0' && !cwr_eol(c)
			&& ft_isspace(c))
			++cwr->pos;
		if (c == COMMENT_CHAR)
			skip_comment(cwr);
	}
	else if (opt == BACK)
	{
		while (cwr->pos >= 0
			&& !cwr_eol((c = cwr->file[cwr->pos])) && ft_isspace(c))
			--cwr->pos;
	}
}

/*
** skips to an end-of-line or comment character, then comes back to the last
** non-space character
*/

void	skip_to_eol(t_cwr *cwr)
{
	char	c;

	cwr->line_len = 0;
	if ((c = cwr->file[cwr->pos]) == '\0' || cwr_eol(c) || c == COMMENT_CHAR)
		return ;
	while ((c = cwr->file[cwr->pos + 1]) != '\0' && !cwr_eol(c)
		&& c != COMMENT_CHAR)
	{
		++cwr->pos;
	}
	cwr->line_len = cwr->pos + 1 - cwr->line_start;
	while ((c = cwr->file[cwr->pos]) != '\0' && !cwr_eol(c) && ft_isspace(c))
	{
		--cwr->pos;
	}
}
