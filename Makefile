# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/26 20:01:08 by sikpenou          #+#    #+#              #
#    Updated: 2020/04/21 19:48:31 by skpn             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM_DIR=asm_dir
ASM=asm

VM_DIR=vm_dir
VM=vm

LIB_DIR=lib/libft
LIB=$(LIB_DIR)/libft.a

all: $(LIB) $(ASM) $(VM) Makefile

$(ASM): FORCE
	make -C $(ASM_DIR)

$(VM): FORCE
	make -C $(VM_DIR)

$(LIB): FORCE
	make -C $(LIB_DIR)

clean: FORCE
	make clean -C $(LIB_DIR)
	make clean -C $(ASM_DIR)
	make clean -C $(VM_DIR)
	rm -f $(ASM_DIR)/auteur
	rm -f $(VM_DIR)/auteur

fclean: clean FORCE
	make fclean -C $(LIB_DIR)
	make fclean -C $(ASM_DIR)
	make fclean -C $(VM_DIR)

re: fclean all FORCE

FORCE:

.SILENT:
