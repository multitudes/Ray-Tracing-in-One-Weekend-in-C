/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 16:37:25 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/24 11:48:58 by lbrusa           ###   ########.fr       */
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

typedef struct s_metal
{
	t_material base; // Base material structure
	t_color albedo;  // Albedo specific to Metal material
	double fuzz;     // Fuzziness of the metal
}               t_metal;

void lambertian_init(t_lambertian *lambertian_material, t_color albedo);
void metal_init(t_metal *metal, t_color albedo, double fuzz);
bool metal_scatter(void *self, const t_ray* r_in, const t_hit_record *rec, t_color *attenuation, t_ray *scattered);
bool lambertian_scatter(void* self, const t_ray *r_in, const t_hit_record *rec, t_color *attenuation, t_ray *scattered) ;

#endif