# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguille <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/13 21:19:28 by mguille           #+#    #+#              #
#    Updated: 2023/01/20 23:01:39 by mguille          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_MAIN = ./srcs/main.c

DIR_SRC =       ./srcs/
SRC_FILES =     parsing.c

DIR_TRIE =      ./srcs/trie/
TRIE_FILES =    trie_moyen.c             \
                trie_de_3.c              \
                trie_general.c           \
                trie_mediane_inferieur.c \
                trie_mediane_superieur.c \
                verif_trie.c

DIR_UTILS =     ./utils/
UTILS_FILES =   struct_free.c    \
                struct.c        \
                utile.c

DIR_INSTRUCTION =   ./Instruction/
INSTRUCTION_FILES = instructions.c                    \
                    push_a.c                        \
                    push_b.c                        \
                    reverse_rotate_a.c              \
                    reverse_rotate_b.c              \
                    reverse_rotate_reverse_rotate.c  \
                    rotate_a.c                      \
                    rotate_b.c                      \
                    rotate_rotate.c                 \
                    swap_a.c                        \
                    swap_b.c                        \
                    swap_swap.c

SRC_WITHOUT_MAIN =  $(addprefix $(DIR_SRC), $(SRC_FILES))      \
                    $(addprefix $(DIR_UTILS), $(UTILS_FILES))  \
                    $(addprefix $(DIR_TRIE), $(TRIE_FILES))    \
                    $(addprefix $(DIR_INSTRUCTION), $(INSTRUCTION_FILES))

SRC =   $(SRC_MAIN) \
        $(SRC_WITHOUT_MAIN)

DIR_BONUS =     ./bonus/
BONUS_FILES =   main.c                              \
                parsing_param.c                     \
                struct_bonus.c

SRC_BONUS = $(addprefix $(DIR_BONUS), $(BONUS_FILES)) \
            $(SRC_WITHOUT_MAIN)

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)
NAME = push_swap
NAME_BONUS = checker
CC = cc
RM = rm -rf
FLAGS = -Wall -Werror -Wextra -g3

MAKE_LIBFT = make -s -C ./libft
LIBFT_A = ./libft/libftprintf.a

# Codes de couleur ANSI
YELLOW = \033[1;33m
BLUE = \033[1;34m
RED = \033[1;31m
RESET = \033[0;39m

$(NAME): $(OBJ)
	$(MAKE_LIBFT)
	@echo "$(YELLOW)Compilation en cours... $< $(RESET)"
	$(CC) $(FLAGS) $(OBJ) $(LIBFT_A) -o $(NAME)
	@echo "$(BLUE)$(NAME) a été compilé avec succès.$(RESET)"

all : $(NAME)

bonus: $(OBJ_BONUS)
	$(MAKE_LIBFT)
	@echo "$(YELLOW)Compilation en cours...$(RESET)"
	$(CC) $(FLAGS) $(OBJ_BONUS) $(LIBFT_A) -o $(NAME_BONUS)
	@echo "$(BLUE)$(NAME_BONUS) a été compilé avec succès.$(RESET)"

.c.o:
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

clean :
	$(MAKE_LIBFT) fclean
	@echo "$(RED)Nettoyage en cours...$(RESET)"
	$(RM) $(OBJ)
	$(RM) $(OBJ_BONUS)
	@echo "$(BLUE)Nettoyage terminé.$(RESET)"

fclean : clean
	$(MAKE_LIBFT) fclean
	@echo "$(RED)Suppression de l'exécutable en cours...$(RESET)"
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)
	@echo "$(BLUE)Suppression terminée.$(RESET)"

re : fclean all

################# Commande perso

# Verifie la norminette
norme:
	@ clear
	@ if ! norminette | grep "Error"; then echo "$(GREEN)OK!$(RESET)"; fi

propre:
	@ make all -s
	@ make clean -s

test:
	@ clear
	@ make propre -s
	@ echo "Resultat du programme ./push_swap : "
	@ echo
	@ ./push_swap

val:
	@ clear
	@ make propre -s
	@ echo "Resultat du programme ./push_swap : "
	@ echo
	valgrind --leak-check=full --show-leak-kinds=all ./push_swap

#################

.PHONY : all clean fclean re
