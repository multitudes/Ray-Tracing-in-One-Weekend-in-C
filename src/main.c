
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
	init_vec3(color, 0, 0, 0);
}



int main(int argc, char **argv)
{
	t_params params;
	(void)argc;
	(void)argv;

    printf("hello world!");
	
	// for the book course we create a ppm image
	create_ppm_image("test.ppm", WIDTH, HEIGHT);

	params.aspect_ratio = 16 / 9;
	
	// viewport
	int image_width = 400;
	int image_height = (int)(image_width / params.aspect_ratio);
	image_height = (image_height < 1) ? 1 : image_height;
	double viewport_height = 2.0;
	double viewport_width = viewport_height * ((double)image_width/image_height);
	double focal_length = 1.0;
	t_vec3 camera_center;
	init_vec3(&camera_center, 0, 0, 0);


    // Calculate the vectors across the horizontal and down the vertical viewport edges.
	t_vec3 viewport_u;
	init_vec3(&viewport_u, viewport_width, 0, 0);
	t_vec3 viewport_v;
	init_vec3(&viewport_v, 0, -viewport_height, 0); 

	t_vec3 pixel_delta_u;
	vec3multscalar(&pixel_delta_u, &viewport_u, 1.0 / (image_width));
	t_vec3 pixel_delta_v;
	vec3multscalar(&pixel_delta_v, &viewport_v, 1.0 / (image_height));

	// location of the upper left corner of the viewport
	t_vec3 viewport_upper_left;
	t_vec3 viewport_half_up_left;
	init_vec3(&viewport_half_up_left, -viewport_width / 2, -viewport_height / 2, -focal_length );
	vec3substr(&viewport_upper_left, &camera_center , &viewport_half_up_left);
	t_vec3 pixel00_loc;
	t_vec3 pixel_delta;
	vec3add(&pixel_delta, &pixel_delta_u, &pixel_delta_v);
	vec3negate(&pixel_delta, &pixel_delta);
	vec3divide(&pixel_delta, &pixel_delta, 2);
	vec3add(&pixel00_loc, &viewport_upper_left, &pixel_delta);


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
