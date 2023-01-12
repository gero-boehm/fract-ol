/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:37:25 by gbohm             #+#    #+#             */
/*   Updated: 2023/01/12 12:53:53 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

void	init_scene(t_scene *scene)
{
	scene->mlx = NULL;
	scene->img = NULL;
	scene->info_img = NULL;
	scene->width = DEFAULT_WIDTH;
	scene->height = DEFAULT_HEIGHT;
	scene->aspect = (double) scene->width / (double) scene->height;
	scene->zoom = DEFAULT_ZOOM;
	scene->iterations = DEFAULT_ITERATIONS;
	scene->time = 0;
	scene->mouse = vec2(.5, .5);
	scene->offset = vec2(.5, .5);
	scene->renderer = RENDERER_CPU;
	scene->type = TYPE_MANDELBROT;
	scene->fractal = ops(OP_NONE, OP_NONE);
	scene->julia = ops(OP_NONE, OP_NONE);
}

int	init_mlx2(t_scene *scene)
{
	scene->mlx = mlx_init(DEFAULT_WIDTH, DEFAULT_HEIGHT, "fract-ol", true);
	if (scene->mlx == NULL)
		return (1);
	scene->img = mlx_new_image(scene->mlx, DEFAULT_WIDTH, DEFAULT_HEIGHT);
	if (scene->img == NULL)
		return (free(scene->mlx), 2);
	mlx_image_to_window(scene->mlx, scene->img, 0, 0);
	return (0);
}

void	setup_hooks(t_scene *scene)
{
	mlx_t	*mlx;

	mlx = scene->mlx;
	mlx_loop_hook(mlx, &on_loop, scene);
	mlx_resize_hook(mlx, &on_resize, scene);
	mlx_scroll_hook(mlx, &on_scroll, scene);
	mlx_key_hook(mlx, &on_keydown, scene);
}
