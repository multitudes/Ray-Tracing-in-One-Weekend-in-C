
#include <stdio.h>
#include <stdbool.h>
#include <MLX42/MLX42.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

#include "utils.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"

#define WIDTH 800
#define HEIGHT 600

typedef struct s_params
{
	void *mlx;
	mlx_image_t *img;
	double aspect_ratio;
} t_params;

/*
to be passed to mlx_loop_hook to update the image
*/
void draw(void *param)
{
	t_params *params = (t_params *)param;
	(void)params;
}

t_color ray_color(t_ray *r)
{
	t_vec3 dir = r->dir;
	unit_vector(&dir);
	double a = 0.5 * (dir.p[1] + 1.0);
	t_color white = vec3(1.0, 1.0, 1.0);
	t_color blue = vec3(0.5, 0.7, 1.0);
	t_color white_scaled = vec3multscalar(&white, 1.0 - a);
	t_color blue_scaled = vec3multscalar(&blue, a);
	t_color color = vec3add(&white_scaled, &blue_scaled);
	print_vec3(&color);
	return color;
}

int main(int argc, char **argv)
{
	t_params params;
	(void)argc;
	(void)argv;



 	// aspect_ratio is an ideal ratio
	params.aspect_ratio = (double)16 / 9;
	printf("aspect_ratio: %f\n", params.aspect_ratio);
	int image_width = 800;
	// calculate image height and ansure that it is at least 1
	int image_height = image_width / params.aspect_ratio;
	printf("image_height: %d\n", image_height);
	image_height = (image_height < 1) ? 1 : image_height;
	
	// viewport
	double viewport_height = 2.0;
	// image is truncated... not rounded up therefore I recalculate the viewport width here
	double viewport_width = viewport_height * ((double)image_width/image_height);
	printf("viewport_width: %f\n", viewport_width);
	// camera
	// camera center. a point in 3D space from which all scene rays will originate
	const t_vec3 camera_center = vec3(0, 0, 0);
	// focal length. distance from the camera to the viewport
	double focal_length = 1.0;

	// 3d space conflicts with 2d image coordinates which start at the top left corner
	// Calculate the vectors across the horizontal and down the vertical viewport edges.
    t_vec3 viewport_u = vec3(viewport_width, 0.0, 0.0);
    t_vec3 viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    t_vec3 pixel_delta_u = vec3divide(&viewport_u, image_width);
	t_vec3 pixel_delta_v = vec3divide(&viewport_v, image_height);

    // Calculate the location of the upper left pixel.
	t_vec3 translation = vec3(-viewport_width / 2, -viewport_height / 2, -focal_length);
    t_point3 viewport_upper_left = vec3add(&camera_center, &translation);
	t_vec3 small_translation = vec3(0.5 * viewport_width / image_width, \
									0.5 * viewport_height / image_height, \
									0.0);
    t_point3 pixel00_loc = vec3add(&viewport_upper_left, &small_translation);


    printf("hello world!\n");
	
	// for the book course we create a ppm image
	// create_ppm_image("test.ppm", WIDTH, HEIGHT);

	FILE *file;
	char filepath[PATH_MAX];

	// render
	sprintf(filepath, "assets/%s", "test2.ppm");

	file = fopen(filepath, "w");
	fprintf(file, "P3\n%d %d\n255\n", image_width, image_height);

	for (int j = 0; j < image_height; j++) 
	{
		// write to std err
		// fprintf(stderr, "\rScanlines remaining: %d\n", image_height - j);
		for (int i = 0; i < image_width; i++)
		{	
			t_point3 i_multiply = vec3multscalar(&pixel_delta_u, (double)i);
			t_point3 j_multiply = vec3multscalar(&pixel_delta_v, (double)j);
			t_point3 deltas = vec3add(&i_multiply, &j_multiply);
			const t_point3 pixel_center = vec3add(&pixel00_loc, &deltas);
			t_ray r = ray(&camera_center, &pixel_center);
			t_color pixel_color = ray_color(&r);

			// t_color pixel_color = vec3((float)i / (image_width - 1), (float)j / (image_height - 1), 0.0);
			write_color(file, &pixel_color);
		}
	}

	// params.mlx = mlx_init(WIDTH, HEIGHT, "in a weekend!", true);
	// params.img = mlx_new_image(params.mlx, WIDTH, HEIGHT);

	// if (mlx_image_to_window(params.mlx, params.img, 30, 30) == -1)
	// {
	// 	write(2, "mlx_image_to_window failed\n", 27);
	// 	return (1);
	// }

	// mlx_loop_hook(params.mlx, draw, &params);

	// mlx_loop(params.mlx);



}


/*
just a check. I was not sure if it is a good idea to create a struct in a func
and return it by value. like an int or a double. But it seems to work. funny
being useed to strings in C where it is not possible. so as long as I dont pass the pointer 
but the whole thing it is going to work. it is passed by value.
*/
// typedef struct {
//     double x;
//     double y;
// } Vec2;

// Vec2 vec2_add(Vec2 a, Vec2 b) {
//     Vec2 result;
//     result.x = a.x + b.x;
//     result.y = a.y + b.y;
//     return result;
// }