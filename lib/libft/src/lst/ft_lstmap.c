/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <sikpenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 18:32:01 by sikpenou          #+#    #+#             */
/*   Updated: 2020/02/27 18:32:03 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int		ft_lstmap(t_head *head, t_func_lstmap func)
{
	int		check_ret;
	t_lst	*lst;
	t_lst	*tmp;

	lst = head->first;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		if ((check_ret = func(head, tmp)) != EXIT_SUCCESS)
			return (check_ret);
	}
	return (EXIT_SUCCESS);
}
