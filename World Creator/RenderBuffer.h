#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <GL/glew.h>

class RenderBuffer
{
public:
	RenderBuffer();
	RenderBuffer(const RenderBuffer & right);
	GLint init();
	RenderBuffer & operator=(const RenderBuffer & right);

	inline GLvoid deleteRenderBuffer()
	{
		glDeleteRenderbuffers(1, &ID);
		ID = 0;
	}
	inline GLvoid bind(GLenum target = GL_RENDERBUFFER)
	{
		glBindRenderbuffer(target, ID);
	}
	inline GLvoid renderbufferStorage(GLenum internalformat, GLsizei width, GLsizei height, GLenum target = GL_RENDERBUFFER)
	{
		glBindRenderbuffer(target, ID);
		glRenderbufferStorage(target, internalformat, width, height);
	}
	inline GLvoid renderbufferStorageMultisample(GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLenum target = GL_RENDERBUFFER)
	{
		glBindRenderbuffer(target, ID);
		glRenderbufferStorageMultisample(target, samples, internalformat, width, height);
	}
	inline GLuint getID()const
	{
		return ID;
	}
	inline static GLvoid resetRenderBuffer(GLenum target = GL_RENDERBUFFER)
	{
		glBindRenderbuffer(target, 0);
	}
	~RenderBuffer();
private:
	GLuint ID;
};

