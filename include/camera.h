/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 16:37:03 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/23 10:56:58 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

#include "vec3.h"
#include "ray.h"
#include "hittable_list.h"
#include "color.h"


typedef struct	t_camera 
{
	double 		aspect_ratio;
	int 		image_width;
	int    		image_height;   // Rendered image height
    t_point3 	center;         // Camera center
    t_point3	pixel00_loc;    // Location of pixel 0, 0
    t_vec3		pixel_delta_u;  // Offset to pixel to the right
    t_vec3		pixel_delta_v;  // Offset to pixel below
} 				t_camera;

t_camera	camera();
void		render(t_camera c, const t_hittablelist world);
t_color		ray_color(t_ray *r, const t_hittablelist *world);

#endif