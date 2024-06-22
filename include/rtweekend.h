/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtweekend.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 16:34:23 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/22 17:47:48 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTWEEKEND_H
# define RTWEEKEND_H

#include <math.h>
#include <limits.h>

#ifdef __linux__
#define INFINITY DBL_MAX
#endif

#define PI 3.1415926535897932385

inline double degrees_to_radians(double degrees) {
    return degrees * PI / 180.0;
}



#endif