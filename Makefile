NAME = cube3d
CC = gcc
Cflags = -Wall -Wextra -Werror 
MLX =  -lmlx -lXext -lX11 -lm -lpng -lz -O3


SRC = src/cube3d.c src/get_next_line.c src/get_next_line_utils.c src/mlx_functions.c src/map_build.c src/player_movement.c src/raycasting.c\
	src/calculations.c src/ft_malloc.c src/raycasting_fixes.c src/raycasting2.c src/key_hook.c src/utils2.c\

OBJ = $(SRC:.c=.o)

all:$(NAME)

$(NAME) : $(OBJ)
		$(CC) $(Cflags) $(OBJ) $(MLX) -o $(NAME) -fsanitize=address	

clean:
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re: fclean all
