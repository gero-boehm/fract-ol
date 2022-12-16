/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:48:13 by gbohm             #+#    #+#             */
/*   Updated: 2022/12/16 02:30:11 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fract_ol.h"


void	on_loop(void *param)
{
	t_scene	*scene;
	mlx_t	*mlx;
	float	time_step;
	int		updated_iterations;

	scene = param;
	mlx = scene->mlx;
	updated_iterations = 0;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		scene->iterations++;
		updated_iterations = 1;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		scene->iterations--;
		updated_iterations = 1;
	}
	if (updated_iterations)
	{
		if (scene->settings.renderer == RENDERER_CPU)
			run(scene);
		set_aspect_uniform(mlx, scene->aspect);
		mlx_set_uniform_1i(mlx, "iterations", scene->iterations);
	}

	time_step = .1;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT_SHIFT))
		time_step = .5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT_ALT))
		time_step = .01;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		mlx_set_uniform_1f(mlx, "time", scene->time -= time_step);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		mlx_set_uniform_1f(mlx, "time", scene->time += time_step);

	int32_t x;
	int32_t y;
	mlx_get_mouse_pos(mlx, &x, &y);

	double mx = (double) x / (double) scene->width;
	double my = (double) y / (double) scene->height;

	if (mlx_is_mouse_down(mlx, MLX_MOUSE_BUTTON_LEFT) && (mx != scene->mouse.x || my != scene->mouse.y))
	{
		t_vec2 difference = vec2_sub(vec2(mx, my), scene->mouse);
		scene->offset = vec2_add(difference, scene->offset);
		if (scene->settings.renderer == RENDERER_CPU)
			run(scene);
		set_offset_uniform(mlx, &scene->offset);
		render_info(scene);
	}
	scene->mouse.x = mx;
	scene->mouse.y = my;

	// printf("%d\n", scene->settings.renderer);
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
	// printf("%d\n", scene->settings.renderer);
	if (scene->settings.renderer == RENDERER_CPU)
		run(scene);
	set_aspect_uniform(mlx, scene->aspect);
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
	if (scene->settings.renderer == RENDERER_CPU)
		run(scene);
	set_offset_uniform(mlx, &scene->offset);
	set_zoom_uniform(mlx, scene->zoom);
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
			if (key.modifier == MLX_ALT)
			{
				if (key.modifier == MLX_SHIFT)
				{
					scene->settings.j_im_op = ops[i];
					mlx_set_uniform_1i(mlx, "j_im_op", scene->settings.j_im_op);
				}
				else
				{
					scene->settings.j_re_op = ops[i];
					mlx_set_uniform_1i(mlx, "j_re_op", scene->settings.j_re_op);
				}
			}
			else
			{
				if (key.modifier == MLX_SHIFT)
				{
					scene->settings.im_op = ops[i];
					mlx_set_uniform_1i(mlx, "im_op", scene->settings.im_op);
				}
				else
				{
					scene->settings.re_op = ops[i];
					mlx_set_uniform_1i(mlx, "re_op", scene->settings.re_op);
				}
			}
			break ;
		}
		i++;
	}
	if (key.key == MLX_KEY_Z)
		scene->settings.type = TYPE_MANDELBROT;
	if (key.key == MLX_KEY_X)
		scene->settings.type = TYPE_JULIA;
	if (key.key == MLX_KEY_B)
		scene->settings.renderer = RENDERER_CPU;
	if (key.key == MLX_KEY_N)
		scene->settings.renderer = RENDERER_GPU_DOUBLE;
	if (key.key == MLX_KEY_M)
		scene->settings.renderer = RENDERER_GPU_FLOAT;
	if (key.key == MLX_KEY_KP_0)
	{
		scene->offset = vec2(.5, .5);
		scene->zoom = DEFAULT_ZOOM;
		scene->iterations = DEFAULT_ITERATIONS;
		set_offset_uniform(mlx, &scene->offset);
		set_zoom_uniform(mlx, scene->zoom);
		mlx_set_uniform_1i(mlx, "iterations", scene->iterations);
	}
	// if (key.key == MLX_KEY_KP_5)
	// {

	// }
	if (scene->settings.renderer == RENDERER_CPU)
		run(scene);
	mlx_set_uniform_1i(mlx, "type", scene->settings.type);
	mlx_set_uniform_1i(mlx, "renderer", scene->settings.renderer);
	render_info(scene);
}
