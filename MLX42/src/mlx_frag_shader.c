/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_frag_shader.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 22:34:59 by W2wizard          #+#    #+#             */
/*   Updated: 2022/12/15 10:39:32 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// If you wish to modify this file edit the .vert or .frag file!

#include "MLX42/MLX42_Int.h"

const char* frag_shader = "#version 400\n"
	"precision highp double;\n"
	"precision highp float;\n"
	"in vec2 TexCoord;\n"
	"flat in int TexIndex;\n"
	"out vec4 FragColor;\n"
	"uniform sampler2D Texture0;\n"
	"uniform double daspect;\n"
	"uniform double dzoom;\n"
	"uniform dvec2 doffset;\n"
	"uniform float faspect;\n"
	"uniform float fzoom;\n"
	"uniform vec2 foffset;\n"
	"uniform int iterations;\n"
	"uniform float time;\n"
	"uniform int renderer;\n"
	"uniform int type;\n"
	"uniform int subtype;\n"
	"\n"
	"float hue2rgb(float f1, float f2, float hue) {\n"
	"	if (hue < 0.0)\n"
	"		hue += 1.0;\n"
	"	else if (hue > 1.0)\n"
	"		hue -= 1.0;\n"
	"	float res;\n"
	"	if ((6.0 * hue) < 1.0)\n"
	"		res = f1 + (f2 - f1) * 6.0 * hue;\n"
	"	else if ((2.0 * hue) < 1.0)\n"
	"		res = f2;\n"
	"	else if ((3.0 * hue) < 2.0)\n"
	"		res = f1 + (f2 - f1) * ((2.0 / 3.0) - hue) * 6.0;\n"
	"	else\n"
	"		res = f1;\n"
	"	return res;\n"
	"}\n"
	"\n"
	"vec3 hsl2rgb(vec3 hsl) {\n"
	"	vec3 rgb;\n"
	"	\n"
	"	if (hsl.y == 0.0) {\n"
	"		rgb = vec3(hsl.z);\n"
	"	} else {\n"
	"		float f2;\n"
	"		\n"
	"		if (hsl.z < 0.5)\n"
	"			f2 = hsl.z * (1.0 + hsl.y);\n"
	"		else\n"
	"			f2 = hsl.z + hsl.y - hsl.y * hsl.z;\n"
	"			\n"
	"		float f1 = 2.0 * hsl.z - f2;\n"
	"		\n"
	"		rgb.r = hue2rgb(f1, f2, hsl.x + (1.0/3.0));\n"
	"		rgb.g = hue2rgb(f1, f2, hsl.x);\n"
	"		rgb.b = hue2rgb(f1, f2, hsl.x - (1.0/3.0));\n"
	"	}   \n"
	"	return rgb;\n"
	"}\n"
	"\n"
	"vec3 hsl2rgb(float h, float s, float l) {\n"
	"	return hsl2rgb(vec3(h, s, l));\n"
	"}\n"
	"\n"
	"dvec2 complex_multiply(dvec2 z1, dvec2 z2)\n"
	"{\n"
	"	double r = z1.x * z2.x - z1.y * z2.y;\n"
	"	double i = z1.x * z2.y + z1.y * z2.x;\n"
	"\n"
	"	return dvec2(r, i);\n"
	"}\n"
	"\n"
	"double complex_modulus_squared(dvec2 z)\n"
	"{\n"
	"	return z.x * z.x + z.y * z.y;\n"
	"}\n"
	"\n"
	"dvec2 mandelbrot(dvec2 z, dvec2 c)\n"
	"{\n"
	"	return complex_multiply(z, z) + c;\n"
	"}\n"
	"\n"
	"dvec2 tricorn(dvec2 z, dvec2 c)\n"
	"{\n"
	"	z *= dvec2(1., -1.);\n"
	"	z = complex_multiply(z, z) + c;\n"
	"	return z;\n"
	"}\n"
	"\n"
	"dvec2 burning_ship(dvec2 z, dvec2 c)\n"
	"{\n"
	"	z = dvec2(abs(z.x), abs(z.y));\n"
	"	z = complex_multiply(z, z) + c;\n"
	"	return z;\n"
	"}\n"
	"\n"
	"int iterate(dvec2 z, dvec2 c)\n"
	"{\n"
	"	for(int i = 0; i < iterations; i++)\n"
	"	{\n"
	"		switch(type) {\n"
	"			case 0:\n"
	"				z = mandelbrot(z, c);\n"
	"				break;\n"
	"			case 1:\n"
	"				z = tricorn(z, c);\n"
	"				break;\n"
	"			case 2:\n"
	"				z = burning_ship(z, c);\n"
	"				break;\n"
	"		}\n"
	"		if(complex_modulus_squared(z) > 4.)\n"
	"			return i;\n"
	"	}\n"
	"	return 0;\n"
	"}\n"
	"\n"
	"vec2 complex_multiply(vec2 z1, vec2 z2)\n"
	"{\n"
	"	float r = z1.x * z2.x - z1.y * z2.y;\n"
	"	float i = z1.x * z2.y + z1.y * z2.x;\n"
	"\n"
	"	return vec2(r, i);\n"
	"}\n"
	"\n"
	"float complex_modulus_squared(vec2 z)\n"
	"{\n"
	"	return z.x * z.x + z.y * z.y;\n"
	"}\n"
	"\n"
	"vec2 mandelbrot(vec2 z, vec2 c)\n"
	"{\n"
	"	return complex_multiply(z, z) + c;\n"
	"}\n"
	"\n"
	"vec2 tricorn(vec2 z, vec2 c)\n"
	"{\n"
	"	z *= vec2(1., -1.);\n"
	"	z = complex_multiply(z, z) + c;\n"
	"	return z;\n"
	"}\n"
	"\n"
	"vec2 burning_ship(vec2 z, vec2 c)\n"
	"{\n"
	"	z = vec2(abs(z.x), abs(z.y));\n"
	"	z = complex_multiply(z, z) + c;\n"
	"	return z;\n"
	"}\n"
	"\n"
	"int iterate(vec2 z, vec2 c)\n"
	"{\n"
	"	for(int i = 0; i < iterations; i++)\n"
	"	{\n"
	"		switch(type) {\n"
	"			case 0:\n"
	"				z = mandelbrot(z, c);\n"
	"				break;\n"
	"			case 1:\n"
	"				z = tricorn(z, c);\n"
	"				break;\n"
	"			case 2:\n"
	"				z = burning_ship(z, c);\n"
	"				break;\n"
	"		}\n"
	"		if(complex_modulus_squared(z) > 4.)\n"
	"			return i;\n"
	"	}\n"
	"	return 0;\n"
	"}\n"
	"\n"
	"void main()\n"
	"{\n"
	"	if(renderer == 0)\n"
	"	{\n"
	"		FragColor = texture(Texture0, TexCoord);\n"
	"		return;\n"
	"	}\n"
	"	int result;\n"
	"\n"
	"	if(renderer == 1)\n"
	"	{\n"
	"		dvec2 z;\n"
	"		dvec2 c;\n"
	"		if(subtype == 0)\n"
	"		{\n"
	"			z = dvec2(0., 0.);\n"
	"			c = dvec2(TexCoord - doffset) * dvec2(daspect, 1.) * dzoom;\n"
	"		}\n"
	"		else\n"
	"		{\n"
	"			z = dvec2(TexCoord - doffset) * dvec2(daspect, 1.) * dzoom;\n"
	"			c = dvec2(sin(time / 10.), cos(time / 10.));\n"
	"		}\n"
	"		result = iterate(z, c);\n"
	"	}\n"
	"	else\n"
	"	{\n"
	"		vec2 z;\n"
	"		vec2 c;\n"
	"		if(subtype == 0)\n"
	"		{\n"
	"			z = vec2(0., 0.);\n"
	"			c = vec2(TexCoord - foffset) * vec2(faspect, 1.) * fzoom;\n"
	"		}\n"
	"		else\n"
	"		{\n"
	"			z = vec2(TexCoord - foffset) * vec2(faspect, 1.) * fzoom;\n"
	"			c = vec2(sin(time / 10.), cos(time / 10.));\n"
	"		}\n"
	"		result = iterate(z, c);\n"
	"	}\n"
	"	vec3 color = mix(vec3(0., 0., 0.), hsl2rgb(mod(time, 1.), 1., .5), float(result) / float(iterations));\n"
	// "	vec3 color = mix(vec3(0., 0., 0.), hsl2rgb(mod(time, 1.), 1., .5), mod(float(result) / 10. + time, 10.));\n"
	"	FragColor = vec4(color, 1.0);\n"
	"}\n";
