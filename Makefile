NAME = cube3d
CC = cc
Cflags = -Wall -Wextra -Werror #-g3 -fsanitize=address
MLX = -lmlx -lXext -lX11 -lm -lpng -lz -O3


SRC = cube3d.c get_next_line.c get_next_line_utils.c mlx_functions.c pov.c map_build.c player_movement.c \
	calculations.c \
	utils.c ft_split.c check_file.c pars_map.c init.c check_map.c check_colors.c check_textures.c to_map.c\

OBJ = $(SRC:.c=.o)

all:$(NAME)

$(NAME) : $(OBJ)
		$(CC) $(Cflags) $(OBJ) $(MLX) -o $(NAME) 	

clean:
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re: fclean all
