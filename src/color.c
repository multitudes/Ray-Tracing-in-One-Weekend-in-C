/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:49:03 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/18 15:24:00 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include <stdio.h>
#include <limits.h>

/*
write a pixel to a file
the format is PPM and this function is called from create_ppm_image
*/
void write_color(FILE *file, t_color *pixel_color)
{
	fprintf(file, "%d %d %d\n", (int)(255.999 * pixel_color->p[0]), (int)(255.999 * pixel_color->p[1]), (int)(255.999 * pixel_color->p[2]));
}