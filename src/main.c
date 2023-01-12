/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:40:30 by gbohm             #+#    #+#             */
/*   Updated: 2023/01/12 14:20:09 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "fract_ol.h"

static void	print_instructions(void)
{
	const char	*str = "\nUsage: <type> [ops_fractal] [ops_julia] [time]\n\n"
		"types:\n"
		"    mandelbrot\n"
		"    tricorn\n"
		"    burning_ship\n"
		"    julia\n\n"
		"ops:\n"
		"    zero\n"
		"    none\n"
		"    neg\n"
		"    abs\n"
		"    sin\n"
		"    cos\n"
		"    tan\n"
		"    asin\n"
		"    atan\n"
		"    csc\n"
		"    sec\n"
		"    cot\n"
		"    exp\n\n"
		"time:\n"
		"    time can be defined as any valid float.\n\n";

	write(1, str, ft_strlen(str));
}

int32_t	main(int argc, const char **argv)
{
	t_scene	scene;
	mlx_t	*mlx;

	init_scene(&scene);
	if (argc == 1 || parse(argc, argv, &scene))
	{
		if (argc != 1)
			write(1, "failed to parse parameters.\n", 28);
		print_instructions();
		return (1);
	}
	if (init_mlx2(&scene))
	{
		write(1, "failed to instantiate scene.\n", 29);
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
