/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:51:24 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/25 16:12:17 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

int		get_opt_nb(t_vm *vm, char *arg)
{
	unsigned	opt_nb;

	opt_nb = 0;
	opt_nb = 0;
	while (opt_nb < NB_OPTIONS)
	{
		if (!ft_strcmp(arg, vm->option[opt_nb].opt_name))
			return (opt_nb);
		opt_nb++;
	}
	return (NB_OPTIONS);
}

int		parse_args(t_vm *vm, int argc, char **argv)
{
	unsigned	arg;
	unsigned	opt_nb;
	int			check_error;

	check_error = 0;
	arg = 1;
	if (argc < 2)
		return (EXIT_FAILURE);
	while (arg < (unsigned)argc)
	{
		opt_nb = get_opt_nb(vm, argv[arg]);
		if ((check_error = vm->option[opt_nb].parse_func(vm, argv, &arg))
			!= EXIT_SUCCESS)
			return (check_error);
	}
	if (vm->nb_players == 0)
		return ( ft_error("No players\n"));
	if ((check_error = charge_players(vm)) != EXIT_SUCCESS)
		return (check_error);
	return (EXIT_SUCCESS);
}
