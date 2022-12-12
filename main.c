#include "fract_ol.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>


mlx_image_t	*g_img;
int use_double = 0;

void	on_loop(void *param)
{
	t_scene	*scene;
	mlx_t	*mlx;

	scene = param;
	mlx = scene->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		mlx_set_uniform_1i(mlx, "iterations", ++scene->iterations);
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		mlx_set_uniform_1i(mlx, "iterations", --scene->iterations);

	int32_t x;
	int32_t y;
	mlx_get_mouse_pos(mlx, &x, &y);

	scene->mouse.x = (double) x / (double) scene->width;
	scene->mouse.y = (double) y / (double) scene->height;

	scene->color += .05;
	mlx_set_uniform_1f(mlx, "color", scene->color);
}

void	on_resize(int32_t width, int32_t height, void *param)
{
	t_scene	*scene;
	mlx_t	*mlx;

	scene = param;
	mlx = scene->mlx;
	scene->width = width;
	scene->height = height;
	scene->aspect = (double) width / (double) height;
	mlx_resize_image(g_img, width, height);
	mlx_set_uniform_1d(mlx, "daspect", scene->aspect);
	mlx_set_uniform_1f(mlx, "faspect", (float) scene->aspect);
}

void on_scroll(double xdelta, double ydelta, void* param)
{
	t_scene	*scene;
	mlx_t	*mlx;
	t_vec2 difference;

	(void) xdelta;
	scene = param;
	mlx = scene->mlx;
	double step = (ydelta * scene->zoom) / 10.;
	scene->zoom += step;
	difference = vec2_sub(scene->mouse, scene->offset);
	scene->offset = vec2_add(vec2_mult_scalar(vec2_div_scalar(difference, scene->zoom), step), scene->offset);
	mlx_set_uniform_1d(mlx, "dzoom", scene->zoom);
	mlx_set_uniform_2d(mlx, "doffset", scene->offset.x, scene->offset.y);
	mlx_set_uniform_1f(mlx, "fzoom", (float) scene->zoom);
	mlx_set_uniform_2f(mlx, "foffset", (float) scene->offset.x, (float) scene->offset.y);
}

void	setup_scene(t_scene *scene)
{
	scene->mlx = mlx_init(DEFAULT_WIDTH, DEFAULT_HEIGHT, "MLX42", true);
	if (scene->mlx == NULL)
		exit(EXIT_FAILURE);
	scene->width = DEFAULT_WIDTH;
	scene->height = DEFAULT_HEIGHT;
	scene->aspect = (double) scene->width / (double) scene->height;
	scene->zoom = DEFAULT_ZOOM;
	scene->iterations = DEFAULT_ITERATIONS;
	scene->color = DEFAULT_COLOR;
	scene->mouse = vec2(.5, .5);
	scene->offset = vec2(.5, .5);
}

int32_t	main(void)
{
	t_scene scene;
	mlx_t *mlx;

	setup_scene(&scene);
	mlx = scene.mlx;
	mlx_set_uniform_1d(mlx, "daspect", scene.aspect);
	mlx_set_uniform_1d(mlx, "dzoom", scene.zoom);
	mlx_set_uniform_2d(mlx, "doffset", scene.offset.x, scene.offset.y);
	mlx_set_uniform_1f(mlx, "faspect", (float) scene.aspect);
	mlx_set_uniform_1f(mlx, "fzoom", (float) scene.zoom);
	mlx_set_uniform_2f(mlx, "foffset", (float) scene.offset.x, (float) scene.offset.y);
	mlx_set_uniform_1i(mlx, "iterations", scene.iterations);
	mlx_set_uniform_1f(mlx, "color", scene.color);
	mlx_set_uniform_1i(mlx, "use_double", use_double);
	g_img = mlx_new_image(mlx, scene.width, scene.height);
	memset(g_img->pixels, 255, g_img->width * g_img->height * sizeof(int));
	mlx_image_to_window(mlx, g_img, 0, 0);
	mlx_loop_hook(mlx, &on_loop, &scene);
	mlx_resize_hook(mlx, &on_resize, &scene);
	mlx_scroll_hook(mlx, &on_scroll, &scene);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}