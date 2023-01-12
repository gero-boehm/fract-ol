/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:40:30 by gbohm             #+#    #+#             */
/*   Updated: 2023/01/12 10:45:09 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "fract_ol.h"



// TODO:
// move ESC key press handler from loop to key hook

int32_t	main(int argc, const char **argv)
{
	t_scene	scene;
	mlx_t	*mlx;

	if (setup_scene2(&scene))
	{
		write(1, "failed to instantiate scene.\n", 29);
		return (1);
	}
	if (parse(argc, argv, &scene))
	{
		write(1, "failed to parse parameters.\n", 28);
		return (2);
	}
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
