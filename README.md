I am following the tutorials in [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html) but writing the code in C for good practice.  

These are my notes from the book and what I learned in the process.

## Raytracing
At its core, a ray tracer sends rays through pixels and computes the color seen in the direction of those rays. The involved steps are

- Calculate the ray from the “eye” through the pixel,
- Determine which objects the ray intersects, and
- Compute a color for the closest intersection point.

## The aspect ratio
A 16∶9 aspect ratio means that the ratio of image width to image height is 16∶9.  
For a practical example, an image 800 pixels wide by 400 pixels high has a 2∶1 aspect ratio. 

## The output image
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
(unfortunately Jekill doesnt render the math equations so will have to write them out later)
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

## The Normal Vector
This is a vector that is perpendicular to the surface at the point of intersection. 

Ex For a sphere, the outward normal is in the direction of the hit point minus the center: 

## Which side of the sphere are we on?
We need to choose to determine the side of the surface at the time of geometry intersection or at the time of coloring.
This is a boolean determined with the dot product
```
bool front_face;
if (dot(ray_direction, outward_normal) > 0.0) {
    // ray is inside the sphere
    normal = -outward_normal;
    front_face = false;
} else {
    // ray is outside the sphere
    normal = outward_normal;
    front_face = true;
}
```

## An array of shapes in C? How!?
Thanks to this course I discovered that you can have polymorphic behavior in C. 
It is a bit weird at first but totally doable.  

I have a struct, `t_hittable` that has a function pointer to a hit function.  

To create an array of different shapes (like spheres and cubes) that all implement the [`hittable`]interface or behaviour, I define a struct `t_hittable` that contains a function pointer for the `hit` function:

```c
typedef struct s_hittable {
    bool (*hit)(const void* self, const t_ray* r, double t_min, double t_max, t_hit_record* rec);
} t_hittable;
```

Then, for each shape (like a sphere or a cube), you create a struct that includes the `t_hittable` struct as its first member:

```c
typedef struct {
    t_hittable base;
    t_point3 center;
    double radius;
} sphere;

typedef struct {
    t_hittable base;
    t_point3 min;
    t_point3 max;
} cube;
```
**This is very important: the `hittable` struct must be the first member of the shape structs.**  
This is because the C standard guarantees that the address of the first member of a struct is the same as the address of the struct itself. This allows you to cast a pointer to a `sphere` or `cube` to a `hittable` pointer and back without any issues.

You can then define the `hit` functions for each shape:

```c
bool hit_sphere(const void* self, const t_ray* r, double t_min, double t_max, t_hit_record* rec) {
    // implementation...
}

bool hit_cube(const void* self, const t_ray* r, double t_min, double t_max, t_hit_record* rec) {
    // implementation...
}
```

The functions all take a `const void* self` parameter, which is a pointer to the shape struct. This allows you to cast the pointer to the appropriate shape struct inside the function.

When you create a new shape, you set the `hit` function pointer in the `hittable` struct to the appropriate function:

```c
t_sphere* new_sphere(t_point3 center, double radius) {
    sphere* s = malloc(sizeof(sphere));
    s->base.hit = hit_sphere;
    s->center = center;
    s->radius = radius;
    return s;
}
```
Or actually without malloc is also possible since I have small structs I can return them by value.  
I did not do the necessary tests but I imagine Using malloc to allocate memory would take use some 
extra time. Stack is faster than heap, but then I copy the struct when returning it. I do not yet know which is faster.  

```c
t_sphere new_sphere(t_point3 center, double radius) {
	sphere s;
	s.base.hit = hit_sphere;
	s.center = center;
	s.radius = radius;
	return s;
}
```
Then in the main function, you can create a list of `t_hittable` pointers and add your shapes to it:

```c
t_hittable *list[2];
t_sphere s1 = sphere(vec3(0, 0, -1), 0.5);
t_sphere s2 = sphere(vec3(0, -100.5, -1), 100);
list[0] = (t_hittable*)(&s1);
list[1] = (t_hittable*)(&s2);
const t_hittablelist world = hittablelist(list, 2);

```

This already works and I get the second sphere creating a nice background.
![sphere](assets/test2.ppm)

To check if a ray hits any of the shapes, you can loop over the array and call the `hit` function through the function pointer:

```c
for (int i = 0; i < 10; i++) {
    if (shapes[i]->hit(shapes[i], r, t_min, t_max, &rec)) {
        // hit
    }
}
```
This would be quite cool but turns out that we will use an extra struct to keep track of the world. Since c++ has vectors which are a kind of dynamic array in C, I created a t_hittablelist struct that contains an array of hittable pointers and a size. Knowing the size is important. For now that's it, later I will add some more functions to add elements etc.

```c

typedef struct 	s_hittablelist {
	t_hittable 	**list;
	int 		size;
	bool 		(*hit)(const void* self, const t_ray* r, double ray_tmin, double ray_tmax, t_hit_record* rec);
} 				t_hittablelist;
```

And so we have a hit function on world that will loop through the list of hittables and call their hit functions.

