/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:11:34 by gbohm             #+#    #+#             */
/*   Updated: 2022/12/18 16:09:58 by gbohm            ###   ########.fr       */
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

void	update_ops(t_scene *scene, mlx_key_data_t key, int *rerender)
{
	t_op	op;

	op = get_op_for_key(key.key);
	if (op == OP_INVALID)
		return ;
	if (key.modifier & MLX_ALT)
	{
		if (key.modifier & MLX_SHIFT)
			scene->julia.im = op;
		else
			scene->julia.re = op;
	}
	else
	{
		if (key.modifier & MLX_SHIFT)
			scene->fractal.im = op;
		else
			scene->fractal.re = op;
	}
	*rerender = 1;
}

void	update_settings(t_scene *scene, keys_t key, int *rerender)
{
	if (key == MLX_KEY_Z)
		*rerender |= !(scene->type = TYPE_MANDELBROT);
	if (key == MLX_KEY_X)
		*rerender |= (scene->type = TYPE_JULIA);
	if (key == MLX_KEY_B)
		*rerender |= !(scene->renderer = RENDERER_CPU);
	if (key == MLX_KEY_N)
		*rerender |= (scene->renderer = RENDERER_GPU_DOUBLE);
	if (key == MLX_KEY_M)
		*rerender |= (scene->renderer = RENDERER_GPU_FLOAT);
	if (key == MLX_KEY_KP_0)
	{
		scene->offset = vec2(.5, .5);
		scene->zoom = DEFAULT_ZOOM;
		scene->iterations = DEFAULT_ITERATIONS;
		*rerender = 1;
	}
}
