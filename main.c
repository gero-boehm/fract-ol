#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include <math.h>
// #include "MLX42/src/font/font.h"
#include "fract_ol.h"

double apply_op(double v, t_op op)
{
	if(op == OP_NONE)
		return (v);
	if(op == OP_NEG)
		return (-v);
	if(op == OP_ABS)
		return (fabs(v));
	if(op == OP_SIN)
		return (sin(v));
	if(op == OP_COS)
		return (cos(v));
	if(op == OP_TAN)
		return (tan(v));
	if(op == OP_ASIN)
		return (asin(v));
	if(op == OP_ACOS)
		return (acos(v));
	if(op == OP_ATAN)
		return (atan(v));
	if(op == OP_CSC)
		return (1. / sin(v));
	if(op == OP_SEC)
		return (1. / cos(v));
	if(op == OP_COT)
		return (1. / tan(v));
	if(op == OP_EXP)
		return (exp(v));
	return (0);
}

t_vec2 fractal(t_scene *scene, t_vec2 z, t_vec2 c)
{
	z = vec2(apply_op(z.x, scene->settings.re_op), apply_op(z.y, scene->settings.im_op));
	z = complex_add(complex_mult(z, z), c);
	return z;
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


void	run(t_scene *scene)
{
	uint32_t	x;
	uint32_t	y;
	t_vec2		pos;
	t_vec2		z;
	t_vec2		c;
	int			result;

	// printf("yay\n");
	x = 0;
	while (x < scene->width)
	{
		y = 0;
		while (y < scene->height)
		{
			pos = vec2(((double) x / (double) scene->width - scene->offset.x) * scene->aspect * scene->zoom, ((double) y / (double) scene->height - scene->offset.y) * scene->zoom);
			if (scene->settings.type == TYPE_MANDELBROT)
			{
				z = vec2(0, 0);
				c = pos;
			}
			else
			{
				z = pos;
				c = vec2(.3, 0);
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
	if (scene.settings.renderer == RENDERER_CPU)
		run(&scene);
	toggle_info(&scene);
	set_aspect_uniform(mlx, scene.aspect);
	set_zoom_uniform(mlx, scene.zoom);
	set_offset_uniform(mlx, &scene.offset);
	mlx_set_uniform_1i(mlx, "iterations", scene.iterations);
	mlx_set_uniform_1f(mlx, "time", scene.time);
	mlx_set_uniform_1i(mlx, "renderer", scene.settings.renderer);
	mlx_set_uniform_1i(mlx, "re_op", scene.settings.re_op);
	mlx_set_uniform_1i(mlx, "im_op", scene.settings.im_op);
	mlx_set_uniform_1i(mlx, "type", scene.settings.type);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
