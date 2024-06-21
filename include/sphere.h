/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:52:56 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/21 09:19:15 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "ray.h"
#include <stdbool.h>
#include "hittable.h"

typedef struct	s_sphere
{
	t_hittable  base;
	t_point3	center;
	double		radius;
}				t_sphere;

/*
 * a sort of initializer for a sphere
 */
t_sphere	sphere(t_point3 center, double radius);

/* if the ray hits the sphere, return the t value */
bool		hit_sphere(const void* self, const t_ray *r, double ray_tmin, double ray_tmax, t_hit_record *rec);
void 		set_face_normal(t_hit_record *rec, const t_ray *r, const t_vec3 *outward_normal);
