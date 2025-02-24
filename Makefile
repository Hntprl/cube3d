NAME = cub3d
BNAME = cub3d_bonus
CC = cc
Cflags = -Wall -Wextra -Werror
MLX = -lmlx -lXext -lX11 -lm -O3 
RM = rm -f
M_SRC_DIR := Mandatory/src
B_SRC_DIR := Bonus/src
PARS_DIR := pars

BSRC := $(B_SRC_DIR)/cube3d.c \
	$(B_SRC_DIR)/get_next_line.c \
	$(B_SRC_DIR)/get_next_line_utils.c \
	$(B_SRC_DIR)/mlx_functions.c \
	$(B_SRC_DIR)/map_build.c \
	$(B_SRC_DIR)/player_movement.c \
	$(B_SRC_DIR)/raycasting.c \
	$(B_SRC_DIR)/calculations.c \
	$(B_SRC_DIR)/ft_malloc.c \
	$(B_SRC_DIR)/raycasting_fixes.c \
	$(B_SRC_DIR)/raycasting2.c \
	$(B_SRC_DIR)/key_hook.c \
	$(B_SRC_DIR)/key_hook2.c \
	$(B_SRC_DIR)/utils2.c \
	$(B_SRC_DIR)/textures.c \

SRC := $(M_SRC_DIR)/cube3d.c \
       $(M_SRC_DIR)/get_next_line.c \
       $(M_SRC_DIR)/get_next_line_utils.c \
       $(M_SRC_DIR)/mlx_functions.c \
       $(M_SRC_DIR)/map_build.c \
       $(M_SRC_DIR)/player_movement.c \
       $(M_SRC_DIR)/raycasting.c \
       $(M_SRC_DIR)/calculations.c \
       $(M_SRC_DIR)/ft_malloc.c \
       $(M_SRC_DIR)/raycasting_fixes.c \
       $(M_SRC_DIR)/raycasting2.c \
       $(M_SRC_DIR)/key_hook.c \
       $(M_SRC_DIR)/utils2.c \
       $(M_SRC_DIR)/textures.c \


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


SRCS := $(SRC) $(PARS)
BBRCS := $(BSRC) $(PARS)

OBJ := $(SRCS:.c=.o)
BOBJ := $(BBRCS:.c=.o)

all:$(NAME)

bonus : $(BOBJ)
	$(CC) $(BOBJ) $(MLX) -o $(BNAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) $(MLX) -o $(NAME)

%.o: %.c
	$(CC) $(Cflags) -c $< -o $@  

clean:
	$(RM) $(OBJ) $(BOBJ)

fclean : clean
	$(RM) $(NAME) $(BNAME)

re: fclean all

.PHONY: all clean fclean re bonus
