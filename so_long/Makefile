NAME    =   a.out
#
# SRCS and OBJS
#
SRCS    =   $(wildcard *.c) \

OBJS = $(SRCS:%.c=%.o)
#
# Compiler and flags
#
CC      =   clang
//CFLAGS    =   -Wall -Werror -Wextra
CLIB    =   -Lmlx -lmlx -framework OpenGL -framework Appkit -Imlx
#
# Rules
#
all	: $(NAME)
%.o	:%.c
	$(CC) $(CFLAGS)  -c $< -o $@
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(CLIB) $(SRCS) -o $(NAME)
	install_name_tool -change libmlx.dylib mlx/libmlx.dylib $(NAME)
clean	:
	rm -rf $(OBJS)
fclean	: clean
	rm -rf  $(NAME)
re	: fclean all