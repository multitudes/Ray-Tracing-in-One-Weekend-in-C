/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 10:28:07 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/23 10:59:19 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "hittable.h"
#include "hittable_list.h"
#include <limits.h>

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
    t_point3 viewport_upper_left = vec3add(&c.center, &translation);
	c.pixel_delta_u = vec3(viewport_width / c.image_width, 0.0, 0.0);
	c.pixel_delta_v = vec3(0.0, -viewport_height / c.image_height, 0.0);
	t_vec3 small_translation = vec3(0.5 * viewport_width / c.image_width, \
									- 0.5 * viewport_height / c.image_height, \
									0.0);
    c.pixel00_loc = vec3add(&viewport_upper_left, &small_translation);
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
			t_point3 deltas = vec3(c.pixel_delta_u.p[0] * i, c.pixel_delta_v.p[1] * j, 0.0);
			
			const t_point3 pixel_center = vec3add(&c.pixel00_loc, &deltas);

			// direction vector from camera to pixel is the pixel location minus the camera center and the camera center is 0,0,0 in this case
			// so the direction vector is the pixel center
			t_ray r = ray(&c.center, &pixel_center);
			t_color pixel_color = ray_color(&r, &world);
			// print_vec3(&pixel_color);
			// t_color pixel_color = vec3((float)i / (image_width - 1), (float)j / (image_height - 1), 0.0);
			write_color(file, &pixel_color);
		}
	}
	fclose(file);
}


t_color	ray_color(t_ray *r, const t_hittablelist *world)
{
	t_color		raycolor;
	
	t_hit_record rec;
	if ((world)->hit(world, r, interval(0, INFINITY), &rec))
	{
		t_color white = color(1.0, 1.0, 1.0);
		t_vec3 target = vec3add(&rec.normal, &white);
		raycolor = vec3multscalar(&target, 0.5);
		return raycolor;
	}
	unit_vector(&(r->dir));
	double a = 0.5 * (r->dir.p[1] + 1.0);
	t_color white = color(1.0, 1.0, 1.0);
	t_color blue = color(0.5, 0.7, 1.0);
	t_color start = vec3multscalar(&white, 1.0 - a);
	t_color end = vec3multscalar(&blue, a);
	raycolor = vec3add(&start, &end);
	return raycolor;
}

