SRCS = main.c \
	so_long_utils.c \
	check_map.c \
	check_map2.c \
	render_map.c \
	hooks.c \
	get_next_line_utils.c \
	get_next_line.c

OBJS = $(SRCS:.c=.o)

MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror
LINKS = -lX11 -lXext -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft

all: $(NAME)

$(NAME): $(MLX) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LINKS) -o $(NAME)

$(MLX):
	make -C $(MLX_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
