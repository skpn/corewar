/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:21:40 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/25 15:55:11 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

int		main(int argc, char **argv)
{
	t_vm	vm;
	t_dump	dump;
	int		ret;

	ft_memset(&vm, 0, sizeof(vm));
	init_structs_vm(&vm, &dump);
	ret = parse_args(&vm, argc, argv);
	if (ret != EXIT_SUCCESS)
		usage_cwr_vm();
	else
		ret = process_loop(&vm);
	if (ret == EXIT_SUCCESS)
	{
		log_players(&vm);
		log_winner(&vm);
	}
	else
		ft_errors_print();
	exit_vm(vm);
	return (ret);
}
