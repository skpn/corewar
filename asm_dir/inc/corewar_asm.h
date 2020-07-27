/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_asm.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 13:30:58 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/25 15:53:19 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_ASM_H
# define COREWAR_ASM_H

# include "libft.h"
# include "op.h"

# define TOKEN_START 1
# define TOKEN_INST 2
# define TOKEN_ARG 3
# define TOKEN_SEP 4
# define TOKEN_LABEL 5
# define TOKEN_LABEL_CHAR 6
# define TOKEN_END 7
# define TOKEN_MAX 12

# define NAME 1
# define COMMENT 2

# define CWR_ERR_TOKEN 1
# define CWR_ERR_LINE 2
# define CWR_ERR_CHR 4
# define CWR_ERR_NO_POS 8
# define CWR_ERR_NONE 16

# define FORWARD 0
# define BACK 1

# define CWR_DEBUG 1

typedef struct	s_op
{
	char		*name;
	unsigned	nb_args;
	unsigned	arg_type[MAX_ARGS_NUMBER];
	unsigned	code;
	unsigned	wait;
	char		*long_name;
	unsigned	encoding_byte;
	unsigned	dir_size;
}				t_op;

typedef struct	s_ref
{
	unsigned	type_size;
	unsigned	prog_line_start;
	unsigned	prog_pos;
}				t_ref;

typedef struct	s_label
{
	char		*name;
	int			is_defined;
	int			prog_pos;
	t_head		refs;
}				t_label;

typedef struct	s_token
{
	int			type;
	int			len;
	int			byte_size;
	int			content_pos;
	char		*content;
	char		*value;
}				t_token;

typedef struct	s_line
{
	char		encoding_byte;
	int			op_code;
	int			dir_size;
	int			arg_nb;
	int			arg_type[MAX_ARGS_NUMBER];
	int			arg[MAX_ARGS_NUMBER];
	int			first_token;
	int			token_pos;
	int			arg_index_token[MAX_ARGS_NUMBER];
	t_token		token[TOKEN_MAX];
	t_op		*rules;
}				t_line;

typedef struct	s_cwr
{
	int			pos;
	int			line_start;
	int			line_len;
	int			file_len;
	int			line_nb;
	int			prog_line_start;
	int			prog_pos;
	int			len_prog_name;
	int			len_comment;
	t_line		*line;
	t_head		labels;
	char		*prog_name;
	char		*comment;
	char		*file_cor;
	char		*file;
	char		*cpy;
	char		header[sizeof(header_t)];
	char		prog[CHAMP_MAX_SIZE];
}				t_cwr;

extern t_op		g_op_tab[17];

int				add_label(t_cwr *cwr, t_token *token, unsigned label_pos);
int				add_ref(t_cwr *cwr, int *arg, t_token *token);
t_label			*alloc_new_label(char *label_name);
t_ref			*alloc_new_ref(unsigned byte_size, unsigned prog_line_start,
	unsigned prog_pos);

int				check_remaining_refs(t_cwr *cwr);
int				check_tokens(t_cwr *cwr, t_line *line);
int				create_output_file(t_cwr *cwr);
int				cwr_eol(char c);
int				cwr_error(t_cwr *cwr, char *msg, int context);

void			exit_cwr(t_cwr *cwr);

t_label			*find_label(t_lst *label_lst, char *label_name);
void			fill_in_refs(t_cwr *cwr, t_lst *ref_lst, unsigned label_pos);

int				get_label(t_cwr *cwr, t_label **label, char *label_name);
int				get_tokens_contents(t_cwr *cwr, t_line *line);

int				init_structs(t_cwr *cwr, t_line *line, t_file *champ_file,
	char *champ_file_name);

int				line_to_prog(t_cwr *cwr, t_line *line);

int				parse_header(t_cwr *cwr);
int				parse_line_tokens(t_cwr *cwr, t_line *line, t_token *token);
int				parse_prog(t_cwr *cwr);
void			print_all_tokens(t_line *line);
void			print_hex(char *zone, int len);
void			print_labels(t_head labels);
void			print_line(t_line *line);
void			print_rules(t_op *rules);
void			print_token(t_token token);

void			skip_comment(t_cwr *cwr);
void			skip_space(t_cwr *cwr, int opt);
void			skip_to_eol(t_cwr *cwr);
void			swap_endian(char *nb, unsigned size);

void			update_line_nb(t_cwr *cwr, char c);
int				usage_cwr_asm(void);

void			write_to_prog(t_cwr *cwr, t_line *line, t_token *token);

#endif
