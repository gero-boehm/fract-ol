CC=cc
CFLAGS=-Wall -Wextra -Werror -I MLX42/include -I include -I lib/libft -g
NAME=fractals
SRC_DIR=src
OBJ_DIR=_bin
LIB_DIR=lib
SRC=calculate.c color.c complex.c dtoa2.c eval_ops.c hooks.c hue2rgb.c info_str.c info_utils.c info.c main.c malloc2.c ops.c parser.c setup.c uniforms.c update.c vec2.c
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
	(cd $(LIB_DIR)/libft && make && make clean)

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