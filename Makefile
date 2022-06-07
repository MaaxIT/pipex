# pipex - A redirection pipe project
# Use this makefile to compile the project

# Compile informations
NAME		=	pipex
SANIFLAG	=	-fsanitize=address
FLAGS		=	-Wall -Wextra -Werror $(SANIFLAG)

# Some constants values
INC_PATH	=	inc/
SRC_PATH	=	src/
INC_PATH	=	inc/

# Import our printf project
PRINTF_PATH =	ft_printf/
PRINTF_LIB	=	$(PRINTF_PATH)libftprintf.a
PRINTF_INC	=	$(PRINTF_PATH)inc/

# Import our libft project
LIBFT_PATH =	libft/
LIBFT_LIB	=	$(LIBFT_PATH)libft.a
LIBFT_INC	=	$(LIBFT_PATH)inc/

# This is all the source files we want to compile
SRC_FILES	=	pipex.c utils.c args.c path.c
OBJS		=	$(addprefix $(SRC_PATH), $(SRC_FILES:%.c=%.o))

# Our compile rules
%.o: %.c
	gcc $(FLAGS) -I$(INC_PATH) -I$(LIBFT_INC) -I$(PRINTF_INC) -c $< -o $@

$(NAME): 	$(OBJS)
	make -C $(LIBFT_PATH)
	make -C $(PRINTF_PATH)
	gcc $(FLAGS) $(OBJS) $(LIBFT_LIB) $(PRINTF_LIB) -o $(NAME)

# Our mandatory rules
all:		$(NAME)

clean:
	make clean -C $(LIBFT_PATH)
	make clean -C $(PRINTF_PATH)
	rm -rf $(OBJS)

fclean:		clean
	make fclean -C $(LIBFT_PATH)
	make fclean -C $(PRINTF_PATH)
	rm -f $(NAME)

re:			fclean all
	make re -C $(LIBFT_PATH)
	make re -C $(PRINTF_PATH)

.PHONY:		all clean fclean re