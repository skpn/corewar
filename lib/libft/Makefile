# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 21:32:05 by sikpenou          #+#    #+#              #
#    Updated: 2020/04/14 14:59:02 by skpn             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = $(COMPILER) $(COMPILATION_FLAGS) $(DEBUG_FLAGS) $(INCLUDE_FLAGS)

COMPILER = clang

COMPILATION_FLAGS = -Wall -Werror -Wextra

DEBUG_FLAGS = -g3 -fsanitize=address -fsanitize=leak

INCLUDE_FLAGS = $(foreach dir, $(INC_DIR), -I $(dir)) 

INC_DIR = $(shell find . -name 'inc' -type d)

SRC_DIR = $(shell find src -type d)

OBJ_DIR = obj

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

SRCS += \
			dynamic_array.c

SRCS += \
			ft_abs.c \
			ft_atoi.c \
			ft_atoi_base.c \
			ft_check_base.c \
			ft_convert_base.c \
			ft_find_next_prime.c \
			ft_ischarset.c \
			ft_isspace.c \
			ft_max.c \
			ft_min.c \
			ft_pow.c \
			ft_putnbr.c \
			ft_swap.c \
			ft_tabmap.c \

SRCS += \
			ft_errors.c

SRCS += \
			ft_itoa.c \
			ft_itoa_base.c \
			ft_strchr_pos.c \
			ft_strcmp.c \
			ft_strcmp_heap.c \
			ft_strcpy.c \
			ft_strcpy_heap.c \
			ft_strdup.c \
			ft_strjoin.c \
			ft_strjoin_free.c \
			ft_strlen.c \
			ft_strlen_heap.c \
			ft_strncmp.c \
			ft_strrchr.c \
			ft_strstr.c \
			ft_strsub.c \
			ft_ulltoa.c \
			ft_ulltoa_base.c

SRCS += \
			ft_lstadd.c \
			ft_lstadd_sorted.c \
			ft_lstadd_back.c \
			ft_lstadd_back_new.c \
			ft_lstadd_new.c \
			ft_lstcpy.c \
			ft_lstcycle.c \
			ft_lstfind.c \
			ft_lstfree.c \
			ft_lstfree_elem.c \
			ft_lstfree_head.c \
			ft_lstinsert.c \
			ft_lstjoin.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_lstnew_elem.c \
			ft_lstnew_head.c \
			ft_lstpop.c \
			ft_lstpop_elem.c \
			ft_lstprint.c

SRCS += \
			ft_free.c \
			ft_memalloc.c \
			ft_memchr.c \
			ft_memchr_pos.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memset.c \
			ft_realloc.c

SRCS += \
			garbage_collector.c

SRCS += \
			hash_tables_access.c \
			hash_tables_free.c \
			hash_tables_funcs.c \
			hash_tables_display.c \
			hash_tables_insert.c \
			hash_tables_init.c

SRCS += \
			pf_core.c \
			pf_expand_numbers.c \
			pf_expand_text.c \
			pf_ft_printf.c \
			pf_padding.c \
			pf_parsing.c

SRCS += \
			read_file.c

INCS += \
		ft_dynamic_array.h \
		ft_errors.h \
		ft_garbage_collector.h \
		ft_hash_tables.h \
		ft_lst.h \
		ft_printf.h \
		ft_read_file.h \
		libft.h

vpath %.c $(foreach dir, $(SRC_DIR), $(dir):)
vpath %.h $(foreach dir, $(INC_DIR), $(dir):)
vpath %.a $(foreach dir, $(LIB_DIR), $(dir):)

all: $(NAME)

$(NAME): $(INCS) $(LIBS) $(OBJS) Makefile
	/bin/echo compiling $(NAME)
	ar rc $(NAME) $(OBJS)

$(OBJ_DIR)/%.o : %.c $(INCS) $(LIBS) Makefile
	mkdir -p $(OBJ_DIR)
	$(CC) -o $@ -c $<

$(LIBS): FORCE
	make -C $(LIB_DIR)

clean: FORCE
	rm -rf $(OBJS)

fclean: clean FORCE
	rm -rf $(NAME)

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
