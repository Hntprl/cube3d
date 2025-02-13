NAME = cube3d
CC = cc
Cflags = -Wall -Wextra -Werror 
MLX =  -lmlx -lXext -lX11 -lm -lpng -lz -O3


SRC = src/cube3d.c src/get_next_line.c src/get_next_line_utils.c src/mlx_functions.c src/map_build.c src/player_movement.c src/raycasting.c\
	src/calculations.c src/ft_malloc.c src/raycasting_fixes.c src/raycasting2.c src/key_hook.c src/utils2.c src/animation.c\
	pars/check_colors.c  pars/check_file.c  pars/check_map.c  pars/check_textures.c  pars/ft_split.c  pars/init.c  pars/pars_map.c  pars/to_map.c  pars/utils.c \

OBJ = $(SRC:.c=.o)

all:$(NAME)

$(NAME) : $(OBJ)
		$(CC) $(Cflags) $(OBJ) $(MLX) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re: fclean all
