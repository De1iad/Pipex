NAME	=	libft.a
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
OBJ_DIR	=	obj/
SRCS	=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c $(wildcard ft_printf/*.c)
OBJS	=	$(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
GREY	=	\33[1;30m
BLUE	=	\33[0;34m
GREEN	=	\e[1;32m

all:	$(NAME)

$(NAME): $(OBJS)
	@printf "\n$(GREY)Archiving $(BLUE)$(NAME)$(GREY)\n"
	@ar -cr $(NAME) $(OBJS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@printf "\r$(GREY)Compiling $(BLUE)$@"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -fr $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all