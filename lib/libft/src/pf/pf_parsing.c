/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 17:38:50 by skpn              #+#    #+#             */
/*   Updated: 2020/03/17 11:27:25 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <stdlib.h>

int		pf_parse_arg_type(t_pf *pf, t_pf_arg *arg, unsigned char c)
{
	arg->type_char = c;
	if (c == 'c')
		arg->type = TYPE_C;
	else if (c == 's')
		arg->type = TYPE_S;
	else if (c == 'p')
	{
		arg->field = FIELD_L;
		arg->flag[FLAG_H] = 1;
		arg->type = TYPE_P;
	}
	else if (c == 'd')
		arg->type = TYPE_D;
	else if (c == 'u')
		arg->type = TYPE_U;
	else if (c == 'x')
		arg->type = TYPE_X;
	arg->value.ld = va_arg(pf->ap, long);
	return (pf->func[arg->type](pf, arg));
}

void	pf_parse_arg_size(t_pf *pf, t_pf_arg *arg, unsigned *size
	, unsigned char c)
{
	if (c == '.')
	{
		arg->has_prec = 1;
		c = pf->format[pf->format_pos++];
		size = &arg->prec;
	}
	if (c == '*')
	{
		*size = va_arg(pf->ap, long long);
	}
	else
	{
		*size = 0;
		while (ft_ischarset(c, "0123456789"))
		{
			*size = *size * 10 + c - 48;
			c = pf->format[pf->format_pos++];
		}
		--pf->format_pos;
	}
	if ((int)(*size) < 0)
		*size = 0;
}

void	pf_parse_arg_flag(t_pf_arg *arg, unsigned char c)
{
	if (c == '+')
		arg->flag[FLAG_P] = 1;
	else if (c == '-')
		arg->flag[FLAG_M] = 1;
	else if (c == '#')
		arg->flag[FLAG_H] = 1;
	else if (c == '0')
		arg->flag[FLAG_Z] = 1;
	else if (c == ' ')
		arg->flag[FLAG_S] = 1;
}

void	pf_parse_arg_field(t_pf *pf, t_pf_arg *arg, unsigned char c)
{
	if (c == 'h')
	{
		arg->field = FIELD_H;
		if (pf->format[pf->format_pos++] == 'h')
		{
			arg->field = FIELD_HH;
			while (pf->format[pf->format_pos] == 'h')
				++pf->format_pos;
		}
		--pf->format_pos;
	}
	if (c == 'l')
	{
		arg->field = FIELD_L;
		if (pf->format[pf->format_pos++] == 'l')
		{
			arg->field = FIELD_LL;
			while (pf->format[pf->format_pos] == 'l')
				++pf->format_pos;
		}
		--pf->format_pos;
	}
}
