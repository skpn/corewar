/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:16:51 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/08 18:47:35 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

int		pf_parse_arg(t_pf *pf)
{
	char		c;
	t_pf_arg	*arg;

	arg = &pf->arg;
	arg->field = FIELD_D;
	while ((c = pf->format[pf->format_pos++]) != 0)
	{
		if (ft_ischarset(c, PF_FLAGS))
			pf_parse_arg_flag(arg, c);
		else if (c == '.' || c == '*' || ft_ischarset(c, "123456789"))
		{
			pf_parse_arg_size(pf, arg, &arg->width, c);
		}
		else if (c == 'h' || c == 'l')
			pf_parse_arg_field(pf, arg, c);
		else if (ft_ischarset(c, PF_TYPES))
			return (pf_parse_arg_type(pf, arg, c));
		else
		{
			return (ERROR_BAD_TYPE);
		}
	}
	return (ERROR_NO_TYPE);
}

int		pf_expand_format(t_pf *pf)
{
	char	c;
	int		check_ret;

	while ((c = pf->format[pf->format_pos++]) != 0)
	{
		if (c == '%')
		{
			ft_memset(&pf->arg, 0, sizeof(pf->arg));
			if ((c = pf->format[pf->format_pos]) != '%' && c != 0
				&& (check_ret = pf_parse_arg(pf)) != EXIT_SUCCESS)
				return (check_ret);
		}
		else
		{
			pf->str[pf->pos++] = c;
			if (pf->pos == PF_BUF_SIZE)
			{
				if (ft_realloc(&pf->str, pf->size, PF_BUF_SIZE) != EXIT_SUCCESS)
					return (ERR_MALLOC);
				pf->size += PF_BUF_SIZE;
			}
		}
	}
	pf->str[pf->pos] = 0;
	return (EXIT_SUCCESS);
}

void	pf_init_func_tab(t_pf *pf)
{
	pf->func[TYPE_C] = &pf_expand_type_c;
	pf->func[TYPE_S] = &pf_expand_type_s;
	pf->func[TYPE_P] = &pf_expand_type_unsigned;
	pf->func[TYPE_D] = &pf_expand_type_signed;
	pf->func[TYPE_U] = &pf_expand_type_unsigned;
	pf->func[TYPE_X] = &pf_expand_type_unsigned;
}

int		pf_core(t_pf *pf)
{
	int			check_ret;
	t_func_pf	func[NB_PF_TYPES];

	if (PF_BUF_SIZE < 1 || PF_BUF_SIZE % 8)
		return (EXIT_FAILURE);
	pf->func = func;
	pf_init_func_tab(pf);
	if (!(pf->str = (char *)gc_malloc(PF_BUF_SIZE)))
		return (ERR_MALLOC);
	pf->size = PF_BUF_SIZE;
	if ((check_ret = pf_expand_format(pf)) != EXIT_SUCCESS)
		return (check_ret);
	return (EXIT_SUCCESS);
}
