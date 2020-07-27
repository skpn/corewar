/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 12:11:33 by skpn              #+#    #+#             */
/*   Updated: 2020/03/27 10:56:09 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LST_H
# define FT_LST_H

# define LST_KEEP_HEAD 1
# define LST_FREE_HEAD 2

typedef struct		s_lst
{
	void			*content;
	struct s_lst	*prev;
	struct s_lst	*next;
}					t_lst;

typedef struct		s_head
{
	unsigned		size;
	t_lst			*first;
	t_lst			*last;
}					t_head;

typedef int			(*t_func_lstmap)(t_head *, t_lst *);

int					ft_lstcycle(t_lst *begin);
void				ft_lstjoin(t_head *head_dest, t_head *head_src);
int					ft_lstmap(t_head *head, t_func_lstmap func);
t_head				*ft_lstnew(void *content);
t_head				*ft_lstcpy(t_head *original_head);
void				ft_lstadd(t_head *head, t_lst *new_lst);
void				ft_lstadd_back(t_head *head, t_lst *new_lst);
t_lst				*ft_lstadd_back_new(t_head *head, void *content);
t_lst				*ft_lstadd_new(t_head *head, void *content);
void				ft_lstadd_sorted(t_head *head, t_lst *new_lst,
	int (*cmp)(t_lst *, t_lst *));
t_lst				*ft_lstfind(t_head *head, void *match);
void				ft_lstfree(t_head **head, int opt_elems, int opt_head);
void				ft_lstfree_elem(t_lst **elem, int opt);
void				ft_lstfree_head(t_head **head);
void				ft_lstinsert(t_head *head, t_lst *ref, t_lst *insert,
	int bef_or_aft);
t_lst				*ft_lstnew_elem(void *content);
t_head				*ft_lstnew_head(void);
t_lst				*ft_lstpop(t_head *head, void *match);
t_lst				*ft_lstpop_elem(t_head *head, t_lst *elem);
void				ft_lstprint(t_head *head);
void				ft_lst_replace_elem(t_head *head, t_lst *original,
	t_lst *replacement);
void				ft_lstsort(t_head *head,
	int (*f_cmp)(t_lst *, t_lst *));
void				ft_lstswap_contents(t_lst *elem_1, t_lst *elem_2);
void				ft_lstswap_heads(t_head *head, t_lst *elem_1,
	t_lst *elem_2);
void				ft_lsttransfer(t_head *head_from, t_head *heaad_to,
	t_lst *elem);

#endif