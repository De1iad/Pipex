NAME	=	pipex
CC		=	gcc
FLAGS	=	-Wall -Wextra -Werror
OBJ_DIR	=	obj/
LIBFT_D	=	libft/
SRCS	=	pipex.c
OBJS	=	$(SRCS:%.c=$(OBJ_DIR)%.o)
LIBFT	=	$(LIBFT_D)libft.a
GREY	=	\33[1;30m
BLUE	=	\33[0;34m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@printf "$(GREY)Compiling $(BLUE)$(NAME)\n"
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@printf "$(GREY)Entering $(BLUE)$(LIBFT_D)\n"
	@make -s -C $(LIBFT_D)

$(OBJ_DIR)%.o: $(SRCS)
	@mkdir -p $(@D)
	@printf "$(GREY)Compiling $(BLUE)$< $(GREY)> $(BLUE)$@\n"
	@$(CC) $(FLAGS) -c $< -o $@ 

clean:
	@printf "$(GREY)Cleaning $(BLUE)$(OBJ_DIR)\n"
	@rm -fr $(OBJ_DIR)
	@printf "$(GREY)Cleaning $(BLUE)libft/\n"
	@make clean -s -C libft/

fclean: clean
	@printf "$(GREY)Deleting $(BLUE)$(NAME)\n"
	@rm -f $(NAME)
	@printf "$(GREY)Deleting $(BLUE)$(LIBFT)\n"
	@make fclean -s -C libft/

re: fclean all
