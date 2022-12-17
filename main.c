/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:40:30 by gbohm             #+#    #+#             */
/*   Updated: 2022/12/17 17:19:54 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include <math.h>
#include "src/fract_ol.h"

t_vec2	fractal(t_scene *scene, t_vec2 z, t_vec2 c)
{
	z = apply_op_vec2(z, scene->fractal);
	z = complex_add(complex_mult(z, z), c);
	return (z);
}

int	iterate(t_scene *scene, t_vec2 z, t_vec2 c)
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

t_vec2	get_position(t_scene *scene, double x, double y)
{
	double	px;
	double	py;

	px = x / (double) scene->width - scene->offset.x;
	py = y / (double) scene->height - scene->offset.y;
	px *= scene->aspect * scene->zoom;
	py *= scene->zoom;
	return (vec2(px, py));
}

void	run(t_scene *scene)
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
			if (scene->type == TYPE_MANDELBROT)
			{
				z = vec2(0, 0);
				c = get_position(scene, x, y);
			}
			else
			{
				z = get_position(scene, x, y);
				c = apply_op_double(scene->time, scene->julia);
			}
			result = iterate(scene, z, c);
			set_color_at(scene->img->pixels + (y * scene->width + x) * 4, lerp_color(0x000000ff, 0xff0000ff, (double) result / (double) scene->iterations));
			y++;
		}
		x++;
	}
}

int32_t	main(int argc, char **argv)
{
	t_scene	scene;
	mlx_t	*mlx;

	(void) argc;
	(void) argv;
	setup_scene(&scene);
	setup_hooks(&scene);
	mlx = scene.mlx;
	if (scene.renderer == RENDERER_CPU)
		run(&scene);
	render_info(&scene);
	update_uniforms(&scene);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
