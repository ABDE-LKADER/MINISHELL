# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/19 17:23:22 by abadouab          #+#    #+#              #
#    Updated: 2024/07/27 19:02:59 by abadouab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

SRCS		=	more/minishell.c more/environment.c \
				tokinizer/inject_spaces.c tokinizer/check_tokens.c \
				tokinizer/word_counter.c tokinizer/ft_split_op.c \
				tokinizer/check_operate.c \
				parcer/parse.c parcer/parse_simple_command.c \
				parcer/parse_checkers.c  parcer/command_checkers.c \
				parcer/check_redirection.c \
				execution/execution.c execution/builtins.c execution/pipeline.c \
				expander/expander.c expander/expanding.c expander/expand_val.c \
				expander/expand_plus.c expander/here_doc_ex.c expander/wildcards_ex.c \
				redirection/redirection.c redirection/restore_fds.c \
				redirection/here_doc.c \
				builtins/echo.c builtins/pwd.c builtins/exit.c \
				builtins/env.c builtins/export.c builtins/unset.c builtins/cd.c \
				signals/sig_handler.c signals/sig_childer.c \
				tools/tokens_tools.c tools/split_args.c tools/termios.c tools/errors.c

OBJS		=	$(SRCS:.c=.o)
HEADER		=	includes/minishell.h

MYLB		=	MYLIB
MYAR		=	MYLIB/libar.a

CC			=	cc
FLAGS		=	-Wall -Wextra -Werror
SHORT		=	-L$(MYLB) -lar -lreadline
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
	@$(CC) $(FLAGS) -c -I $(MYLB) -I includes $< -o $@
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
