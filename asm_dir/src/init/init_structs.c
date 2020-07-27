/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:05:16 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/21 19:30:01 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_asm.h"

/*
** the new reference's instruction's position (prog_line_start) is used to
** get the distance to the label it refers to, and its own position (prog_pos)
** is used to know where to write the argument in the program
*/

t_ref	*alloc_new_ref(unsigned size, unsigned prog_line_start,
	unsigned prog_pos)
{
	t_ref *new_ref;

	new_ref = (t_ref *) gc_malloc(sizeof(t_ref));
	if (!new_ref)
		return (NULL);
	new_ref->type_size = size;
	new_ref->prog_line_start = prog_line_start;
	new_ref->prog_pos = prog_pos;
	return (new_ref);
}

/*
** a new label's is set at position -1 and is_defined 0; this lets us know if a
** label has not yet been defined
*/

t_label	*alloc_new_label(char *label_name)
{
	t_label *new_label;

	new_label = (t_label *) gc_malloc(sizeof(*new_label));
	if (!new_label)
		return (NULL);
	new_label->name = label_name;
	new_label->prog_pos = -1;
	new_label->is_defined = 0;
	return (new_label);
}

int		get_file_cor(t_cwr *cwr, char *file_s)
{
	int		len;

	len = ft_strlen(file_s);
	if (len < 3 || file_s[len - 1] != 's' || file_s[len - 2] != '.')
		return (cwr_error(cwr, "bad file extension\n", CWR_ERR_NO_POS));
	if (!(cwr->file_cor = (char *) gc_malloc(len + 3)))
		return (cwr_error(cwr, "error allocating file_cor\n", CWR_ERR_NO_POS));
	ft_memcpy(cwr->file_cor, file_s, len - 1);
	cwr->file_cor[len - 1] = 'c';
	cwr->file_cor[len] = 'o';
	cwr->file_cor[len + 1] = 'r';
	return (EXIT_SUCCESS);
}

int		init_structs(t_cwr *cwr, t_line *line, t_file *champ_file,
	char *champ_file_name)
{
	int		ret;

	ft_memset(cwr, 0, sizeof(*cwr));
	if ((ret = get_file_cor(cwr, champ_file_name)) != EXIT_SUCCESS)
		return (ret);
	line->rules = g_op_tab;
	cwr->line = line;
	++cwr->line_nb;
	if (read_file(champ_file, champ_file_name) != EXIT_SUCCESS)
		return (cwr_error(cwr, "error reading file", CWR_ERR_NO_POS));
	cwr->file = champ_file->content;
	cwr->file_len = champ_file->size;
	if ((cwr->cpy = ft_strdup(cwr->file)) == NULL)
		return (cwr_error(cwr, "error copying file\n", CWR_ERR_NO_POS));
	return (EXIT_SUCCESS);
}
