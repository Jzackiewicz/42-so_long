NAME = so_long

CC = cc
CFLAGS = -Wall -Werror -Wextra

SOURCES = main.c 
OBJECTS = $(SOURCES:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_PATH = ./mlx
MLX =	$(MLX_PATH)/libmlx.a
MLX_FLAGS = -Lmlx -Imlx -L/usr/lib/X11 -lXext -lX11

INCLUDES = -I/opt/X11/include -Imlx

all: $(MLX_LIB) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

$(NAME): $(OBJECTS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX_FLAGS)

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJECTS) 

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
