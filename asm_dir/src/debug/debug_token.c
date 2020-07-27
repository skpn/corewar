/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 15:42:05 by user42            #+#    #+#             */
/*   Updated: 2020/04/21 17:48:06 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_asm.h"

void	print_token_service(t_token token)
{
	char	*type;

	type = NULL;
	type = "BAD TYPE";
	if (token.type)
	{
		type = token.type == TOKEN_START ? "START" : type;
		type = token.type == TOKEN_INST ? "INST" : type;
		type = token.type == TOKEN_ARG ? "ARG" : type;
		type = token.type == TOKEN_SEP ? "SEP" : type;
		type = token.type == TOKEN_LABEL ? "LABEL" : type;
		type = token.type == TOKEN_LABEL_CHAR ? "LABEL_CHAR" : type;
		type = token.type == TOKEN_END ? "END" : type;
	}
	ft_printf("type: %d (%s)\t", token.type, type);
	ft_printf("Content_pos: %u\t", token.content_pos);
	ft_printf("len: %d\t", token.len);
	ft_printf("byte_size: %d\t", token.type);
	ft_printf("value: %s\t", token.value);
	ft_printf("content: '%.*s'\n", token.len, token.content);
}

void	print_token(t_token token)
{
	if (CWR_DEBUG == 0)
		return ;
	ft_printf("PRINTING TOKEN\n");
	print_token_service(token);
	ft_printf("\n");
	fflush(0);
}

void	print_all_tokens(t_line *line)
{
	unsigned	token_nb;

	if (CWR_DEBUG == 0)
		return ;
	ft_printf("PRINTING ALL TOKENS\n");
	token_nb = line->first_token;
	while (token_nb < TOKEN_MAX)
	{
		ft_printf("TOKEN %u\n", token_nb);
		print_token_service(line->token[token_nb]);
		++token_nb;
	}
	ft_printf("\n");
}
