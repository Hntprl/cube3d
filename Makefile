NAME = cube3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
MLX = -lmlx -lXext -lX11 -lm -lpng -lz -O3

SRC = calculations.c \
      cube3d.c \
      get_next_line_utils.c \
      mlx_functions.c \
      raycasting_fixes.c \
      check_colors.c \
      init.c \
      pars_map.c \
      check_file.c \
      ft_malloc.c \
      player_movement.c \
      to_map.c \
      check_map.c \
      ft_split.c \
      map_build.c \
      raycasting2.c \
      utils.c \
      check_textures.c \
      get_next_line.c \
      raycasting.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
