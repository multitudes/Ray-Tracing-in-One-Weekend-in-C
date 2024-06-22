/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:49:03 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/20 12:04:59 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include <stdio.h>
#include <limits.h>


t_color color(double r, double g, double b)
{
	t_color result;

	result.p[0] = r;
	result.p[1] = g;
	result.p[2] = b;
	return result;
}

/*
write a pixel to a file
the format is PPM and this function is called from create_ppm_image
*/
void write_color(FILE *file, t_color *pixel_color)
{
	fprintf(file, "%d %d %d\n", (int)(255.999 * pixel_color->p[0]), (int)(255.999 * pixel_color->p[1]), (int)(255.999 * pixel_color->p[2]));
}

t_color creategradient(t_vec3 *dir, t_color *white, t_color *blue)
{
	double a = 0.5 * (dir->p[1] + 1.0);
	t_color white_scaled = vec3multscalar(white, 1.0 - a);
	t_color blue_scaled = vec3multscalar(blue, a);
	t_color raycolor = vec3add(&white_scaled, &blue_scaled);
	return raycolor;
}

t_color	backgroundcolor(t_vec3 *dir)
{
	t_color blue;
	t_color white;
	t_color raycolor;
	
	white = vec3(1.0, 1.0, 1.0);
	blue = vec3(0.5, 0.7, 1.0);
	unit_vector(dir);
	raycolor = creategradient(dir, &white, &blue);
	return raycolor;
}