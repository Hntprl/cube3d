NAME = cube3d
CC = gcc
Cflags = -Wall -Wextra -Werror
MLX = -lmlx -lXext -lX11 -lm -lpng -lz -O3


SRC = cube3d.c get_next_line.c get_next_line_utils.c mlx_functions.c \
	calculations.c \

OBJ = $(SRC:.c=.o)

all:$(NAME)

$(NAME) : $(OBJ)
		$(CC) $(Cflags) $(OBJ) $(MLX) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re: fclean all
