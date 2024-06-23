/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtweekend.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 16:34:23 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/23 14:16:26 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTWEEKEND_H
# define RTWEEKEND_H

#include <math.h>
#include <limits.h>
#include <stdlib.h>


#define PI 3.1415926535897932385

inline double degrees_to_radians(double degrees) {
    return degrees * PI / 180.0;
}

/*
 * Returns a random real in [0,1).
 */
inline double random_d() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

/*
 * Returns a random real in [min,max).
 */
inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_d();
}

#endif