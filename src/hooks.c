/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:48:13 by gbohm             #+#    #+#             */
/*   Updated: 2023/01/12 14:15:19 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

void	on_loop(void *param)
{
	t_scene	*scene;
	int		rerender;

	scene = param;
	rerender = 0;
	update_iterations(scene, &rerender);
	update_time(scene, &rerender);
	update_mouse(scene, &rerender);
	if (!rerender)
		return ;
	if (scene->renderer == RENDERER_CPU)
		calculate(scene);
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
		calculate(scene);
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
		calculate(scene);
	update_uniforms(scene);
	render_info(scene);
}

void	on_keydown(mlx_key_data_t key, void *param)
{
	t_scene	*scene;
	int		rerender;

	if (key.action != MLX_PRESS)
		return ;
	scene = param;
	if (key.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(scene->mlx);
		return ;
	}
	rerender = 0;
	update_ops(scene, key, &rerender);
	update_settings(scene, key.key, &rerender);
	if (!rerender)
		return ;
	if (scene->renderer == RENDERER_CPU)
		calculate(scene);
	update_uniforms(scene);
	render_info(scene);
}
