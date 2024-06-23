/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 16:37:25 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/23 15:47:58 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

#include "hittable.h"
#include "ray.h"
#include "color.h"

//forward declaration
typedef struct s_hit_record t_hit_record;

typedef struct s_material
{
	bool (*scatter)(const void *self, const t_ray *r_in, const t_hit_record *rec, t_color *attenuation, t_ray *scattered);
}				t_material;



#endif