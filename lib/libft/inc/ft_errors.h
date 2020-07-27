/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 14:35:21 by skpn              #+#    #+#             */
/*   Updated: 2020/04/08 18:52:53 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERRORS_H
# define FT_ERRORS_H

# define ERR_FD 2

# define ERR_LEN 60
# define ERR_TOTAL_LEN ERR_LEN * 15

# define ERR_MSG_FULL "Too many errors.\n"
# define ERR_MSG_FULL_LEN 17
# define ERR_TOO_LONG "... (error too long)\n"
# define ERR_TOO_LONG_LEN 21

# define ERR_MALLOC EXIT_FAILURE + 1

# define ERR_MAGIC_FILE EXIT_FAILURE + 2

# define ERR_OVERFLOW EXIT_FAILURE + 3
# define ERR_UNDERFLOW EXIT_FAILURE + 4

# define ERR_OPEN EXIT_FAILURE + 5
# define ERR_READ EXIT_FAILURE + 6
# define ERR_FILE_TOO_LARGE EXIT_FAILURE + 7

typedef struct	s_err
{
	int			fd;
	int			pos;
	char		*msg;
}				t_err;

int		ft_error(char *new_error);

void	ft_errors_print(void);

void	ft_errors_set_fd(int fd);

#endif