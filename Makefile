CC=cc
CFLAGS=-Wall -Wextra -Werror -IMLX42/include -Iinclude
NAME=libft.a
SRC=vec2.c uniforms.c
OBJ=$(SRC:.c=.o)
LIBS=MLX42/libmlx42.a -lglfw -L "/Users/$$USER/.brew/opt/glfw/lib/" -framework Cocoa -framework OpenGL -framework IOKit

all: $(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(NAME): $(OBJ)
	ar -crs $(NAME) $^

bonus: all
	ar -crs $(NAME) $^

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

compile: $(OBJ) main.o
	make -C MLX42
	$(CC) $(CFLAGS) $^ $(LIBS)

test: compile
	./a.out

tclean: clean
	rm -f main.o

tfclean: fclean
	rm -f a.out

.PHONY:
	all bonus clean fclean re compile test tclean tfclean