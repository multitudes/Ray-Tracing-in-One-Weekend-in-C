# The @ symbol at the beginning of the line suppresses the echoing of the command to the terminal when it is executed. 
# Without it, the command and its output would be printed to the terminal, which can make the output cleaner.
# -o $@:
# This specifies the output file to be produced. $@ is a special variable in Makefiles, representing 
# the target of the rule. In this context, it specifies the output file name.
# -c $<:
# The -c flag indicates that the compiler should only produce an object file without linking. 
# $< is another special variable, representing the first prerequisite (dependency) of the rule. It is the source file.

NAME = inaweekend

CC = cc

CFLAGS 			= -Wextra -Wall -Werror
CFLAGS 			+= -Iinclude -Isrc -O3 -Wunreachable-code -Ofast
# CFLAGS 			+= -DDEBUG=1

# define the path to my libft 
LIBFTDIR 		= ./lib/libft

LIBS			= -ldl -lglfw -pthread -lm
LIBS 			+= $(LIBFTDIR)/libft.a

OBJ_DIR			= obj/
SRC_DIR			= src/

INCLUDE			+= -I ./include -I $(LIBFTDIR)

SRCS 			= $(addprefix $(SRC_DIR), main.c utils.c vec3.c color.c ray.c sphere.c) 
OBJS 			= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
HDRS 			= $(addprefix include/, utils.h vec3.h color.h sphere.h ray.h)


libft = $(LIBFTDIR)/libft.a


all: libmlx libft $(NAME)

# Static pattern rule for compilation - adding the .o files in the obj folder 
# with includes for the libft that will allow the <libft.h> notation 
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE)  -c $< -o $@


build:
	@mkdir -p build


libft:
	$(MAKE) -C $(LIBFTDIR) all

$(NAME): $(OBJS) $(HDRS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(INCLUDE) -o $(NAME)

# %.o: %.c
# 	@$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE) && printf "Compiling: $(notdir $<)"

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


