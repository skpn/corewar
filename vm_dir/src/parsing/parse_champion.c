/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:11:40 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/24 23:46:32 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"
#include <fcntl.h>
#include <unistd.h>

int		parse_header(t_player *player, int fd)
{
	header_t	*header;
	int			check_ret;
	char		buf[sizeof(header_t) + 1];

	check_ret = read(fd, buf, sizeof(header_t));
	if (check_ret != (int)sizeof(header_t))
	{
		close(fd);
		if (check_ret == -1)
			return (ft_error("Read error\n"));
		return ( ft_error("Header is not the right size\n"));
	}
	header = (header_t *)buf;
	swap_endian((char *)&header->magic, sizeof(header->magic));
	swap_endian((char *)&header->prog_size, sizeof(header->prog_size));
	player->magic = ((header_t *)buf)->magic;
	if (player->magic != COREWAR_EXEC_MAGIC)
		return (ft_error("Magic file error\n"));
	ft_strcpy(player->name, ((header_t *)buf)->prog_name);
	player->prog_size = ((header_t *)buf)->prog_size;
	ft_strcpy(player->comment, ((header_t *)buf)->comment);
	return (EXIT_SUCCESS);
}

int		add_champion(t_vm *vm, char *champ_file, unsigned nb_champ)
{
	int			check_ret;
	int			fd;
	t_player	*player;

	if (++vm->nb_players > MAX_PLAYERS)
		return ( ft_error("Too many players\n"));
	if ((fd = open(champ_file, O_RDONLY)) == -1)
		return (ft_error("Open error\n"));
	player = &vm->player[nb_champ];
	player->id = (nb_champ + 1) * ZAZ_MODE;
	if ((check_ret = parse_header(player, fd)) != EXIT_SUCCESS)
		return (check_ret);
	check_ret = read(fd, player->prog, CHAMP_MAX_SIZE + 1);
	close(fd);
	if (check_ret == -1)
		return (ft_error("Read error\n"));
	if (check_ret != (int)player->prog_size)
		return ( ft_error("Program size does not match header information\n"));
	if (check_ret == CHAMP_MAX_SIZE + 1)
		return ( ft_error("Program too long\n"));
	return (EXIT_SUCCESS);
}

int		parse_champion(t_vm *vm, char **argv, unsigned *arg)
{
	unsigned	nb_champ;
	int			check_ret;

	if (ft_strcmp("-n", argv[*arg]) != 0)
		nb_champ = MAX_PLAYERS + vm->nb_players + 1;
	else
	{
		(*arg)++;
		if (!argv[*arg])
			return (ft_error("Bad argument for option: '-n'\n"));
		nb_champ = ft_atoi_base(argv[*arg], "0123456789");
		if (argv[*arg][0] == '-' || nb_champ == 0 || nb_champ > MAX_PLAYERS
			|| vm->player[nb_champ].id)
			return (ft_error("Bad argument for option: '-n'\n"));
		(*arg)++;
		if (!argv[*arg])
			return (ft_error("Bad argument for option: '-n'\n"));
	}
	check_ret = add_champion(vm, argv[*arg], nb_champ);
	(*arg)++;
	return (check_ret);
}
