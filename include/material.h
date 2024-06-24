/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 16:37:25 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/24 11:08:30 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

#include "hittable.h"
#include "ray.h"
#include "color.h"
#include <stdbool.h>

//forward declaration
typedef struct s_hit_record t_hit_record;

typedef struct s_material
{
	bool (*scatter)(void *self, const t_ray *r_in, const t_hit_record *rec, t_color *attenuation, t_ray *scattered);
}				t_material;

// Define a structure for Lambertian material
typedef struct s_lambertian
{
    t_material base; // Base material structure
    t_color albedo;  // Albedo specific to Lambertian material
}               t_lambertian;



#endif