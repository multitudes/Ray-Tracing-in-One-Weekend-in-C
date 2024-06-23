/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:45:44 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/23 14:51:29 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtweekend.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include "utils.h"

#include "sphere.h"
#include "hittable.h"
#include "hittable_list.h"
#include "interval.h"
#include <float.h>
#include <camera.h>

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	// world
	t_hittable *list[2];
	t_sphere s1 = sphere(vec3(0, 0, -1), 0.5);
	t_sphere s2 = sphere(vec3(0, -100.5, -1), 100);
	list[0] = (t_hittable*)(&s1);
	list[1] = (t_hittable*)(&s2);
	const t_hittablelist world = hittablelist(list, 2);
	
	// init camera

    t_camera cam = camera();

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 100;
	cam.pixel_samples_scale = 1.0 / cam.samples_per_pixel;
	cam.max_depth         = 50;

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
