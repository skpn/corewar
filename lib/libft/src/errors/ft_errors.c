/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 15:55:14 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/09 15:20:20 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_err	*get_errors(void)
{
	static char		static_msg[ERR_TOTAL_LEN + ERR_MSG_FULL_LEN + 1];
	static t_err	errors = {ERR_FD, 0, static_msg};

	return (&errors);
}

void	ft_errors_set_fd(int fd)
{
	t_err	*errors;

	errors = get_errors();
	errors->fd = fd;
}

void	ft_errors_print(void)
{
	t_err	*errors;

	errors = get_errors();
	write(errors->fd, errors->msg, errors->pos);
	errors->pos = 0;
}

int		ft_error(char *new_error)
{
	unsigned	new_error_len;
	t_err		*errors;
	char		warning[ERR_LEN];

	errors = get_errors();
	if (errors->pos >= ERR_TOTAL_LEN)
		return (EXIT_FAILURE);
	new_error_len = ft_strlen(new_error);
	if (new_error_len > ERR_LEN)
	{
		ft_memcpy(warning, new_error, ERR_LEN - ERR_TOO_LONG_LEN);
		ft_memcpy(warning + (ERR_LEN - ERR_TOO_LONG_LEN), ERR_TOO_LONG,
			ERR_TOO_LONG_LEN);
		new_error = warning;
		new_error_len = ERR_LEN;
	}
	if (errors->pos + new_error_len >= ERR_TOTAL_LEN)
		ft_memcpy(errors->msg + errors->pos, ERR_MSG_FULL, ERR_MSG_FULL_LEN);
	else
		ft_memcpy(errors->msg + errors->pos, new_error, new_error_len);
	errors->pos += new_error_len;
	return (EXIT_FAILURE);
}