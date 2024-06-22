/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:47:37 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/20 12:05:25 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "vec3.h"
# include <stdio.h>

t_color		color(double r, double g, double b);
void		write_color(FILE *file, t_color *pixel_color);
t_color 	creategradient(t_vec3 *dir, t_color *white, t_color *blue);
t_color		backgroundcolor(t_vec3 *dir);

#endif