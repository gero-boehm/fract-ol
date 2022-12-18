/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:05:54 by gbohm             #+#    #+#             */
/*   Updated: 2022/12/18 16:09:37 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

static t_vec2	fractal(t_scene *scene, t_vec2 z, t_vec2 c)
{
	z = apply_op_vec2(z, scene->fractal);
	z = complex_add(complex_mult(z, z), c);
	return (z);
}

static int	iterate(t_scene *scene, t_vec2 z, t_vec2 c)
{
	int	i;

	i = 0;
	while (i < scene->iterations)
	{
		z = fractal(scene, z, c);
		if (complex_modulus_squared(z) > 4)
			return (i);
		i++;
	}
	return (0);
}

static t_vec2	get_position(t_scene *scene, double x, double y)
{
	double	px;
	double	py;

	px = x / (double) scene->width - scene->offset.x;
	py = y / (double) scene->height - scene->offset.y;
	px *= scene->aspect * scene->zoom;
	py *= scene->zoom;
	return (vec2(px, py));
}

static void	set_complex_vars(t_scene *scene, t_vec2 pos, t_vec2 *z, t_vec2 *c)
{
	if (scene->type == TYPE_MANDELBROT)
	{
		*z = vec2(0, 0);
		*c = get_position(scene, pos.x, pos.y);
	}
	else
	{
		*z = get_position(scene, pos.x, pos.y);
		*c = apply_op_double(scene->time / 10., scene->julia);
	}
}

void	calculate(t_scene *scene)
{
	uint32_t	x;
	uint32_t	y;
	t_vec2		z;
	t_vec2		c;
	int			result;

	x = 0;
	while (x < scene->width)
	{
		y = 0;
		while (y < scene->height)
		{
			set_complex_vars(scene, vec2(x, y), &z, &c);
			result = iterate(scene, z, c);
			color_pixel(scene, x, y, result);
			y++;
		}
		x++;
	}
}
