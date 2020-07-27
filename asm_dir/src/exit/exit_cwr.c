/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cwr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 14:08:31 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/21 14:51:32 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_asm.h"

void	free_labels(t_head *labels)
{
	t_head	*refs_head;
	t_lst	*label_lst;
	t_label	*label;

	label_lst = labels->first;
	while (label_lst)
	{
		label = label_lst->content;
		label_lst = label_lst->next;
		refs_head = &label->refs;
		ft_lstfree(&refs_head, FREE_BOTH, LST_KEEP_HEAD);
	}
	ft_lstfree(&labels, FREE_BOTH, LST_KEEP_HEAD);
}

void	exit_cwr(t_cwr *cwr)
{
	free_labels(&cwr->labels);
	if (cwr->file)
		 gc_free((void **)&cwr->file);
	if (cwr->file_cor)
		 gc_free((void **)&cwr->file_cor);
	if (cwr->cpy)
		 gc_free((void **)&cwr->cpy);
}
