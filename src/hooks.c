/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:48:13 by gbohm             #+#    #+#             */
/*   Updated: 2022/12/17 17:31:57 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

void	update_iterations(t_scene *scene, int *rerender)
{
	mlx_t	*mlx;

	mlx = scene->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		scene->iterations++;
		*rerender = 1;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		scene->iterations--;
		*rerender = 1;
	}
}

void	update_time(t_scene *scene, int *rerender)
{
	mlx_t	*mlx;
	float	step;

	mlx = scene->mlx;
	step = .1;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT_SHIFT))
		step = .5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT_ALT))
		step = .01;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		mlx_set_uniform_1f(mlx, "time", scene->time -= step);
		*rerender = 1;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		mlx_set_uniform_1f(mlx, "time", scene->time += step);
		*rerender = 1;
	}
}

void	update_mouse(t_scene *scene, int *rerender)
{
	mlx_t	*mlx;
	int32_t	x;
	int32_t	y;
	double	mx;
	double	my;

	mlx = scene->mlx;
	mlx_get_mouse_pos(mlx, &x, &y);
	mx = (double) x / (double) scene->width;
	my = (double) y / (double) scene->height;
	if (mlx_is_mouse_down(mlx, MLX_MOUSE_BUTTON_LEFT)
		&& (mx != scene->mouse.x || my != scene->mouse.y))
	{
		scene->offset = vec2_add(vec2_sub(vec2(mx, my), scene->mouse),
				scene->offset);
		*rerender = 1;
	}
	scene->mouse.x = mx;
	scene->mouse.y = my;
}


void	on_loop(void *param)
{
	t_scene	*scene;
	mlx_t	*mlx;
	int		rerender;

	scene = param;
	mlx = scene->mlx;
	rerender = 0;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	update_iterations(scene, &rerender);
	update_time(scene, &rerender);
	update_mouse(scene, &rerender);
	if (!rerender)
		return ;
	if (scene->renderer == RENDERER_CPU)
		run(scene);
	update_uniforms(scene);
	render_info(scene);
}

void	on_resize(int32_t width, int32_t height, void *param)
{
	t_scene	*scene;
	mlx_t	*mlx;

	scene = param;
	mlx = scene->mlx;
	scene->width = width;
	scene->height = height;
	scene->aspect = (double) width / (double) height;
	mlx_resize_image(scene->img, width, height);
	if (scene->renderer == RENDERER_CPU)
		run(scene);
	update_uniforms(scene);
	render_info(scene);
}

void	on_scroll(double xdelta, double ydelta, void *param)
{
	t_scene	*scene;
	mlx_t	*mlx;
	double	step;
	t_vec2	difference;

	(void) xdelta;
	scene = param;
	mlx = scene->mlx;
	step = (ydelta * scene->zoom) / 10.;
	scene->zoom += step;
	difference = vec2_sub(scene->mouse, scene->offset);
	scene->offset = vec2_add(vec2_mult_scalar(
				vec2_div_scalar(difference, scene->zoom), step), scene->offset);
	if (scene->renderer == RENDERER_CPU)
		run(scene);
	update_uniforms(scene);
	render_info(scene);
}

void	on_keydown(mlx_key_data_t key, void *param)
{
	const int		count = 14;
	const keys_t	keys[] = {MLX_KEY_Q, MLX_KEY_W, MLX_KEY_E, MLX_KEY_R, MLX_KEY_T, MLX_KEY_Y, MLX_KEY_U, MLX_KEY_I, MLX_KEY_O, MLX_KEY_P, MLX_KEY_A, MLX_KEY_S, MLX_KEY_D, MLX_KEY_F};
	const t_op		ops[] = {OP_NONE, OP_NEG, OP_ABS, OP_SIN, OP_COS, OP_TAN, OP_ASIN, OP_ACOS, OP_ATAN, OP_CSC, OP_SEC, OP_COT, OP_EXP, OP_ZERO};
	t_scene			*scene;
	mlx_t			*mlx;
	int				i;

	if (key.action != MLX_PRESS)
		return ;
	scene = param;
	mlx = scene->mlx;
	(void) key;
	i = 0;
	while (i < count)
	{
		if (key.key == keys[i])
		{
			if (key.modifier & MLX_ALT)
			{
				if (key.modifier & MLX_SHIFT)
					scene->julia.im = ops[i];
				else
					scene->julia.re = ops[i];
			}
			else
			{
				if (key.modifier & MLX_SHIFT)
					scene->fractal.im = ops[i];
				else
					scene->fractal.re = ops[i];
			}
			break ;
		}
		i++;
	}
	if (key.key == MLX_KEY_Z)
		scene->type = TYPE_MANDELBROT;
	if (key.key == MLX_KEY_X)
		scene->type = TYPE_JULIA;
	if (key.key == MLX_KEY_B)
		scene->renderer = RENDERER_CPU;
	if (key.key == MLX_KEY_N)
		scene->renderer = RENDERER_GPU_DOUBLE;
	if (key.key == MLX_KEY_M)
		scene->renderer = RENDERER_GPU_FLOAT;
	if (key.key == MLX_KEY_KP_0)
	{
		scene->offset = vec2(.5, .5);
		scene->zoom = DEFAULT_ZOOM;
		scene->iterations = DEFAULT_ITERATIONS;
	}
	// if (key.key == MLX_KEY_KP_5)
	// {
	// 	printf("%lf\n", scene->offset.x);
	// }
	if (scene->renderer == RENDERER_CPU)
		run(scene);
	update_uniforms(scene);
	render_info(scene);
}
