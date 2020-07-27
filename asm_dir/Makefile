# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/26 20:01:08 by sikpenou          #+#    #+#              #
#    Updated: 2020/04/21 14:52:19 by skpn             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../asm

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
		main_asm.c \

# DEBUG
SRCS += \
		debug.c \
		debug_token.c

# EXIT
SRCS += \
		error_cwr.c \
		exit_cwr.c

# HEADER
SRCS += \
		parse_header.c

# INIT
SRCS += \
		init_structs.c

# LABELS
SRCS += \
		labels.c \
		label_refs.c

# LINE
SRCS += \
		line_to_prog.c

# OUTPUT
SRCS += \
		output.c

# PROG
SRCS += \
		parse_prog.c

# TOKEN
SRCS += \
		check_tokens.c \
		get_tokens_contents.c \
		parse_tokens.c

# TOOLS
SRCS += \
		tools.c \
		tools_skip.c

SRCS += \
		op.c

INCS += \
		corewar_asm.h \
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
