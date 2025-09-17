SRCS = main.c \
	render_map.c \
	hooks.c

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror
LINKS = -L/opt/X11/lib -lX11 -lXext -lmlx_Darwin -L$(LIBFT_DIR) -lft -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(LINKS) -g $(OBJS) -o $(NAME)

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
