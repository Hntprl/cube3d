NAME = cub3d
BNAME = cub3d_bonus
CC = cc
Cflags = -Wall -Wextra -Werror 
MLX = -lmlx -lXext -lX11 -lm -O3
RM = rm -f
SRC_DIR := src
PARS_DIR := pars


SRC := $(SRC_DIR)/cube3d.c \
       $(SRC_DIR)/get_next_line.c \
       $(SRC_DIR)/get_next_line_utils.c \
       $(SRC_DIR)/mlx_functions.c \
       $(SRC_DIR)/map_build.c \
       $(SRC_DIR)/player_movement.c \
       $(SRC_DIR)/raycasting.c \
       $(SRC_DIR)/calculations.c \
       $(SRC_DIR)/ft_malloc.c \
       $(SRC_DIR)/raycasting_fixes.c \
       $(SRC_DIR)/raycasting2.c \
       $(SRC_DIR)/key_hook.c \
       $(SRC_DIR)/key_hook2.c \
       $(SRC_DIR)/utils2.c \
       $(SRC_DIR)/textures.c \


PARS := $(PARS_DIR)/check_colors.c \
	$(PARS_DIR)/check_file.c \
	$(PARS_DIR)/check_map.c \
	$(PARS_DIR)/check_textures.c \
	$(PARS_DIR)/ft_split.c \
	$(PARS_DIR)/init.c \
	$(PARS_DIR)/pars_map.c \
	$(PARS_DIR)/to_map.c \
	$(PARS_DIR)/utils.c \
	$(PARS_DIR)/utils2.c \


SRCS := $(SRC) $(PARS) Mandatory/main.c 
BBRCS := $(SRC) $(PARS) Bonus/main_bonus.c

OBJ := $(SRCS:.c=.o)
BOBJ := $(BBRCS:.c=.o)

all:$(NAME)

bonus : $(BNAME)

$(BNAME) : $(BOBJ) cube3d.h
	$(CC) $(BOBJ) $(MLX) -o $(BNAME)

$(NAME) : $(OBJ) cube3d.h
	$(CC)  $(OBJ) $(MLX) -o $(NAME)

%.o: %.c
	$(CC) $(Cflags) -c $< -o $@

clean:
	$(RM) $(OBJ) $(BOBJ)

fclean : clean
	$(RM) $(NAME) $(BNAME)

re: fclean all

.PHONY: all clean fclean re bonus
