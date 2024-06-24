/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:45:44 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/24 18:54:49 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtweekend.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include "utils.h"
#include "hittable.h"
#include "sphere.h"
#include "camera.h"
#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "material.h"
#include "hittable_list.h"
#include "interval.h"
#include <float.h>
#include <camera.h>

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	// world

	// double R = cos(M_PI / 4);
	
	// t_lambertian lambertian_material_left;
	// t_lambertian lambertian_material_right;

	// lambertian_init(&lambertian_material_left, color(0, 0, 1));
	// lambertian_init(&lambertian_material_right, color(1, 0, 0));

	// t_sphere s1 = sphere(point3(-R, 0, -1), R, (t_material*)&lambertian_material_left);
	// t_sphere s2 = sphere(point3(R, 0, -1), R, (t_material*)&lambertian_material_right);

	// t_hittable *list[2];
	
	// list[0] = (t_hittable*)(&s1);
	// list[1] = (t_hittable*)(&s2);
	// const t_hittablelist world = hittablelist(list, 2);
	

	t_lambertian lambertian_material_ground;
	t_lambertian lambertian_material_center;
	// t_metal metal_material_left;
	t_dielectric dielectric_material_left;
	t_dielectric dielectric_material_bubble;
	t_metal metal_material_right;

   	lambertian_init(&lambertian_material_ground, color(0.8, 0.8, 0.0));
	lambertian_init(&lambertian_material_center, color(0.1, 0.2, 0.5));
    // metal_init(&metal_material_left, color(0.8, 0.8, 0.8), 0.3);
	dielectric_init(&dielectric_material_left, 1.50);
	dielectric_init(&dielectric_material_bubble, 1.00 / 1.50);
	metal_init(&metal_material_right, color(0.8, 0.6, 0.2), 1.0);

	// Assuming t_lambertian and t_metal have a t_material as their first member,
	// you can safely cast their addresses to t_material*.
	t_sphere s1 = sphere(point3(0.0, -100.5, -1.0), 100.0, (t_material*)&lambertian_material_ground);
	t_sphere s2 = sphere(point3(0.0, 0.0, -1.2), 0.5, (t_material*)&lambertian_material_center);
	// t_sphere s3 = sphere(point3(-1.0, 0.0, -1.0), 0.5, (t_material*)&metal_material_left);
	
	t_sphere s3 = sphere(point3(-1.0, 0.0, -1.0), 0.5, (t_material*)&dielectric_material_left);
	t_sphere s4 = sphere(point3(-1.0, 0.0, -1.0), 0.4, (t_material*)&dielectric_material_bubble);
	t_sphere s5 = sphere(point3(1.0, 0.0, -1.0), 0.5, (t_material*)&metal_material_right);


	t_hittable *list[5];

	list[0] = (t_hittable*)(&s1);
	list[1] = (t_hittable*)(&s2);
	list[2] = (t_hittable*)(&s3);
	list[3] = (t_hittable*)(&s4);
	list[4] = (t_hittable*)(&s5);
	const t_hittablelist world = hittablelist(list, 5);
	
	// init camera

    t_camera cam = camera();

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 100;
	cam.pixel_samples_scale = 1.0 / cam.samples_per_pixel;
	cam.max_depth         = 50;
	cam.vfov     = 90;
	cam.lookfrom = point3(-2,2,1);
    cam.lookat   = point3(0,0,-1);
    cam.vup      = vec3(0,1,0);
	
	// render
	render(cam, world);
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
