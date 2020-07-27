/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 14:54:25 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/21 16:53:19 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_asm.h"

/*
** there can be nothing between the flag and the header element, and the element
** must be delimited with double quotes
*/

int		get_header_elem(t_cwr *cwr, char **header_elem)
{
	char	c;

	skip_space(cwr, FORWARD);
	if ((c = cwr->file[cwr->pos]) != '"')
	{
		return (cwr_error(cwr, "bad char between flag and header element:",
			CWR_ERR_CHR));
	}
	++cwr->pos;
	*header_elem = cwr->cpy + cwr->pos;
	while ((c = cwr->file[cwr->pos]) != 0 && c != '"')
	{
		if (c == '\n')
			update_line_nb(cwr, c);
		else
			++cwr->pos;
	}
	if (c != '"')
		return (cwr_error(cwr, "header element must end with '\"'",
			CWR_ERR_NONE));
	cwr->cpy[cwr->pos] = 0;
	++cwr->pos;
	return (EXIT_SUCCESS);
}

/*
** aside from the flags and header elements, there can only be space and
** comments in the header
*/

void	find_header_flag(t_cwr *cwr)
{
	char	c;

	while ((c = cwr->file[cwr->pos]) != 0
		&& (c == COMMENT_CHAR || ft_isspace(c)))
	{
		if (c == COMMENT_CHAR)
			skip_comment(cwr);
		c = cwr->file[cwr->pos];
		if (c == '\n')
			update_line_nb(cwr, c);
		else
			++cwr->pos;
	}
}

/*
** we first look for the .name and .comment flags, then fill the appropriate
** cwr member
*/

int		find_header_elem(t_cwr *cwr)
{
	find_header_flag(cwr);
	if (!ft_strncmp(cwr->file + cwr->pos, ".name", 5))
	{
		cwr->pos += 5;
		return (get_header_elem(cwr, &cwr->prog_name));
	}
	else if (!ft_strncmp(cwr->file + cwr->pos, ".comment", 8))
	{
		cwr->pos += 8;
		return (get_header_elem(cwr, &cwr->comment));
	}
	else
	{
		return (cwr_error(cwr, "bad char before name/comment flags:",
			CWR_ERR_CHR));
	}
}

/*
** first we find the two header elements, then check their length
*/

int		parse_header(t_cwr *cwr)
{
	int		ret;

	if ((ret = find_header_elem(cwr)) != EXIT_SUCCESS)
		return (ret);
	if ((ret = find_header_elem(cwr)) != EXIT_SUCCESS)
		return (ret);
	if ((cwr->len_prog_name = ft_strlen(cwr->prog_name)) > PROG_NAME_LENGTH)
		return (cwr_error(cwr, "program name too long", CWR_ERR_NO_POS));
	if ((cwr->len_comment = ft_strlen(cwr->comment)) > COMMENT_LENGTH)
		return (cwr_error(cwr, "comment too long", CWR_ERR_NO_POS));
	while (cwr->file[cwr->pos] != '\n')
	{
		if (!ft_isspace(cwr->file[cwr->pos++]))
			return (cwr_error(cwr, "bad char after header:", CWR_ERR_CHR));
	}
	update_line_nb(cwr, '\n');
	return (ret);
}
