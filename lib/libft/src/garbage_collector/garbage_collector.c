/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 23:04:53 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/03 11:09:55 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** this is a small garbage collector (gc) ; it does not keep track of unused
** pointers
**
** you can activate/desactivate it with gc_get and the GC_ON and GC_OFF options;
** using a switch and not a calling argument avoids the need to change the
** function calls in internal library functions;
** if you free an element from the gc while the gc is off, only the element will
** be freed, the gc part willl be freed with the branch  
**
** you can create new collection branches with the gc_get and the NEW option
** (necessary before first use as you start with 0 branches)
**
** free the gc branches with free_gc (create new branches if you need to free
** different parts of emory at different times)
*/

int		add_sub_head(t_head *gc_main_head)
{
	t_lst			*gc_main_lst;
	t_head			*new_sub_head;

	if (!(new_sub_head = (t_head *)malloc(sizeof(*new_sub_head))))
		return (ERR_MALLOC);
	ft_memset(new_sub_head, 0, sizeof(*new_sub_head));
	if (!(gc_main_lst = (t_lst *)malloc(sizeof(*gc_main_lst))))
		return (ERR_MALLOC);
	ft_memset(gc_main_lst, 0, sizeof(*gc_main_lst));
	gc_main_lst->content = new_sub_head;
	ft_lstadd(gc_main_head, gc_main_lst);
	return (EXIT_SUCCESS);
}

/*
** option GC_NEW to check generate a branch (necessary before first use)
**
** option GC_ON/GC_OFF to turn the gc on or off
**
** option GC_STATE to check wether the gc is on or off
**
** option GC_CURRENT to get the most recent gc branch
**
** option GC_FREE is for internal use only
**
*/

int		gc_get(t_lst **gc_lst, int opt)
{
	static int		state = GC_OFF;
	static t_head	gc_main_head = {0, NULL, NULL};

	if (opt == GC_STATE)
		return (state);
	else if (opt == GC_ON || opt == GC_OFF)
		state = opt;
	else if (opt == GC_FREE)
	{
		if (gc_main_head.size == 0)
			return (EXIT_FAILURE);
		*gc_lst = ft_lstpop_elem(&gc_main_head, gc_main_head.first);
	}
	else
	{
		if (opt == GC_NEW && add_sub_head(&gc_main_head) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		if (!(*gc_lst = gc_main_head.first))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/*
** this functions frees the gc branches and their contents
**
** option CURRENT to free the most recent branch, option ALL to free all
** branches (not recommended if the calling program still has memory on the gc)
*/

void	free_gc(int opt)
{
	t_lst	*main_gc_lst;
	t_head	*gc_head;
	t_lst	*to_free;
	t_lst	*tmp;

	if (gc_get(&main_gc_lst, GC_FREE) == EXIT_FAILURE)
		return ;
	gc_head = main_gc_lst->content;
	if (gc_head->first)
	{
		to_free = gc_head->first;
		while (to_free)
		{
			tmp = to_free;
			to_free = to_free->next;
			if (tmp->content)
				free(tmp->content);
			free(tmp);
		}
	}
	free(gc_head);
	free(main_gc_lst);
	if (opt == GC_ALL)
		free_gc(GC_ALL);
}

/*
** this function pops and frees the element containing the matching malloc'ed
** zone from the current gc, and frees the malloc'ed zone
*/

void	gc_free(void **match)
{
	t_lst	*elem;
	t_lst	*gc_lst;
	t_head	*gc;

	if (!*match)
		return ;
	if (gc_get(NULL, GC_STATE) == GC_ON)
	{
		if (gc_get(&gc_lst, GC_CURRENT) != EXIT_SUCCESS)
			return ;
		gc = gc_lst->content;
		if (!(elem = ft_lstpop(gc, *match)))
			return ;
		free(elem);
	}
	free(*match);
	*match = NULL;
}

/*
** this function allocs a zone, and stores it in the current gc
*/

void	*gc_malloc(size_t size)
{
	void	*new_malloc;
	t_lst	*main_gc_lst;
	t_lst	*gc_elem;

	if (gc_get(NULL, GC_STATE) == GC_ON)
	{
		if (gc_get(&main_gc_lst, GC_CURRENT) != EXIT_SUCCESS)
			return (NULL);
		if (!(gc_elem = (t_lst *)malloc(sizeof(*gc_elem))))
			return (NULL);
		ft_lstadd((t_head *)main_gc_lst->content, gc_elem);
		gc_elem->content = malloc(size);
		new_malloc = gc_elem->content;
	}
	else
		new_malloc = malloc(size);
	if (new_malloc != NULL)
		ft_memset(new_malloc, 0, size);
	return (new_malloc);
}
