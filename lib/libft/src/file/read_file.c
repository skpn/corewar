/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 20:56:29 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/08 18:50:23 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

/*
** This file reader takes a t_file pointer and a file name and fills the t_file
** structure with the correct fd, file size, and file content (malloc'ed)
**
** The free function takes an option to free the t_file as well in case it was
** malloc'ed
**
** The reading buffer size and max file size are defined in ft_read_file.h
*/

void		free_file(t_file *file, int opt)
{
	if (file->content)
		gc_free((void **)&file->content);
	if (opt == FREE_STRUCT)
		gc_free((void **)&file);
}

static int	read_loop(t_file *file)
{
	int		ret;

	while ((ret = read(file->fd, file->content + file->size, FILE_BUF)) >= 0
		&& file->size < FILE_MAX_SIZE)
	{
		file->size += ret;
		if (ret == FILE_BUF)
		{
			if (ft_realloc(&file->content, file->size, FILE_BUF)
				!= EXIT_SUCCESS)
				return (ERR_MALLOC);
		}
		else
		{
			file->content[file->size] = '\0';
			return (EXIT_SUCCESS);
		}
	}
	ft_error(ret < 0 ? "read error\n" : "file size above limit\n");
	return (EXIT_FAILURE);
}

int			read_file(t_file *file, char *file_name)
{
	int		ret;

	file->fd = 0;
	if (file_name != NULL && (file->fd = open(file_name, O_RDONLY)) < 3)
		return (ERR_OPEN);
	if (!(file->content = (char *)malloc(FILE_BUF + 1)))
		return (ERR_MALLOC);
	file->content[FILE_BUF] = 0;
	file->size = 0;
	ret = read_loop(file);
	if (file->fd != 0)
		close(file->fd);
	if (ret != EXIT_SUCCESS)
		gc_free((void **)&file->content);
	return (ret);
}
