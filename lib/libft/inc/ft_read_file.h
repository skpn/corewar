/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 12:33:46 by skpn              #+#    #+#             */
/*   Updated: 2020/04/07 19:06:23 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READ_FILE_H
# define FT_READ_FILE_H

# define FILE_BUF 40000
# define FILE_MAX_SIZE 4000000

typedef struct	s_ft_file
{
	int			fd;
	unsigned	size;
	char		*content;
}				t_file;

void			free_file(t_file *file, int opt);

int				read_file(t_file *file, char *file_name);

#endif