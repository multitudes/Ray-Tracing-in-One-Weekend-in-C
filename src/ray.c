/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:46:44 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/18 15:58:25 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

void			init_ray(t_ray *ray, t_point3 *origin, t_vec3 *direction)
{
	ray->orig = *origin;
	ray->dir = *direction;
}

const t_point3	*ray_origin(const t_ray *ray)
{
	return (&ray->orig);
}

const t_vec3	*ray_direction(const t_ray *ray)
{
	return (&ray->dir);
}

t_point3		point_at(const t_ray *ray, double t)
{
	t_point3 *result;
	t_vec3 scaled_dir;

	scaled_dir = vec3multscalar(&ray->dir, t)
	return (vec3add(&ray->orig, scaled_dir));
}