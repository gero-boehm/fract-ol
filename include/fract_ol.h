/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:49 by gbohm             #+#    #+#             */
/*   Updated: 2022/12/15 19:02:39 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

# include "MLX42/MLX42.h"

# define DEFAULT_ZOOM 5
# define DEFAULT_ITERATIONS 100
# define DEFAULT_WIDTH 256
# define DEFAULT_HEIGHT 256

typedef enum e_renderer {
	RENDERER_CPU,
	RENDERER_GPU_DOUBLE,
	RENDERER_GPU_FLOAT,
}	t_renderer;

typedef enum e_color_component {
	R,
	G,
	B,
	A,
}	t_color_component;

typedef enum e_op {
	OP_NONE,
	OP_NEG,
	OP_ABS,
	OP_SIN,
	OP_COS,
	OP_TAN,
	OP_ASIN,
	OP_ACOS,
	OP_ATAN,
	OP_CSC,
	OP_SEC,
	OP_COT,
	OP_EXP,
}	t_op;

typedef enum e_type {
	TYPE_MANDELBROT,
	TYPE_JULIA,
}	t_type;

typedef struct s_vec2 {
	double	x;
	double	y;
}	t_vec2;

typedef struct s_settings {
	t_renderer	renderer;
	t_op		re_op;
	t_op		im_op;
	t_type		type;
}	t_settings;

typedef struct s_scene {
	mlx_t		*mlx;
	uint32_t	width;
	uint32_t	height;
	mlx_image_t	*img;
	mlx_image_t	*info;
	double		aspect;
	double		zoom;
	t_vec2		mouse;
	t_vec2		offset;
	int			iterations;
	float		time;
	t_settings	settings;
}	t_scene;

void		setup_scene(t_scene *scene);
void		setup_hooks(t_scene *scene);

t_vec2		vec2(double x, double y);
t_vec2		vec2_add(t_vec2 v1, t_vec2 v2);
t_vec2		vec2_sub(t_vec2 v1, t_vec2 v2);
t_vec2		vec2_div_scalar(t_vec2 v, double s);
t_vec2		vec2_mult_scalar(t_vec2 v, double s);

void		set_offset_uniform(mlx_t *mlx, t_vec2 *offset);
void		set_aspect_uniform(mlx_t *mlx, double aspect);
void		set_zoom_uniform(mlx_t *mlx, double zoom);

t_vec2		mandelbrot(t_vec2 z, t_vec2 c);
t_vec2		tricorn(t_vec2 z, t_vec2 c);
t_vec2		burning_ship(t_vec2 z, t_vec2 c);

t_vec2		complex_mult(t_vec2 z1, t_vec2 z2);
t_vec2		complex_add(t_vec2 z1, t_vec2 z2);
double		complex_modulus_squared(t_vec2 z);

void		on_loop(void *param);
void		on_resize(int32_t width, int32_t height, void *param);
void		on_scroll(double xdelta, double ydelta, void *param);
void		on_keydown(mlx_key_data_t key, void *param);

uint32_t	lerp_color(uint32_t min, uint32_t max, double t);
void		set_color_at(uint8_t *pixel, uint32_t color);

void		run(t_scene *scene);

#endif