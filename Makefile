NAME= minishell

SRCS= check_tokens.c  ft_split.c minishell.c  word_counter.c utils.c

OBJS=$(SRCS:.c=.o)

HEADER= minishell.h

CC=cc

CFLAGS= -Wall -Wextra -g -fsanitize=address

RM= rm -rf

$(NAME) : $(OBJS) $(HEADER)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

$(OBJS): %.o : %.c $(HEADER)
		$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean: 
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

run: re 
	 clear && ./$(NAME)