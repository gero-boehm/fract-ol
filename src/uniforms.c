/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uniforms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:37:04 by gbohm             #+#    #+#             */
/*   Updated: 2022/12/17 17:19:21 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

static void	set_aspect_uniform(mlx_t *mlx, double aspect)
{
	mlx_set_uniform_1d(mlx, "daspect", aspect);
	mlx_set_uniform_1f(mlx, "faspect", (float) aspect);
}

static void	set_zoom_uniform(mlx_t *mlx, double zoom)
{
	mlx_set_uniform_1d(mlx, "dzoom", zoom);
	mlx_set_uniform_1f(mlx, "fzoom", (float) zoom);
}

static void	set_offset_uniform(mlx_t *mlx, t_vec2 *offset)
{
	mlx_set_uniform_2d(mlx, "doffset", offset->x, offset->y);
	mlx_set_uniform_2f(mlx, "foffset", (float) offset->x, (float) offset->y);
}

void	update_uniforms(t_scene *scene)
{
	mlx_t	*mlx;

	mlx = scene->mlx;
	set_aspect_uniform(mlx, scene->aspect);
	set_zoom_uniform(mlx, scene->zoom);
	set_offset_uniform(mlx, &scene->offset);
	mlx_set_uniform_1i(mlx, "iterations", scene->iterations);
	mlx_set_uniform_1f(mlx, "time", scene->time);
	mlx_set_uniform_1i(mlx, "renderer", scene->renderer);
	mlx_set_uniform_1i(mlx, "re_op", scene->fractal.re);
	mlx_set_uniform_1i(mlx, "im_op", scene->fractal.im);
	mlx_set_uniform_1i(mlx, "j_re_op", scene->julia.re);
	mlx_set_uniform_1i(mlx, "j_im_op", scene->julia.im);
	mlx_set_uniform_1i(mlx, "type", scene->type);
}
