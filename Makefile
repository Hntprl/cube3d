NAME = cube3d
CC = gcc
Cflags = -Wall -Wextra -Werror
MLX = -lmlx -lXext -lX11 -lm -lpng -lz -O3


SRC = cube3d.c get_next_line.c get_next_line_utils.c mlx_functions.c pov.c map_build.c player_movement.c \
	calculations.c \
	utils.c ft_split.c check_file.c pars_map.c init.c\

OBJ = $(SRC:.c=.o)

all:$(NAME)

$(NAME) : $(OBJ)
		$(CC) $(Cflags) $(OBJ) $(MLX) -o $(NAME) -fsanitize=address	

clean:
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re: fclean all
