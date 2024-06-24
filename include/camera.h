/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 16:37:03 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/24 15:49:46 by lbrusa           ###   ########.fr       */
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
	int 		samples_per_pixel;
	double		pixel_samples_scale;
	int			max_depth;		   // Maximum number of ray bounces into scene
	double		vfov;			   // Field of view
} 				t_camera;

t_camera	camera();
void		render(t_camera cam, const t_hittablelist world);
t_color		ray_color(t_ray *r, int max_deph, const t_hittablelist *world);
t_ray		get_ray(t_camera *c, int u, int v);
t_vec3		sample_square();

#endif