/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_expand_numbers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 19:07:31 by sikpenou          #+#    #+#             */
/*   Updated: 2020/03/17 11:29:10 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include <stdlib.h>

void	get_nb_len(t_pf_arg *arg, unsigned long *print_nb, unsigned long *b_len)
{
	unsigned long	tmp_print_nb;

	arg->base_len = 1;
	*print_nb = arg->value.lu & arg->field;
	*b_len = (arg->type == TYPE_X || arg->type == TYPE_P) ? 16 : 10;
	tmp_print_nb = *print_nb;
	while (tmp_print_nb >= *b_len)
	{
		tmp_print_nb /= *b_len;
		++arg->base_len;
	}
	if (arg->base_len < arg->prec)
		arg->base_len = arg->prec;
}

void	print_padding(t_pf *pf, t_pf_arg *arg)
{
	ft_memset(pf->str + pf->pos, arg->filler
		, arg->filler_len + arg->prefix_len);
	if (arg->flag[FLAG_Z] != 0)
		pf->pos += arg->filler_len;
	if (arg->prefix_len > 0)
		pf->str[pf->pos++] = arg->prefix[0];
	if (arg->prefix_len > 1)
		pf->str[pf->pos++] = arg->prefix[1];
	if (arg->flag[FLAG_Z] == 0)
		pf->pos += arg->filler_len;
}

void	print_number_in_base(t_pf *pf, t_pf_arg *arg
	, unsigned long print_nb, unsigned long b_len)
{
	unsigned	digits;

	digits = arg->base_len;
	pf->pos += digits;
	while (--digits)
	{
		pf->str[--pf->pos] = BASE_HEX[print_nb % b_len];
		print_nb /= b_len;
	}
	pf->str[--pf->pos] = BASE_HEX[print_nb % b_len];
	pf->pos += arg->base_len;
}

int		pf_expand_type_unsigned(t_pf *pf, t_pf_arg *arg)
{
	unsigned long	print_nb;
	unsigned long	b_len;

	get_nb_len(arg, &print_nb, &b_len);
	pf_get_padding(pf, arg);
	print_padding(pf, arg);
	print_number_in_base(pf, arg, print_nb, b_len);
	return (EXIT_SUCCESS);
}

int		pf_expand_type_signed(t_pf *pf, t_pf_arg *arg)
{
	if (arg->field == FIELD_HH && arg->value.ch < 0)
	{
		arg->is_neg = 1;
		arg->value.lu = (arg->value.ch + 1) * -1 + 1;
	}
	else if (arg->field == FIELD_H && arg->value.sh < 0)
	{
		arg->is_neg = 1;
		arg->value.lu = (arg->value.sh + 1) * -1 + 1;
	}
	else if (arg->field == FIELD_D && arg->value.d < 0)
	{
		arg->is_neg = 1;
		arg->value.lu = (arg->value.d + 1) * -1 + 1;
	}
	else if ((arg->field == FIELD_L || arg->field == FIELD_LL)
		&& arg->value.ld < 0)
	{
		arg->is_neg = 1;
		arg->value.lu = (arg->value.ld + 1) * -1 + 1;
	}
	return (pf_expand_type_unsigned(pf, arg));
}
