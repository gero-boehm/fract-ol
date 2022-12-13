/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:49 by gbohm             #+#    #+#             */
/*   Updated: 2022/12/13 16:55:01 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

# include "MLX42/MLX42.h"

# define DEFAULT_ZOOM 5
# define DEFAULT_ITERATIONS 100
# define DEFAULT_WIDTH 512
# define DEFAULT_HEIGHT 512

typedef enum e_renderer {
	RENDERER_CPU,
	RENDERER_GPU_DOUBLE,
	RENDERER_GPU_FLOAT,
}	t_renderer;

typedef enum e_type {
	TYPE_MANDELBROT,
	TYPE_TRICORN,
	TYPE_BURNING_SHIP,
}	t_type;

typedef enum e_subtype {
	SUBTYPE_MANDELBROT,
	SUBTYPE_JULIA,
}	t_subtype;

typedef struct s_vec2 {
	double	x;
	double	y;
}	t_vec2;

typedef struct s_settings {
	t_renderer	renderer;
	t_type		type;
	t_subtype	subtype;
}	t_settings;

typedef struct s_scene {
	mlx_t		*mlx;
	uint32_t	width;
	uint32_t	height;
	double		aspect;
	double		zoom;
	t_vec2		mouse;
	t_vec2		offset;
	int			iterations;
	float		time;
	t_settings	settings;
}	t_scene;

t_vec2	vec2(double x, double y);
t_vec2	vec2_add(t_vec2 v1, t_vec2 v2);
t_vec2	vec2_sub(t_vec2 v1, t_vec2 v2);
t_vec2	vec2_div_scalar(t_vec2 v, double s);
t_vec2	vec2_mult_scalar(t_vec2 v, double s);

void	set_offset_uniform(mlx_t *mlx, t_vec2 *offset);
void	set_aspect_uniform(mlx_t *mlx, double aspect);
void	set_zoom_uniform(mlx_t *mlx, double zoom);

t_vec2	mandelbrot(t_vec2 z, t_vec2 c);
t_vec2	tricorn(t_vec2 z, t_vec2 c);
t_vec2	burning_ship(t_vec2 z, t_vec2 c);

t_vec2	complex_multiply(t_vec2 z1, t_vec2 z2);
t_vec2	complex_add(t_vec2 z1, t_vec2 z2);
double	complex_modulus_squared(t_vec2 z);

#endif