```
bool hit(const void *self, const t_ray* r, double ray_tmin, double ray_tmax, t_hit_record* rec)
{
	 	t_hittablelist *hittablelist = (t_hittablelist *)self;
		t_hit_record temp_rec;
		bool hit_anything = false;
		double closest_so_far = ray_tmax;
		int i = 0;

		while (i < hittablelist->size)
		{
			if (hittablelist->list[i]->hit(hittablelist->list[i], r, ray_tmin, closest_so_far, &temp_rec))
			{
				hit_anything = true;
				closest_so_far = temp_rec.t;
				*rec = temp_rec;
			}
			i++;
		} 
	return (hit_anything);
}

t_hittablelist hittablelist(t_hittable **list, int size)
{
	t_hittablelist hittablelist;

	hittablelist.list = list;
	hittablelist.size = size;
	hittablelist.hit = hit;
	return (hittablelist);
}
```

## Useful to have - An Interval type

In C++ it is a class, in C it will be a struct. The interval type is useful to keep track of the t_min and t_max values. 
```c
typedef struct {
	double t_min;
	double t_max;
} t_interval;
```


## The Camera
In C we do not have classes of course but we will still refactor the code in its own file with its struct and functions.
The camera is responsible for two important jobs:

    - Construct and dispatch rays into the world.
    - Use the results of these rays to construct the rendered image.

After main creates a camera and sets default values, it will call the render() method.  
The render() method will prepare the camera for rendering and then execute the render loop.

## Passing by value or by reference?
In C++ we have references which are variables that can be passed around without copying. In C we have pointers. But pointers bring a problem. 
If I declare the sum like
```
t_vec3 add(t_vec3 *a, t_vec3 *b)
{
	t_vec3 sum;
	sum.x = a->x + b->x;
	sum.y = a->y + b->y;
	sum.z = a->z + b->z;
	return (sum);
}
```
Then if using the add functions for two vectors I have to pass pointers then I cannot use the add function with the result of another add function. Like this is working but I have to create a temp extra var c:
```
t_vec3 a = vec3(1, 2, 3);
t_vec3 b = vec3(4, 5, 6);
t_vec3 c = add(&a, &b);
t_vec3 d = add(&c, &c);
```
This will not work because the add function expects pointers and I cannot in C take the pointer of a rvalue return value . So I will have to use the add function like this:
```	
t_vec3 a = vec3(1, 2, 3);
t_vec3 b = vec3(4, 5, 6);
t_vec3 c = vec3(&add(&a, &b), &add(&a, &b));
```

With small structs there is a very small performance hit when passing by value. So I will pass by value and this allows to chain functions and have better readable code.
```
t_vec3 add(t_vec3 a, t_vec3 b)
{
	t_vec3 sum;
	sum.x = a.x + b.x;
	sum.y = a.y + b.y;
	sum.z = a.z + b.z;
	return (sum);
}
```
now:
```
t_vec3 a = vec3(1, 2, 3);	
t_vec3 b = vec3(4, 5, 6);
t_vec3 d = add(add(a, b), add(a, b));
```
It is much nicer.

## Using unions in C
A union is a special data type available in C that allows to store different data types in the same memory location. You can define a union with many members, but only one member can contain a value at any given time. Unions provide an efficient way of using the same memory location for multiple-purpose.
In my case I have a vector in 3d with x y and z components. Also I have a color type with 3 components too. I can use alias to use the same struct for both. Also I discovered that I can use a union to have access to rgb and xyz at the same time.  In C++ I would use encapsulation and private/public members with getters and setters but in C I dont have this level of abstraction.
```c
typedef struct s_vec3 {
    union {
        struct {
            double x, y, z;
        };
        struct {
            double r, g, b;
        };
    };
} t_vec3, t_color, t_point3;
```

## Antialiasing
If we look at our zoomed image created until now we see that the edges are jagged like pixels on a staircase. To fix this we will take multiple samples per pixel and average the color. This is called antialiasing. In the book also there is an interesting note about the human eye and how it perceives color.
> With a single ray through the center of each pixel, we are performing what is commonly called point sampling. The problem with point sampling can be illustrated by rendering a small checkerboard far away. If this checkerboard consists of an 8×8 grid of black and white tiles, but only four rays hit it, then all four rays might intersect only white tiles, or only black, or some odd combination. In the real world, when we perceive a checkerboard far away with our eyes, we perceive it as a gray color, instead of sharp points of black and white.

We need to sample the light falling around the pixel, and integrate the changes.

To do so we will create a random number generator to sample the colors around the pixel in a random way. 

Here the C random number generator has been apparently superiour to the c++ one for quite some time. Interesting.


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

- stb_image.h, a header-only image library available on GitHub at https://github.com/nothings/stb.
- [https://gabrielgambetta.com/computer-graphics-from-scratch/](https://gabrielgambetta.com/computer-graphics-from-scratch/)  
- A raytracer on the back of a business card. [https://fabiensanglard.net/rayTracing_back_of_business_card/](https://fabiensanglard.net/rayTracing_back_of_business_card/)

here are a few really good resources by [Fabien Sanglard](https://fabiensanglard.net/about/index.html):

scratchapixel.com : Great raytracer lessons written by professionals that have worked on Toy Story, Avatar, Lord of the Rings, Harry Potter, Pirates of the Caribbean and many other movies.
An Introduction to Ray Tracing : An old book but a Classic.
Physically Based Rendering : Heavy on maths but really good and well explained.

- stb_image.h, a header-only image library available on GitHub at https://github.com/nothings/stb.  