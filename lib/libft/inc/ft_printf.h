/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:00:55 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/20 15:04:22 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include "stdarg.h"

# define TYPE_C 0
# define TYPE_S 1
# define TYPE_P 2
# define TYPE_D 3
# define TYPE_U 4
# define TYPE_X 5
# define NB_PF_TYPES 7
# define PF_TYPES "cspdux"

# define FLAG_P 0
# define FLAG_M 1
# define FLAG_H 2
# define FLAG_Z 3
# define FLAG_S 4
# define NB_PF_FLAGS 5
# define PF_FLAGS "+-#0 "

# define FIELD_HH 0xFFLU
# define FIELD_H  0xFFFFLU
# define FIELD_D  0xFFFFFFFFLU
# define FIELD_L  0xFFFFFFFFFFFFFFFFLU
# define FIELD_LL 0xFFFFFFFFFFFFFFFFLU
# define NB_FIELDS 5

# define BASE_HEX "0123456789abcdef"

# define PF_BUF_SIZE 64
# define PF_RESULT_MAX_SIZE 2147483647
# define NB_PF_ARGS 100

# define ERROR_NO_TYPE 0
# define ERROR_BAD_TYPE 1
# define ERROR_PF_BUF_TOO_SMALL 2
# define ERROR_TOO_MANY_PF_ARGS 3
# define ERROR_PF_RESULT_TOO_LONG 4

typedef union		u_pf_value
{
	char			ch;
	short			sh;
	int				d;
	long			ld;
	unsigned char	u_ch;
	unsigned short	u_sh;
	unsigned		u_d;
	unsigned long	lu;
	char			*s;
	void			*p;
}					t_pf_value;

typedef struct		s_pf_arg
{
	unsigned char	type_char;
	unsigned		type;
	unsigned		width;
	unsigned		has_prec;
	unsigned		prec;
	unsigned long	field;
	unsigned		base_len;
	unsigned		prefix_len;
	unsigned		filler_len;
	unsigned		total_len;
	unsigned		padding;
	unsigned		is_neg;
	char			filler;
	char			prefix[3];
	char			flag[NB_PF_FLAGS];
	t_pf_value		value;
}					t_pf_arg;

typedef struct s_pf	t_pf;

typedef int			(*t_func_pf)(t_pf *, t_pf_arg *);

struct				s_pf
{
	unsigned		pos;
	unsigned		format_pos;
	unsigned		size;
	unsigned		fd;
	va_list			ap;
	char			*format;
	char			*str;
	t_pf_arg		arg;
	t_func_pf		*func;
};

int					ft_dprintf(int fd, char *format, ...);
int					ft_printf(char *format, ...);
int					ft_sprintf(char **str, char *format, ...);

int					pf_core(t_pf *pf);

void				pf_exit(t_pf *pf);
int					pf_expand_arg(t_head *args, t_lst *lst_pf_arg);
int					pf_expand_format(t_pf *pf);
int					pf_expand_type_c(t_pf *pf, t_pf_arg *arg);
int					pf_expand_type_s(t_pf *pf, t_pf_arg *arg);
int					pf_expand_type_signed(t_pf *pf, t_pf_arg *arg);
int					pf_expand_type_unsigned(t_pf *pf, t_pf_arg *arg);

int					pf_get_padding(t_pf *pf, t_pf_arg *arg);

void				pf_parse_arg_field(t_pf *pf, t_pf_arg *arg,
	unsigned char c);
void				pf_parse_arg_flag(t_pf_arg *arg, unsigned char c);
void				pf_parse_arg_size(t_pf *pf, t_pf_arg *arg, unsigned *size,
	unsigned char c);
int					pf_parse_arg_type(t_pf *pf, t_pf_arg *arg, unsigned char c);
int					pf_parse_arg_value(t_pf *pf, t_pf_arg *arg);

#endif
