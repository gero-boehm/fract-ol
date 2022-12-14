CC=cc
CFLAGS=-Wall -Wextra -Werror -I MLX42/include -I include -I lib/libft
NAME=fractals
SRC_DIR=src
OBJ_DIR=_bin
LIB_DIR=lib
SRC=main.c color.c complex.c calculate.c hooks.c hue2rgb.c setup.c uniforms.c vec2.c info.c malloc2.c dtoa2.c ops.c update.c info_str.c info_utils.c
OBJ=$(addprefix _bin/, $(SRC:.c=.o))
LIBS=MLX42/libmlx42.a -lglfw -L "/Users/$$USER/.brew/opt/glfw/lib/" -framework Cocoa -framework OpenGL -framework IOKit
HEADERS=src/fract_ol.h

all: $(NAME)
	./$<

$(OBJ_DIR):
	mkdir $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) -o $@ $<

$(LIB_DIR)/libft/libft.a:
	$(shell cd $(LIB_DIR) && git clone https://github.com/gero-boehm/libft.git)
	make -C $(LIB_DIR)/libft
	make -C clean

$(NAME): $(OBJ) $(LIB_DIR)/libft/libft.a
	make -C MLX42
	$(CC) $(CFLAGS) -o $(NAME) $^ $(LIBS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

norm:
	norminette $(addprefix $(SRC_DIR)/, $(SRC)) $(HEADERS)

.PHONY:
	all bonus clean fclean re norm