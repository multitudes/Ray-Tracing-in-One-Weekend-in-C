# miniRT
This project is an introduction to the beautiful world of Raytracing.

## MLX42
This project uses the MLX42 library to create the graphical interface. 
I choose to use this library as it is a maintained and updated version of the minilibx library. 
To link the MLX42 I clone it from the codam-coding-college repository and link it to the project in the Makefile already:
```
# define the path to the mlx library
LIBMLX			:= ./lib/MLX42

# define the path to the mlx library archive - ldl is needed for linux 
# to link to the dynamic linking loader and glfw is needed for the windowing system
LIBS			:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

# define the path to the mlx library headers
INCLUDE			:= -I ./include -I $(LIBMLX)/include

# my makefile rule will call the mlx library rule
all: libmlx

# if needed I can create a dir for the build - this is in the online documentation for the MLX42 library

build:
	@mkdir -p build
	
libmlx:
	@if [ ! -d "lib/MLX42" ]; then \
	git clone https://github.com/codam-coding-college/MLX42.git lib/MLX42; \
	fi
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
```

The above will install the MLX42 library in the lib/MLX42 directory and link it to the project.
when compiling I will need to use the $(INCLUDE) and $(LIBS) flags to include the library and headers.
```
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) $(OBJS) -o $(NAME)
```


## Raytracing

## links
- [Raytracing in one weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)  
- [Raytracing the next week](https://raytracing.github.io/books/RayTracingTheNextWeek.html)  
- [Raytracing the rest of your life](https://raytracing.github.io/books/RayTracingTheRestOfYourLife.html)  

- [MLX42](https://github.com/codam-coding-college/MLX42)  