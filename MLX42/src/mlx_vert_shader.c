/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lol.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2wizard <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 22:34:59 by W2wizard      #+#    #+#                 */
/*   Updated: 2022/02/17 22:34:59 by W2wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// If you wish to modify this file edit the .vert or .frag file!

#include "MLX42/MLX42_Int.h"

const char* vert_shader = "#version 330 core\n"
	"\n"
	"layout(location = 0) in vec3 aPos;\n"
	"layout(location = 1) in vec2 aTexCoord;\n"
	"layout(location = 2) in int aTexIndex;\n"
	"\n"
	"out vec2 TexCoord;\n"
	"flat out int TexIndex;\n"
	"\n"
	"uniform mat4 ProjMatrix;\n"
	"\n"
	"void main()\n"
	"{\n"
	"	gl_Position = ProjMatrix * vec4(aPos, 1.0);\n"
	"	TexCoord = aTexCoord;\n"
	"	TexIndex = aTexIndex;\n"
	"}\n"
;
