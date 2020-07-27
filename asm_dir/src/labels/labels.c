/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 11:31:56 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/21 19:26:51 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_asm.h"

/*
** a label is a pointer to a point in the program ; it can be defined, and its
** position in the program will be marked down at that time, or referred to in
** an instruction argument;
** when referring to a label the value of the argument will be the distance
** in bytes between the argument's program position, and the label's program
** position;
** if the referred label is not defined, a gap will be left in the program and a
** reference will be added to the label's references list; if the label has not
** yet been allocated it will be allocated and left undefined 
*/

t_label	*find_label(t_lst *label_lst, char *label_name)
{
	while (label_lst)
	{
		if (!ft_strcmp(((t_label *)label_lst->content)->name, label_name))
			return (label_lst->content);
		label_lst = label_lst->next;
	}
	return (NULL);
}

/*
** if we can find an existing label with the researched name, we point *label to
** it ; otherwise we allocate one, point *label to it and add it to the list 
*/

int		get_label(t_cwr *cwr, t_label **label, char *label_name)
{
	*label = find_label(cwr->labels.first, label_name);
	if (*label != NULL)
		return (EXIT_SUCCESS);
	else if (!(*label = alloc_new_label(label_name)))
		return (cwr_error(cwr, "could not allocate label: ", CWR_ERR_TOKEN));
	else if (!ft_lstadd_new(&cwr->labels, *label))
		return (cwr_error(cwr, "could not add label to list: ", CWR_ERR_TOKEN));
	return (EXIT_SUCCESS);
}

/*
** first we try to look for the label ; if it exists with a position other than
** -1, it has already been added and is a duplicate ; if the position is -1 it
** is either brand new or has only been referred to and we now define its
** position ; if it has references we fill them in now that we have the label's
** position to calculate a distance
*/

int		add_label(t_cwr *cwr, t_token *token, unsigned label_prog_pos)
{
	t_label	*label;
	t_head	*refs_head;

	token->content[token->len - 1] = 0;
	if (get_label(cwr, &label, token->content) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	else if (label->is_defined)
		return (cwr_error(cwr, "duplicate label: ", CWR_ERR_TOKEN));
	label->prog_pos = label_prog_pos;
	label->is_defined = 1;
	if (label->refs.first)
	{
		label->prog_pos = cwr->prog_line_start;
		fill_in_refs(cwr, label->refs.first, label->prog_pos);
		refs_head = &label->refs;
		ft_lstfree(&refs_head, FREE_BOTH, LST_KEEP_HEAD);
	}
	return (EXIT_SUCCESS);
}
