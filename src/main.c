
#include <stdio.h>
#include <stdbool.h>
#include <MLX42/MLX42.h>
#include <unistd.h>

#include "utils.h"
#include "vector.h"
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

void ray_color(t_color *color, t_ray *r)
{
	(void)r;
	(void)color;
	// init_vec3(color, 0, 0, 0);
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

int main(int argc, char **argv)
{
	t_params params;
	(void)argc;
	(void)argv;

    printf("hello world!\n");
	
	// for the book course we create a ppm image
	create_ppm_image("test.ppm", WIDTH, HEIGHT);

	// params.aspect_ratio = 16 / 9;
	
	// // viewport
	// int image_width = 400;
	// int image_height = (int)(image_width / params.aspect_ratio);
	// image_height = (image_height < 1) ? 1 : image_height;
	// double viewport_height = 2.0;
	// double viewport_width = viewport_height * ((double)image_width/image_height);
	// double focal_length = 1.0;
	// t_vec3 camera_center;




	params.mlx = mlx_init(WIDTH, HEIGHT, "in a weekend!", true);
	params.img = mlx_new_image(params.mlx, WIDTH, HEIGHT);

	if (mlx_image_to_window(params.mlx, params.img, 30, 30) == -1)
	{
		write(2, "mlx_image_to_window failed\n", 27);
		return (1);
	}

	mlx_loop_hook(params.mlx, draw, &params);

	mlx_loop(params.mlx);



}
