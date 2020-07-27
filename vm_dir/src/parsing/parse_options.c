/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 16:59:12 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/24 22:16:39 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

int		parse_visu_option(t_vm *vm, char **argv, unsigned *arg)
{
	vm->visu = 0;
	(void)argv;
	(*arg)++;
	return (EXIT_SUCCESS);
}

int		parse_verbose_option(t_vm *vm, char **argv, unsigned *arg)
{
	(*arg)++;
	if (!argv[*arg])
		return ( ft_error("Bad argument for option: '-v'\n"));
	vm->log = ft_atoi_base(argv[*arg], "0123456789");
	(*arg)++;
	return (EXIT_SUCCESS);
}

int		parse_aff_option(t_vm *vm, char **argv, unsigned *arg)
{
	vm->aff = 1;
	(*arg)++;
	(void)argv;
	return (EXIT_SUCCESS);
}

int		parse_dump_option(t_vm *vm, char **argv, unsigned *arg)
{
	if (!ft_strcmp(argv[*arg], "-d"))
		vm->exit_after_dump = 1;
	(*arg)++;
	vm->dump_cycles = ft_atoi_base(argv[*arg], "0123456789");
	if (!vm->dump_cycles && !vm->exit_after_dump)
		return ( ft_error("Bad argument for option: '-d'\n"));
	(*arg)++;
	return (EXIT_SUCCESS);
}
