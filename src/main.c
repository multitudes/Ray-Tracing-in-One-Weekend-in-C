/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:45:44 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/23 10:52:12 by lbrusa           ###   ########.fr       */
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

	t_camera c = camera();

	// world
	t_hittable *list[2];
	t_sphere s1 = sphere(vec3(0, 0, -1), 0.5);
	t_sphere s2 = sphere(vec3(0, -100.5, -1), 100);
	list[0] = (t_hittable*)(&s1);
	list[1] = (t_hittable*)(&s2);
	const t_hittablelist world = hittablelist(list, 2);
	
	// render
	render(c, world);
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
