# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/26 20:01:08 by sikpenou          #+#    #+#              #
#    Updated: 2020/04/21 11:26:09 by skpn             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../vm

CC = $(COMPILER) $(COMPILATION_FLAGS) $(DEBUG_FLAGS) $(INCLUDE_FLAGS)

COMPILER = clang

COMPILATION_FLAGS = -Wall -Werror -Wextra

DEBUG_FLAGS = -g3 -fsanitize=address -fsanitize=leak

INCLUDE_FLAGS = $(foreach dir, $(INC_DIR), -I $(dir)) 

INC_DIR = $(shell find .. -type d -name 'inc')

SRC_DIR = $(shell find src -type d)

LIB_DIR = $(shell find ../lib -mindepth 1 -maxdepth 1 -type d)

LIBS += \
	../lib/libft/libft.a

OBJ_DIR = obj

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# BASIC
SRCS += \
		charge_players.c \
		init_structs_vm.c \
		main_vm.c \
		manage_end_of_cycle.c \
		process_loop.c

# DISPLAY
SRCS += \
		log_cycles_vm.c \
		log_vm.c \
		set_dump.c \
		update_dump.c

# EXIT
SRCS += \
		exit_vm.c

# OP
SRCS += \
		vm_func_01_live.c \
		vm_func_02_ld.c \
		vm_func_03_st.c \
		vm_func_04_add.c \
		vm_func_05_sub.c \
		vm_func_06_and.c \
		vm_func_07_or.c \
		vm_func_08_xor.c \
		vm_func_09_zjmp.c \
		vm_func_10_ldi.c \
		vm_func_11_sti.c \
		vm_func_12_fork.c \
		vm_func_13_lld.c \
		vm_func_14_lldi.c \
		vm_func_15_lfork.c \
		vm_func_16_aff.c

# PARSING
SRCS += \
		parse_args.c \
		parse_champion.c \
		parse_op_args_value.c \
		parse_op.c \
		parse_options.c

# TOOLS
SRCS += \
		address_tools.c \
		endian_conversion.c

SRCS += \
		op.c

INCS += \
		corewar_vm.h \
		libft.h

vpath %.c $(foreach dir, $(SRC_DIR), $(dir):)
vpath %.h $(foreach dir, $(INC_DIR), $(dir):)
vpath %.a $(foreach dir, $(LIB_DIR), $(dir):)

all: $(NAME) Makefile

$(NAME): $(INCS) $(LIBS) $(OBJS)
	/bin/echo compiling $(shell basename $(NAME))
	$(CC) -o $(NAME) $(OBJS) $(LIBS)

$(OBJ_DIR)/%.o : %.c $(INCS) $(LIBS)
	mkdir -p $(OBJ_DIR)
	$(CC) -o $@ -c $<

$(LIBS): FORCE
	make -C $(LIB_DIR)

clean: FORCE
	rm -rf $(OBJS)
	rm -rf $(OBJ_DIR)
	make clean -C $(LIB_DIR)

fclean: clean FORCE
	rm -rf $(NAME)
	make fclean -C $(LIB_DIR)

re: fclean all FORCE

show:
	echo "comp   : $(CC)\n"
	echo "src_dir: $(SRC_DIR)\n"
	echo "inc_dir: $(INC_DIR)\n"
	echo "lib_dir: $(LIB_DIR)\n"
	echo "srcs   : $(SRCS)\n"
	echo "incs   : $(INCS)\n"
	echo "libs   : $(LIBS)\n"

FORCE:

.SILENT:
