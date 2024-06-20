

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

- Calculate the ray from the “eye” through the pixel,
- Determine which objects the ray intersects, and
- Compute a color for the closest intersection point.

## aspect ratio
A 16∶9 aspect ratio means that the ratio of image width to image height is 16∶9.  
For a practical example, an image 800 pixels wide by 400 pixels high has a 2∶1 aspect ratio. 

## the output image
The book writes the image to a file in the PPM format. The PPM format is a text-based format that starts with a header that describes the image size and color depth. The header is followed by the pixel data, which is written as a series of RGB triplets. 
ex:
```
P3
800 450
255
220 234 255
220 234 255

```
In the above example P3 is just a magic number and has no connection with the display color depth. The next line is the image size, 800 pixels wide by 450 pixels high. The last line is the color depth, 8 bits in this case but can be seen as the is the maximum value for each color. Everything after that is the image data: RGB triplets.  
https://en.wikipedia.org/wiki/Netpbm 


## The Viewport
The viewport is a virtual rectangle in the 3D world that contains the grid of image pixel locations. If pixels are spaced the same distance horizontally as they are vertically, the viewport that bounds them will have the same aspect ratio as the rendered image. The distance between two adjacent pixels is called the pixel spacing, and square pixels is the standard. 
We'll initially set the distance between the viewport and the camera center point to be one unit. This distance is often referred to as the focal length.  
While our 3D space has the conventions above, this conflicts with our image coordinates, where we want to have the zeroth pixel in the top-left and work our way down to the last pixel at the bottom right. This means that our image coordinate Y-axis is inverted: Y increases going down the image. 
 We'll also have the y-axis go up, the x-axis to the right, and the negative z-axis pointing in the viewing direction. (This is commonly referred to as right-handed coordinates.)

## Ray-Sphere Intersection

The equation for a sphere of radius r that is centered at the origin is an important mathematical equation: 

$$
x^2 + y^2 + z^2 = r^2
$$

If a given point (x,y,z) is inside the sphere, then $x^2 + y^2 + z^2 < r^2$ , and if a given point (x,y,z) is outside the sphere, then $x^2 + y^2 + z^2 > r^2$.

If we want to allow the sphere center to be at an arbitrary point (Cx,Cy,Cz) in 3D, then the equation becomes:  
$$
(Cx−x)^2 + (Cy−y)^2 + (Cz−z)^2 = r^2
$$

This formula looks very similar to the definition of a dot product of a vector from point P = (x,y,z) to a center C = (Cx,Cy,Cz) which is (C-P).

The dot product of this vector with itself is:  

$$
(C−P)⋅(C−P)=(Cx−x)^2+(Cy−y)^2+(Cz−z)^2 = r ^ 2
$$ 

We can read this as “any point P that satisfies this equation is on the sphere”.  

Remember that on our ray P is a function of t, so we can substitute P = Q + td into the equation and solve for t. (Q is the origin of the ray, and d is the direction of the ray.)

The only unknown is t, and we have a $t^2$, which means that this equation is quadratic. 
You can solve for a quadratic equation $ax^2+bx+c=0$ by using the quadratic formula:

$$
x = \frac{-b \pm \sqrt{b^2 - 4ac}}{2a}
$$

So solving for t in the ray-sphere intersection equation gives us these values for a, b, and c:
$$
a=d⋅d
b=−2d⋅(C−Q)
c=(C−Q)⋅(C−Q)−r2
$$

where Q is the origin of the ray, d is the direction of the ray, C is the center of the sphere, and r is the radius of the sphere.

Really we just need to know if the square root also called the discriminant is real and positive. If it is, then the ray intersects the sphere at two points. If it is zero, then the ray is tangent to the sphere. If it is negative, then the ray misses the sphere entirely.

$$
\sqrt{b^2 - 4ac}
$$

In code:
```c
bool hit_sphere(const t_sphere *s, const t_ray *r) 
{
    t_vec3 cq = vec3substr(&(s->center), &(r->orig));
    double a = dot(&(r->dir), &(r->dir));
    double b = -2.0 * dot(&(r->dir), &cq);
    double c = dot(&cq, &cq) - s->radius * s->radius;
    double discriminant = b*b - 4*a*c;
    return (discriminant >= 0);
}
```


## Extras - the compile_commands.json file
If using nvim the LSP will ask for a compile_commands.json file. This file is can be generated by the compiledb tool. 
```
make clean && make > build.log
compiledb -n < build.log      
```

## links
- [Raytracing in one weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)  
- [Raytracing the next week](https://raytracing.github.io/books/RayTracingTheNextWeek.html)  
- [Raytracing the rest of your life](https://raytracing.github.io/books/RayTracingTheRestOfYourLife.html)  

- [MLX42](https://github.com/codam-coding-college/MLX42)  
- stb_image.h, a header-only image library available on GitHub at https://github.com/nothings/stb.  