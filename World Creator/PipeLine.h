#pragma once

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "ShaderProgram.h"

class PipeLine
{
public:
	PipeLine();
	static inline GLvoid clearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
	{
		glClearColor(red, green, blue, alpha);
	}
	static inline GLvoid clearColor(glm::vec4 & color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}
	static inline GLvoid clear(GLbitfield mask)
	{
		glClear(mask);
	}
	static inline GLvoid enable(GLenum cap)
	{
		glEnable(cap);
	}
	static inline GLvoid disable(GLenum cap)
	{
		glDisable(cap);
	}
	static inline GLvoid frontFace(GLenum mode)
	{
		glFrontFace(mode);
	}
	static inline GLvoid cullFace(GLenum mode)
	{
		glCullFace(mode);
	}
	static inline GLvoid blendFunc(GLenum sfacfor, GLenum dfactor)
	{
		glBlendFunc(sfacfor, dfactor);
	}
	static inline GLvoid alphaFunc(GLenum func, GLclampf ref)
	{
		glAlphaFunc(func, ref);
	}
	static inline GLvoid lineWidth(GLfloat width)
	{
		glLineWidth(width);
	}
	static inline GLvoid pointSize(GLfloat size)
	{
		glPointSize(size);
	}

	/*
	glLineWidth(2.0f);
	*/
	~PipeLine();
public:
};

