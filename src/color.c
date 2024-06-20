/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:49:03 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/20 10:25:35 by lbrusa           ###   ########.fr       */
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
