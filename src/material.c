/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:43:42 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/24 11:13:56 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material.h"

/*
 * scatter function for a lambertian material
 */
bool lambertian_scatter(void* self, const t_ray *r_in, const t_hit_record *rec, t_color *attenuation, t_ray *scattered) 
{
	(void)r_in;
	t_lambertian *lamb = (t_lambertian *)self;
	t_vec3 scatter_direction = vec3add(rec->normal, random_unit_vector());
    *scattered = ray(rec->p, scatter_direction);
    *attenuation = lamb->albedo;
        return true;
    return true; 
}

// Example of creating a lambertian material
t_lambertian lambertian_material;

// Function to initialize a Lambertian material
void lambertian_init(t_lambertian *lambertian_material, t_color albedo) 
{
    lambertian_material->base.scatter = lambertian_scatter; // Assign the scatter function
    lambertian_material->albedo = albedo; // Set the albedo
}