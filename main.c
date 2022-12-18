/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:40:30 by gbohm             #+#    #+#             */
/*   Updated: 2022/12/18 14:29:21 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include <math.h>
#include "src/fract_ol.h"

int32_t	main(int argc, char **argv)
{
	t_scene	scene;
	mlx_t	*mlx;

	(void) argc;
	(void) argv;
	if (setup_scene2(&scene))
		return (1);
	setup_hooks(&scene);
	mlx = scene.mlx;
	if (scene.renderer == RENDERER_CPU)
		calculate(&scene);
	render_info(&scene);
	update_uniforms(&scene);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
