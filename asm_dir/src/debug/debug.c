/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 15:26:13 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/21 17:37:30 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_asm.h"

void	print_hex(char *zone, int len)
{
	int		pos;

	if (CWR_DEBUG == 0)
		return ;
	pos = -1;
	while (++pos < len)
	{
		ft_printf("%.2hhx ", zone[pos]);
		if (!(pos % 8) && pos)
			ft_printf("\n");
	}
}

void	print_labels(t_head labels)
{
	t_lst	*label_lst;
	t_label	*label;

	if (CWR_DEBUG == 0)
		return ;
	ft_printf("PRINTING LABELS\n");
	if (!(label_lst = labels.last))
	{
		ft_printf("no labels\n");
		return ;
	}
	while (label_lst)
	{
		label = label_lst->content;
		label_lst = label_lst->prev;
		ft_printf("label name: %s, prog_pos: %u, nb refs: %u\n", label->name,
			label->prog_pos, label->refs.size);
	}
}

void	print_line(t_line *line)
{
	int		i;

	if (CWR_DEBUG == 0)
		return ;
	i = -1;
	ft_printf("LINE CONTENT \n");
	ft_printf("\ncoding_byte = %hhx\t", line->encoding_byte);
	ft_printf("op_code = %u\t", line->op_code);
	ft_printf("dir_size = %u\t", line->dir_size);
	ft_printf("arg_nb = %u\n", line->arg_nb);
	while (++i < 3)
	{
		ft_printf("arg_type[%d] = %u\t", i, line->arg_type[i]);
		ft_printf("arg[%d] = %d\n", i, line->arg[i]);
	}
	ft_printf("first_token = %u\t", line->first_token);
	ft_printf("token_pos = %d\n", line->token_pos);
}

void	print_rules(t_op *rules)
{
	if (CWR_DEBUG == 0)
		return ;
	ft_printf("RULES OF MY LINE\n");
	ft_printf("\nop ruled: %s\t", rules->name);
	ft_printf("nb_args: %u\t", rules->nb_args);
	ft_printf("code nb: %u\t", rules->code);
	ft_printf("encoding_byte ? ");
	rules->encoding_byte ? ft_printf("Yes\n") : ft_printf("No\n");
}
