# The @ symbol at the beginning of the line suppresses the echoing of the command to the terminal when it is executed. 
# Without it, the command and its output would be printed to the terminal, which can make the output cleaner.
# -o $@:
# This specifies the output file to be produced. $@ is a special variable in Makefiles, representing 
# the target of the rule. In this context, it specifies the output file name.
# -c $<:
# The -c flag indicates that the compiler should only produce an object file without linking. 
# $< is another special variable, representing the first prerequisite (dependency) of the rule. It is the source file.

NAME = miniRT
CC = cc
CCFLAGS = -Wextra -Wall -Werror
CFLAGS += -Iinclude -Isrc -O3 -Wunreachable-code -Ofast
CFLAGS += -DDEBUG=1

LIBMLX	:= ./lib/MLX42
LIBFTDIR = ./lib/libft

LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
LIBS += $(LIBFTDIR)/libft.a

HEADERS	:= -I ./include -I $(LIBMLX)/include
HEADERS	+= -I ./include -I $(LIBFTDIR)

SRCS = $(addprefix src/, main.c)

OBJS = $(SRCS:%.c=%.o)

libft = $(LIBFTDIR)/libft.a

LIBFT_LIB = -Llibft -lft

all: libmlx libft $(NAME)

build:
	@mkdir -p build
	
libmlx:
	@if [ ! -d "lib/MLX42" ]; then \
	git clone https://github.com/codam-coding-college/MLX42.git lib/MLX42; \
	fi
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	@$(MAKE) -C $(LIBFTDIR) all

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

clean:
	rm -f $(OBJECTS) *~
	$(MAKE) -C $(LIBFTDIR) clean
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean
	rm -rf build

re: fclean all

.PHONY: all clean fclean re libmlx


