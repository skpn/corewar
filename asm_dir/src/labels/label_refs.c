/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_refs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 15:36:36 by skpn              #+#    #+#             */
/*   Updated: 2020/04/21 19:30:27 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_asm.h"

/*
** label references are a way to stock a reference until a label is defined ;
** when we find a reference to a label name without label or whose label is
** undefined, we know that this label has not been found yet, so we stock it in
** the label's list of references and fill it out when the label is defined
*/

/*
** at the end of the program, if any reference remains it means it was referring
** to a label that was never found, which is an error (see fill_in_refs below)
*/

int		check_remaining_refs(t_cwr *cwr)
{
	t_lst	*label_lst;
	t_label *label;
	t_token	*token;

	label_lst = cwr->labels.last;
	while (label_lst)
	{
		label = label_lst->content;
		label_lst = label_lst->prev;
		if (label->refs.last)
		{
			cwr->line->token_pos = 0;
			token = &cwr->line->token[cwr->line->token_pos];
			token->content = label->name;
			token->len = ft_strlen(label->name);
			return (cwr_error(cwr, "undefined label for ref: ", CWR_ERR_TOKEN));
		}
	}
	return (EXIT_SUCCESS);
}

/*
** this function iterates over a label's list of references, to calculate their
** distance to the label and writes the value at the program position of the
** reference
*/

void	fill_in_refs(t_cwr *cwr, t_lst *ref_lst, unsigned label_pos)
{
	t_ref	*ref;
	int		*int_value;
	short	*short_value;

	while (ref_lst)
	{
		ref = ref_lst->content;
		ref_lst = ref_lst->next;
		if (ref->type_size == 2)
		{
			short_value = (short *)(cwr->prog + ref->prog_pos);
			*short_value = label_pos - ref->prog_line_start;
		}
		else
		{
			int_value = (int *)(cwr->prog + ref->prog_pos);
			*int_value = label_pos - ref->prog_line_start;
		}
		swap_endian(cwr->prog + ref->prog_pos, ref->type_size);
	}
}

/*
** to add a reference we first get the label it refers to ; if that label has
** a valid position in the program we calculate the distance in bytes bewteen
** the reference and the label and we use it as the argument's value ; else if
** the label has not yet been found and has a position of -1 we allocate a
** reference and add it to the label's list of references
*/

int		add_ref(t_cwr *cwr, int *arg, t_token *token)
{
	t_label	*label;
	t_ref	*ref;

	token->content[token->len] = 0;
	while (token->content[0] == LABEL_CHAR || token->content[0] == DIRECT_CHAR)
		++token->content;
	if (get_label(cwr, &label, token->content) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (label->is_defined)
		*arg = label->prog_pos - cwr->prog_line_start;
	else
	{
		ref = alloc_new_ref(token->byte_size, cwr->prog_line_start,
			cwr->prog_pos);
		if (ref == NULL)
			return (cwr_error(cwr, "could not allocate ref: ", CWR_ERR_TOKEN));
		if (!ft_lstadd_new(&label->refs, ref))
			return (cwr_error(cwr, "could not add ref to label: ",
				CWR_ERR_TOKEN));
	}
	return (EXIT_SUCCESS);
}
