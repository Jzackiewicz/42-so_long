NAME = so_long

CC = cc
CFLAGS = -Wall -Werror -Wextra

SOURCES = main.c input_handling.c map_checking.c map_loading.c utils.c map_checking_utils.c
OBJECTS = $(SOURCES:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_PATH = mlx
MLX =	$(MLX_PATH)/libmlx.a

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

 $(MLX):
	make -C $(MLX_PATH)

$(NAME): $(OBJECTS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBFT) $(MLX) -Imlx_linux -lXext -lX11 -lm -lz

$(OBJECTS): %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_PATH) clean
	rm -f $(OBJECTS) 

fclean: clean
	make -C $(LIBFT_DIR) fclean
	make -C $(MLX_PATH) clean
	rm -f $(MLX)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
