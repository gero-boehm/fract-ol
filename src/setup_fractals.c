/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_fractals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 08:59:14 by gbohm             #+#    #+#             */
/*   Updated: 2023/01/12 08:59:41 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

int	setup_tricorn(t_scene *scene)
{
	scene->fractal.im = OP_NEG;
	return (0);
}

int	setup_burning_ship(t_scene *scene)
{
	scene->fractal.re = OP_ABS;
	scene->fractal.im = OP_ABS;
	return (0);
}

int	setup_julia(t_scene *scene)
{
	scene->type = TYPE_JULIA;
	scene->julia.im = OP_ZERO;
	scene->time = -6.5;
	return (0);
}
