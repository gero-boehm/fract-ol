/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uniforms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:37:04 by gbohm             #+#    #+#             */
/*   Updated: 2022/12/13 06:44:42 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

void	set_offset_uniform(mlx_t *mlx, t_vec2 *offset)
{
	mlx_set_uniform_2d(mlx, "doffset", offset->x, offset->y);
	mlx_set_uniform_2f(mlx, "foffset", (float) offset->x, (float) offset->y);
}

void	set_aspect_uniform(mlx_t *mlx, double aspect)
{
	mlx_set_uniform_1d(mlx, "daspect", aspect);
	mlx_set_uniform_1f(mlx, "faspect", (float) aspect);
}

void	set_zoom_uniform(mlx_t *mlx, double zoom)
{
	mlx_set_uniform_1d(mlx, "dzoom", zoom);
	mlx_set_uniform_1f(mlx, "fzoom", (float) zoom);
}
