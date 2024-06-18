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
At its core, a ray tracer sends rays through pixels and computes the color seen in the direction of those rays. The involved steps are

    Calculate the ray from the “eye” through the pixel,
    Determine which objects the ray intersects, and
    Compute a color for the closest intersection point.

## aspect ratio
A 16∶9 aspect ratio means that the ratio of image width to image height is 16∶9.  
For a practical example, an image 800 pixels wide by 400 pixels high has a 2∶1 aspect ratio. 

## The Viewport
The viewport is a virtual rectangle in the 3D world that contains the grid of image pixel locations. If pixels are spaced the same distance horizontally as they are vertically, the viewport that bounds them will have the same aspect ratio as the rendered image. The distance between two adjacent pixels is called the pixel spacing, and square pixels is the standard. 
We'll initially set the distance between the viewport and the camera center point to be one unit. This distance is often referred to as the focal length.  
While our 3D space has the conventions above, this conflicts with our image coordinates, where we want to have the zeroth pixel in the top-left and work our way down to the last pixel at the bottom right. This means that our image coordinate Y-axis is inverted: Y increases going down the image. 
 We'll also have the y-axis go up, the x-axis to the right, and the negative z-axis pointing in the viewing direction. (This is commonly referred to as right-handed coordinates.)



## links
- [Raytracing in one weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)  
- [Raytracing the next week](https://raytracing.github.io/books/RayTracingTheNextWeek.html)  
- [Raytracing the rest of your life](https://raytracing.github.io/books/RayTracingTheRestOfYourLife.html)  

- [MLX42](https://github.com/codam-coding-college/MLX42)  