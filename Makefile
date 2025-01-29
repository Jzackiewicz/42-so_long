NAME = so_long

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

SOURCES =	main.c input_handling.c map_checking.c \
			map_loading.c utils.c map_checking_utils.c \
			graphics.c moving_character.c

OBJECTS_DIR = obj
OBJECTS = $(addprefix $(OBJECTS_DIR)/, $(SOURCES:.c=.o))

LIBFT_DIR = includes/libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_PATH = includes/mlx
MLX = $(MLX_PATH)/libmlx.a

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_PATH)

$(NAME): $(OBJECTS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBFT) $(MLX) -Imlx_linux -lXext -lX11 -lm -lz

$(OBJECTS_DIR)/%.o: %.c | $(OBJECTS_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJECTS_DIR):
	mkdir -p $(OBJECTS_DIR)

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_PATH) clean
	rm -rf $(OBJECTS_DIR)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	make -C $(MLX_PATH) clean
	rm -f $(MLX)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
