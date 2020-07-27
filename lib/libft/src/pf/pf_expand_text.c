/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_expand_text.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 17:38:59 by skpn              #+#    #+#             */
/*   Updated: 2020/03/17 11:43:00 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include <stdlib.h>

int		pf_expand_type_s(t_pf *pf, t_pf_arg *arg)
{
	int		check_ret;
	char	*value;

	value = arg->value.s;
	if (value == 0)
		value = "(null)";
	arg->base_len = ft_strlen(value);
	if ((check_ret = pf_get_padding(pf, arg)) != EXIT_SUCCESS)
		return (check_ret);
	if (arg->filler_len > 0)
		ft_memset(pf->str + pf->pos, arg->filler, arg->filler_len);
	pf->pos += arg->filler_len;
	ft_memcpy(pf->str + pf->pos, value, arg->base_len);
	pf->pos += arg->base_len;
	return (EXIT_SUCCESS);
}

int		pf_expand_type_c(t_pf *pf, t_pf_arg *arg)
{
	char	str[2];

	str[0] = arg->value.ch;
	str[1] = 0;
	arg->value.s = str;
	arg->type = TYPE_S;
	return (pf_expand_type_s(pf, arg));
}
