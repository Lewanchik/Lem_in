NAME = lem-in

CC = gcc

CFLAGS = -Wall -Wextra -Werror

FILES = src/add_link.c src/add_room.c src/additional_functions.c\
src/algorithm.c src/errors.c src/list_functions.c src/main.c src/print_ants.c\
src/read_rooms.c get_next_line.c

OBJ = $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	cd printf && make && make clean
	cd mylib/libft && make && make clean
	gcc -o $(NAME) $(CFLAGS) $(OBJ) printf/libftprintf.a mylib/libft/libft.a

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

