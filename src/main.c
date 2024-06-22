/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:45:44 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/22 14:47:35 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include "utils.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "sphere.h"

bool hit_sphere(const t_sphere *s, const t_ray *r) 
{
    t_vec3 cq = vec3substr(&(s->center), &(r->orig));
    double a = dot(&(r->dir), &(r->dir));
    double b = -2.0 * dot(&(r->dir), &cq);
    double c = dot(&cq, &cq) - s->radius * s->radius;
    double discriminant = b*b - 4*a*c;
    return (discriminant >= 0);
}


t_color	ray_color(t_ray *r)
{
	t_vec3	dir;
	t_color raycolor;
	
	dir = r->dir;
	const t_sphere s = sphere(point3(0, 0, -1), 0.5);
	if (hit_sphere(&s, r))
	{
		raycolor = color(1, 0, 0);
        return raycolor;
	}
	unit_vector(&dir);
	double a = 0.5 * (dir.p[1] + 1.0);
	// printf("a: %f\n", a);
	t_color white = vec3(1.0, 1.0, 1.0);
	t_color blue = vec3(0.5, 0.7, 1.0);
	t_color white_scaled = vec3multscalar(&white, 1.0 - a);
	t_color blue_scaled = vec3multscalar(&blue, a);
	raycolor = vec3add(&white_scaled, &blue_scaled);
	// print_vec3(&color);
	return raycolor;
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;



 	// aspect_ratio is an ideal ratio
	double aspect_ratio = (double)16 / 9;
	printf("aspect_ratio: %f\n", aspect_ratio);
	int image_width = 400;
	// calculate image height and ansure that it is at least 1
	int image_height = (double)image_width / aspect_ratio;
	printf("image_height: %d\n", image_height);
	image_height = (image_height < 1) ? 1 : image_height;
	
	// viewport
	double viewport_height = 2.0;
	// image is truncated... not rounded up therefore I recalculate the viewport width here
	double viewport_width = viewport_height * ((double)image_width/image_height);
	printf("viewport_width: %f and height %f\n", viewport_width, viewport_height);
	// camera
	// camera center. a point in 3D space from which all scene rays will originate
	const t_vec3 camera_center = vec3(0, 0, 0);
	// focal length. distance from the camera to the viewport
	double focal_length = 1.0;

	// 3d space conflicts with 2d image coordinates which start at the top left corner
	// Calculate the vectors across the horizontal and down the vertical viewport edges.
    // t_vec3 viewport_u = vec3(viewport_width, 0.0, 0.0);
    // t_vec3 viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    // t_vec3 pixel_delta_u = vec3divide(&viewport_u, image_width);
	// t_vec3 pixel_delta_v = vec3divide(&viewport_v, image_height);

    // Calculate the location of the upper left pixel. viewport_height needs to be negated again so positive values are up.
	t_vec3 translation = vec3(-viewport_width / 2, viewport_height / 2, -focal_length);
    t_point3 viewport_upper_left = vec3add(&camera_center, &translation);
	printf("viewport_upper_left: ");
	print_vec3(&viewport_upper_left);
	// get the offset to the first pixel center
	t_vec3 small_translation = vec3(0.5 * viewport_width / image_width, \
									- 0.5 * viewport_height / image_height, \
									0.0);
	printf("small_translation: ");
	print_vec3(&small_translation);
    t_point3 pixel00_loc = vec3add(&viewport_upper_left, &small_translation);
	printf("pixel00_loc: ");
	print_vec3(&pixel00_loc);

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
			// t_point3 i_multiply = vec3multscalar(&pixel_delta_u, (double)i);
			// t_point3 j_multiply = vec3multscalar(&pixel_delta_v, (double)j);
			t_point3 deltas = vec3((double)viewport_width / image_width * i, -(double)viewport_height / image_height * j, 0.0);
			
			const t_point3 pixel_center = vec3add(&pixel00_loc, &deltas);

// direction vector from camera to pixel is the pixel location minus the camera center and the camera center is 0,0,0 in this case
// so the direction vector is the pixel center
			t_ray r = ray(&camera_center, &pixel_center);
			t_color pixel_color = ray_color(&r);
			print_vec3(&pixel_color);
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
