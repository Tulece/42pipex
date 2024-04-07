NAME		=	pipex
NAME_BONUS	=	pipex_bonus
CC			=	cc
FLAGS		=	-g -Wall -Werror -Werror
LIBFT_PATH	=	libft/
LIBFT_FILE	=	libft/libft.a

SRC			=	$(wildcard src/*.c)
OBJ			=	$(patsubst %.c,%.o,$(SRC))
SRC_BONUS	=	$(wildcard src_bonus/*.c)
OBJ_BONUS	=	$(patsubst %.c,%.o,$(SRC_BONUS))
RM 			=	rm -f

.SUFFIXES: .c .o

$(NAME): $(OBJ)
	make -C libft/
	$(CC) $(FLAGS) $(OBJ) $(LIBFT_FILE) -o $(NAME) -I includes/

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@ -I includes/


all: $(NAME)

bonus: $(NAME_BONUS)
$(NAME_BONUS): $(OBJ_BONUS)
	make -C libft/
	$(CC) $(FLAGS) $(OBJ_BONUS) $(LIBFT_FILE) -o $(NAME_BONUS) -I includes/

clean:
	@echo "Deleting Obj file in $(LIBFT_PATH)...\n"
	@make clean -sC $(LIBFT_PATH)
	@echo "Done\n"
	@echo "Deleting Push Swap object...\n"
	@rm -f $(OBJ)
	@rm -f $(OBJ_BONUS)
	@echo "Done\n"

fclean: clean
	@echo "Deleting Push_Swap executable..."
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@make fclean -C $(LIBFT_PATH)
	@echo "Done\n"

re: fclean all

.PHONY: all clean fclean re
