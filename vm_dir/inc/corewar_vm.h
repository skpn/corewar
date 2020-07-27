/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_vm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:22:14 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/25 16:10:24 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VM_H
# define COREWAR_VM_H

# include "op.h"
# include "libft.h"

# define NB_OPTIONS 6

# define MASK_INDIRECT 192
# define MASK_DIRECT 128
# define MASK_REGISTER 64

# define T_VAL 1
# define T_ADDR 2

# define LIVE 1
# define LD 2
# define ST 3
# define ADD 4
# define SUB 5
# define AND 6
# define OR 7
# define XOR 8
# define ZJMP 9
# define LDI 10
# define STI 11
# define FORK 12
# define LLD 13
# define LLDI 14
# define LFORK 15
# define AFF 16
# define NB_FUNCS 16

# define LOG_LIVE 1
# define LOG_CYCLE 2
# define LOG_OP 4
# define LOG_DEATH 8
# define LOG_PC 16

# define FT_BIG_ENDIAN 1

# define ZAZ_MODE -1

typedef struct s_vm	t_vm;

typedef int			(*t_parse_func)(t_vm *, char **args, unsigned *arg);

typedef struct		s_options
{
	char			*opt_name;
	t_parse_func	parse_func;
}					t_options;

typedef struct		s_player
{
	unsigned		id;
	unsigned		magic;
	unsigned		prog_size;
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	char			prog[CHAMP_MAX_SIZE + 1];
}					t_player;

typedef struct		s_dump
{
	unsigned		size;
	unsigned		lines;
	unsigned		line_size;
	unsigned		line_numbers_size;
	unsigned		line_start;
	unsigned		octs_per_line;
	char			buf[MEM_SIZE * 4];
	char			*base;
}					t_dump;

typedef struct		s_op
{
	char			*name;
	unsigned		nb_args;
	unsigned		arg_type[3];
	unsigned		code;
	unsigned		wait;
	char			*long_name;
	unsigned		coding_byte;
	unsigned		dir_size;
}					t_op;

typedef struct		s_vm_op
{
	unsigned char	coding_byte;
	unsigned		is_valid;
	unsigned		code;
	unsigned		move;
	unsigned		has_coding_byte;
	unsigned		arg_type[3];
	unsigned		arg_raw[3];
	unsigned		arg[3];
	short			tmp_pc;
	t_op			*ref;
}					t_vm_op;

typedef struct		s_process
{
	unsigned		id;
	unsigned		is_alive;
	unsigned		wait;
	unsigned		code;
	unsigned		carry;
	unsigned		last_live_cycle;
	short			pc;
	char			reg_tab[REG_NUMBER][REG_SIZE];
}					t_process;

typedef int			(*t_func_vm)(t_vm *, t_process *);

struct				s_vm
{
	unsigned		visu;
	unsigned		aff;
	unsigned		log;
	unsigned		parse_pos;
	unsigned		nb_players;
	unsigned		cycles_since_check;
	unsigned		checks;
	int				cycles_to_die;
	unsigned		dump_cycles;
	unsigned		cycles_since_dump;
	unsigned		exit_after_dump;
	unsigned		cycle;
	unsigned		lives;
	unsigned		winner;
	unsigned		last_id_process;
	t_vm_op			op;
	t_head			*processes;
	t_dump			*dump;
	char			arena[MEM_SIZE];
	t_options		option[NB_OPTIONS + 1];
	t_op			op_tab[18];
	t_func_vm		func[17];
	t_player		player[MAX_PLAYERS + MAX_PLAYERS + 1];
};


extern t_op			g_op_tab[17];

int					add_process(t_vm *vm, unsigned pos);
unsigned			arena_pos_to_dump_pos(t_vm *vm, unsigned arena_pos);
void				arena_to_reg(t_vm *vm, short pos,
	char reg[REG_SIZE]);

int					charge_players(t_vm *vm);

int					check_vm(t_vm *vm);
void				convert_args_add_sub(t_vm *vm, t_process *process);
void				convert_args_and_or_xor(t_vm *vm, t_process *process);
void				convert_ind_to_dir(t_vm *vm, t_process *process,
	unsigned *ind);

void				display_player_alive(t_vm *vm, t_player player);
void				dump_memory(t_vm *vm);

void				exit_vm(t_vm vm);

int					ft_strcmp_slow(const char *s1, const char *s2);

void				get_address(unsigned *arg);
int					get_args_value(t_vm *vm, t_vm_op *op);
t_player			*get_player(t_vm *vm, t_process *process);
int					get_size(t_vm_op *op, unsigned arg);

void				init_structs_vm(t_vm *vm, t_dump *dump);

void				log_cycle(t_vm *vm);
void				log_cycles_to_die(t_vm *vm);
void				log_death(t_vm *vm, t_process *process);
void				log_live(t_vm *vm, t_player *player);
void				log_op_add_sub(t_vm *vm, t_process *process);
void				log_op_and_or_xor(t_vm *vm, t_process *process);
void				log_pc(t_vm *vm, t_process *process);
void				log_players(t_vm *vm);
void				log_winner(t_vm *vm);
void				long_unsigned_to_reg(char reg[REG_SIZE], long unsigned nb);
void				long_unsigned_to_arena(t_vm *vm, short pos,
	long unsigned nb, unsigned size);

void				manage_end_of_cycle(t_vm *vm);
void				move_pc(short *pc, unsigned len);

int					parse_aff_option(t_vm *vm, char **argv, unsigned *arg);
int					parse_verbose_option(t_vm *vm, char **argv, unsigned *arg);
int					parse_dump_option(t_vm *vm, char **argv, unsigned *arg);
int					parse_args(t_vm *vm, int argc, char **argv);
void				parse_op(t_vm *vm, t_process *process);
int					parse_champion(t_vm *vm, char **argv, unsigned *arg);
int					parse_visu_option(t_vm *vm, char **argv, unsigned *arg);
void				print_dump_zone(t_vm *vm, unsigned arena_pos,
	unsigned print_len);
int					process_loop(t_vm *vm);

long unsigned		reg_to_long_unsigned(char reg[REG_SIZE]);
void				reg_to_arena(t_vm *vm, short pos,
	char reg[REG_SIZE]);

void				set_dump(t_dump *dump);
t_vm				set_vm(void);
void				set_process_player(char reg[REG_SIZE], unsigned player_id);
void				swap_endian(char *nb, unsigned size);

void				update_dump(t_vm *vm);
void				update_dump_zone(t_vm *vm, unsigned arena_pos,
	unsigned len);
void				update_process_player(t_process *process);
int					usage_cwr_vm(void);

int					vm_func_live(t_vm *vm, t_process *process);
int					vm_func_ld(t_vm *vm, t_process *process);
int					vm_func_st(t_vm *vm, t_process *process);
int					vm_func_add(t_vm *vm, t_process *process);
int					vm_func_sub(t_vm *vm, t_process *process);
int					vm_func_and(t_vm *vm, t_process *process);
int					vm_func_or(t_vm *vm, t_process *process);
int					vm_func_xor(t_vm *vm, t_process *process);
int					vm_func_zjmp(t_vm *vm, t_process *process);
int					vm_func_ldi(t_vm *vm, t_process *process);
int					vm_func_sti(t_vm *vm, t_process *process);
int					vm_func_fork(t_vm *vm, t_process *process);
int					vm_func_lld(t_vm *vm, t_process *process);
int					vm_func_lldi(t_vm *vm, t_process *process);
int					vm_func_lfork(t_vm *vm, t_process *process);
int					vm_func_aff(t_vm *vm, t_process *process);

#endif
