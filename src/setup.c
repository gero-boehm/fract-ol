/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:37:25 by gbohm             #+#    #+#             */
/*   Updated: 2022/12/16 01:07:22 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fract_ol.h"

void	setup_scene(t_scene *scene)
{
	t_settings	settings;

	scene->mlx = mlx_init(DEFAULT_WIDTH, DEFAULT_HEIGHT, "MLX42", true);
	if (scene->mlx == NULL)
		exit(EXIT_FAILURE);
	scene->img = mlx_new_image(scene->mlx, DEFAULT_WIDTH, DEFAULT_HEIGHT);
	if (scene->img == NULL)
	{
		free(scene->mlx);
		exit(EXIT_FAILURE);
	}
	mlx_image_to_window(scene->mlx, scene->img, 0, 0);
	scene->info = NULL;
	// scene->info = mlx_put_string(scene->mlx, "testing12: aa\n aa: tt", 0, 0);
	// if (scene->info == NULL)
	// {
	// 	free(scene->mlx);
	// 	free(scene->img);
	// 	exit(EXIT_FAILURE);
	// }
	// mlx_image_to_window(scene->mlx, scene->info, 0, 0);
	scene->width = DEFAULT_WIDTH;
	scene->height = DEFAULT_HEIGHT;
	scene->aspect = (double) scene->width / (double) scene->height;
	scene->zoom = DEFAULT_ZOOM;
	scene->iterations = DEFAULT_ITERATIONS;
	scene->time = 0;
	scene->mouse = vec2(.5, .5);
	scene->offset = vec2(.5, .5);
	settings.renderer = RENDERER_CPU;
	settings.re_op = OP_NONE;
	settings.im_op = OP_NONE;
	settings.j_re_op = OP_NONE;
	settings.j_im_op = OP_NONE;
	settings.type = TYPE_MANDELBROT;
	scene->settings = settings;
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
