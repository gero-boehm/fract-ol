/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:49 by gbohm             #+#    #+#             */
/*   Updated: 2022/12/12 17:43:08 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

# include "MLX42/MLX42.h"

# define DEFAULT_ZOOM 5
# define DEFAULT_ITERATIONS 100
# define DEFAULT_WIDTH 512
# define DEFAULT_HEIGHT 512
# define DEFAULT_COLOR 0

typedef struct s_vec2 {
	double	x;
	double	y;
}	t_vec2;

typedef struct s_scene {
	mlx_t		*mlx;
	uint32_t	width;
	uint32_t	height;
	double		aspect;
	double		zoom;
	t_vec2		mouse;
	t_vec2		offset;
	int			iterations;
	float		color;
}	t_scene;

t_vec2	vec2(double x, double y);
t_vec2	vec2_add(t_vec2 v1, t_vec2 v2);
t_vec2	vec2_sub(t_vec2 v1, t_vec2 v2);
t_vec2	vec2_div_scalar(t_vec2 v, double s);
t_vec2	vec2_mult_scalar(t_vec2 v, double s);


#endif