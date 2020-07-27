/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 18:42:52 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/08 18:45:11 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define DEBUG 1
# define QUIET 1
# define VERBOSE 2

# define LEFT 1
# define RIGHT 2
# define BOTH 3

# define BEFORE 1
# define AFTER 2

# define FREE_STRUCT 1
# define FREE_CONTENT 2
# define FREE_BOTH 3

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "ft_dynamic_array.h"
# include "ft_errors.h"
# include "ft_garbage_collector.h"
# include "ft_hash_tables.h"
# include "ft_lst.h"
# include "ft_printf.h"
# include "ft_read_file.h"

unsigned long long	ft_ato_ull(const char *str, int *pos);
int					ft_abs(int a);
int					ft_atoi(const char *str);
int					ft_atoi_base(char *nbr, char *base_from);

int					ft_check_base(char *str, char *base);
char				*ft_convert_base(char *nbr, char *base_from,
	char *base_to);

int					ft_find_next_prime(unsigned long nb);
void				ft_free(void **match);
int					ft_free_tab(void **tab, size_t len);

int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_ischarset(unsigned char c, char *charset);
int					ft_isdigit(int c);
int					ft_isspace(int c);
char				*ft_itoa(int n);
char				*ft_itoa_base(long nb, char *base_to);

unsigned			ft_lltoa_base(long long nb, char *base_to,
	char *result);

int					ft_max(int a, int b);
void				*ft_memalloc(size_t size);
int					ft_memchr_pos(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c,
	size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_memcset(void *o_s, int c, int stop);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, unsigned char c, size_t len);
int					ft_min(int a, int b);

long long int		ft_pow(long long int nb, long long int pow);
void				ft_putnbr(long long n);
void				ft_putnbr_fd(int n, int fd);

int					ft_realloc(char **zone, long curr_size_in_octs,
	long to_add_in_octs);

int					ft_strchr_pos(char *str, int c);
int					ft_strcmp(char *s1, char *s2);
int					ft_strcmp_heap(char *s1, char *s2);
char				*ft_strcpy(char *dest, char *src);
char				*ft_strcpy_heap(char *dest, char *src);
char				*ft_strdup(const char *s1);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strjoin_free(char **s1, char **s2, int opt);
size_t				ft_strlen(const char *s);
size_t				ft_strlen_heap(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strrchr(const char *str, int c);
char				*ft_strrev(char *str);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strtrim(char const *s);
char				*ft_strsub(char const *s, unsigned int start,
	size_t len);
void				ft_swap(void **a, void **b, int opt);
void				ft_swapstr(char **a, char **b);

int					ft_tabmap(void **tab, unsigned size,
	t_func_tabmap func);

char				*ft_ulltoa(unsigned long long n);
unsigned			ft_ulltoa_base(unsigned long long n, char *base_to,
	char *result);

#endif
