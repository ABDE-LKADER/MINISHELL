# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: darkab <darkab@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/19 17:23:22 by abadouab          #+#    #+#              #
#    Updated: 2024/06/13 21:14:27 by darkab           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

SRCS		=	minishell.c \
				inject_spaces.c command_checkers.c  \
				check_tokens.c word_counter.c ft_split_op.c \
				errors.c parse_checkers.c parse_simple_command.c \
				signal_handler.c parse.c here_doc.c environment.c  \
				expanding.c execution.c check_redirection.c \
				check_operate.c pipeline.c redirection.c \
				builtins/handle_builtins.c builtins/ft_echo.c \
				builtins/ft_pwd.c builtins/ft_exit.c \
				builtins/ft_env.c builtins/ft_export.c \
				builtins/ft_unset.c

OBJS		=	$(SRCS:.c=.o)
HEADER		=	minishell.h

MYLB		=	MYLIB
MYAR		=	MYLIB/libar.a

CC			=	cc
FLAGS		=	-Wall -Wextra -g -fsanitize=address # -Werror
SHORT		=	-L$(MYLB) -lar -L ~/.brew/opt/readline/lib -lreadline
RM			=	rm -fr

GREEN		=	"\033[1;32m"
YELOW		=	"\033[1;33m"
REDCL		=	"\033[1;31m"
RESET		=	"\033[0m"

all: start $(MYLB) $(NAME) finish

start:
	@printf "\n"
	@echo $(GREEN)"Starting build..."
	@sleep 1
	@printf "Loading [ "

finish:
	@echo $(GREEN) ] 100%$(RESET)
	@echo $(GREEN)Project built.$(RESET)
	@printf "\n"

$(MYLB):
	@make -C $(MYLB) --no-print-directory

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $^ $(SHORT) -o $(NAME)

$(OBJS): %.o: %.c $(HEADER) $(MYAR)
	@$(CC) $(FLAGS) -c -I $(MYLB) -I . -I ~/.brew/opt/readline/include $< -o $@
	@printf $(GREEN)"."$(RESET)

clean:
	@$(RM) $(OBJS)
	@$(RM) $(OBJS_BONUS)
	@make clean -C $(MYLB) --no-print-directory
	@echo $(YELOW)Cleaning up 🧹💫$(RESET)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(NAME_BONUS)
	@make fclean -C $(MYLB) --no-print-directory
	@echo $(REDCL)Purging all files 🗑️$(RESET)

re: fclean all

run: all clean
		clear && ./minishell

.PHONY: $(MYLB)
