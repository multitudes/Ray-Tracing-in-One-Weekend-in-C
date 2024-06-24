/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 10:28:07 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/24 11:44:50 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "hittable.h"
#include "hittable_list.h"
#include <limits.h>
#include "rtweekend.h"
#include <stdio.h>

/*
 * camera
 * 
 * aspect_ratio: width / height
 * image_width: width of the image in pixels
 * image_height: height of the image in pixels
 * center: the point in 3D space from which all scene rays will originate
 * pixel00_loc: the location of the upper left pixel
 * pixel_delta_u: the offset to the first pixel center
 * pixel_delta_v: the offset to the pixel center
 */
t_camera camera()
{
	t_camera c;
	
	c.max_depth = 10;
	c.samples_per_pixel = 10;
	c.pixel_samples_scale = 1.0 / c.samples_per_pixel;
	c.aspect_ratio = (double)16.0 / 9.0;
	c.image_width = 400;
	c.image_height = (double)c.image_width / c.aspect_ratio;
	c.image_height = (c.image_height < 1) ? 1 : c.image_height;
	c.center = vec3(0, 0, 0);
 	double focal_length = 1.0;
	double viewport_height = 2.0;
	double viewport_width = viewport_height * ((double)c.image_width/c.image_height);
	// printf("viewport_width: %f and height %f\n", viewport_width, viewport_height);
	t_vec3 translation = vec3(-viewport_width / 2, viewport_height / 2, -focal_length);
    t_point3 viewport_upper_left = vec3add(c.center, translation);
	c.pixel_delta_u = vec3(viewport_width / c.image_width, 0.0, 0.0);
	c.pixel_delta_v = vec3(0.0, -viewport_height / c.image_height, 0.0);
	t_vec3 small_translation = vec3(0.5 * viewport_width / c.image_width, \
									- 0.5 * viewport_height / c.image_height, \
									0.0);
    c.pixel00_loc = vec3add(viewport_upper_left, small_translation);
	printf("pixel00_loc: ");
	print_vec3(&c.pixel00_loc);

	return c;


}


void	render(t_camera c, const t_hittablelist world)
{
	// render
	// for the book course we create a ppm image
	// create_ppm_image("test.ppm", WIDTH, HEIGHT);

	FILE *file;
	char filepath[PATH_MAX];

	// render
	sprintf(filepath, "assets/%s", "test2.ppm");
	file = fopen(filepath, "w");
	fprintf(file, "P3\n%d %d\n255\n", c.image_width, c.image_height);

	for (int j = 0; j < c.image_height; j++) 
	{
		// write to std err
		// fprintf(stderr, "\rScanlines remaining: %d\n", image_height - j);
		for (int i = 0; i < c.image_width; i++)
		{	
			t_color pixel_color = color(0,0,0);
            for (int sample = 0; sample < c.samples_per_pixel; sample++) {
                    t_ray r = get_ray(&c, i, j);
					t_color partial = ray_color(&r, c.max_depth, &world);
                    pixel_color = vec3add(pixel_color, partial);
                }
			write_color(file, vec3multscalar(pixel_color, c.pixel_samples_scale));
		}
	}
	fclose(file);
}


t_color	ray_color(t_ray *r, const int depth, const t_hittablelist *world)
{
	t_hit_record rec;
	if (depth <= 0)
        return color(0,0,0);
	if ((world)->hit(world, r, interval(0.001, INFINITY), &rec))
	{
		t_ray scattered;
		t_color attenuation;
		if (rec.mat->scatter(rec.mat, r, &rec, &attenuation, &scattered))
			return vec3mult(attenuation, ray_color(&scattered, depth - 1, world));
		// t_vec3 direction = vec3add(rec.normal, random_unit_vector());
		// t_ray scattered = ray(rec.p, direction);
		// return vec3multscalar(ray_color(&scattered, depth - 1, world), 0.5);
		return color(0,0,0);
	}
	t_vec3 unit_direction = unit_vector(r->dir);
	double a = 0.5 * (unit_direction.y + 1.0);
	t_color start = vec3multscalar(color(1.0, 1.0, 1.0), 1.0 - a);
	t_color end = vec3multscalar(color(0.5, 0.7, 1.0), a);
	return vec3add(start, end);
}

t_ray get_ray(t_camera *c, int i, int j)  
{
	// Construct a camera ray originating from the origin and directed at randomly sampled
	// point around the pixel location i, j.

	t_vec3	offset = sample_square();
	t_vec3	pixel_sample = vec3add(c->pixel00_loc, 
						vec3add(vec3multscalar(c->pixel_delta_u, (i + offset.x)),
								vec3multscalar(c->pixel_delta_v, (j + offset.y))));

	t_vec3 ray_origin = c->center;
	t_vec3 ray_direction = vec3substr(pixel_sample, ray_origin);

	return ray(ray_origin, ray_direction);
}

t_vec3	sample_square()
{
	// Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
	return vec3(random_d() - 0.5, random_d() - 0.5, 0);
}

