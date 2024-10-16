# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anastruc <anastruc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/08 15:22:31 by anastruc          #+#    #+#              #
#    Updated: 2024/10/16 14:23:33 by anastruc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philosopher
COMPIL = cc
FLAGS = -Wall -Werror -Wextra -pthread -g3 -fPIC
# -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fsanitize=integer -fsanitize=null -fsanitize=unreachable
#ATTENTION FLAG A UTILISER SEPAREMENT DE VALGRIND
PINK = \033[1;35m
BLUE = \033[1;36m
NC = \033[0m

HEADER_F = headers/function.h \
			headers/structure.h \

MANDATORY_SRCS = parsing.c \
				 parsing_utils.c \
				 main.c \
				 init.c \
				 philosopher_thread.c \
				 philosopher_thread_utils.c \
				monitor_thread.c \
				getter_setter.c \
				getter_setter2.c \
				getter_setter3.c \
				getter_setter4.c \
				support_function.c \
				clean_and_free.c \

# Magic with srcs and objs #

PMANDATORY = $(addprefix srcs/, $(MANDATORY_SRCS))


M_OBJS = $(PMANDATORY:srcs/%.c=objs/%.o)

all : $(NAME)

objs/%.o: srcs/%.c $(HEADER_F)
	@mkdir -p objs
	@$(COMPIL) $(FLAGS) -c $< -o $@

$(NAME) : $(M_OBJS)  $(HEADER_F)
	@$(COMPIL) $(FLAGS) -o $@ $(M_OBJS)
	@echo  "$(BLUE)\n    PHILOSOPHER COMPILED \n$(NC)"

clean :
	@rm -rf objs
	@echo  "$(BLUE) \n     PHILOSOPER CLEANED \n$(NC)"

fclean : clean
	@rm -f $(NAME)

data_race:
	@valgrind --tool=helgrind ./$(NAME) $(ARGS)

leak :
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(NAME) $(ARGS)

re : fclean all

.PHONY : all clean fclean re bonus




# clear && make && valgrind --suppressions=ignore_leak_readline --leak-check=full --show-leak-kinds=all  --trace-children=yes ./minishell

