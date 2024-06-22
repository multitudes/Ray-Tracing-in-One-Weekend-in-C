/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:45:44 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/22 15:24:16 by lbrusa           ###   ########.fr       */
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

t_color	ray_color(t_ray *r)
{
	t_vec3		dir;
	t_color		raycolor;
	t_sphere	s;
	double		t;	

	t = 0;
	dir = r->dir;
	unit_vector(&dir);
	s = sphere(point3(0, 0, -1), 0.5);
	t_hit_record rec;
	if (hit_sphere(&s, r, 0.1, 5.0, &rec))
	{
		const t_vec3 p_intersection = point_at(r, rec.t);
		const t_vec3 inters_minus_center = vec3substr(&p_intersection, &s.center);
		t_vec3 n = vec3divscalar(&inters_minus_center, s.radius);
		raycolor = color((n.p[0] + 1) / 2, (n.p[1] + 1) / 2, (n.p[2] + 1) / 2);
		return raycolor;
	}
	if (t > 0.0)
	{
		const t_vec3 p_intersection = point_at(r, t);
		const t_vec3 center = vec3(0, 0, -1);
		t_vec3 n = vec3substr(&p_intersection, &center);
		unit_vector(&n);

		raycolor = color((n.p[0] + 1) / 2, (n.p[1] + 1) / 2, (n.p[2] + 1) / 2);
        return raycolor;
	}
	raycolor = backgroundcolor(&dir);
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
			// print_vec3(&pixel_color);
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
