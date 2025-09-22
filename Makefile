SRCS = main.c \
	check_map.c \
	render_map.c \
	hooks.c \
	get_next_line_utils.c \
	get_next_line.c

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -O0 -fsanitize=address
LINKS = -L/opt/X11/lib -lX11 -lXext -lmlx_Darwin -L$(LIBFT_DIR) -lft -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(LINKS) $(OBJS) -o $(NAME)
	dsymutil $@

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

# cc -Wall -Wextra -Werror -L/opt/X11/lib -lX11 -lXext -lmlx_Darwin -framework OpenGL -framework AppKit so_long.c -o so_long
