#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <GL/glew.h>

#include "RenderBuffer.h"
#include "Texture2D.h"

class FrameBuffer
{
public:
	FrameBuffer();
	FrameBuffer(const FrameBuffer & right);
	GLint init();
	FrameBuffer & operator=(const FrameBuffer & right);

	inline GLvoid deleteFrameBuffer()
	{
		glDeleteFramebuffers(1, &ID);
		ID = 0;
	}
	inline GLvoid bind(GLenum target = GL_FRAMEBUFFER)
	{
		glBindFramebuffer(target, ID);
	}
	inline GLvoid framebufferParameteri(GLenum target, GLenum pname, GLint param)
	{
		glBindFramebuffer(target, ID);
		glFramebufferParameteri(target, pname, param);
	}
	inline GLvoid framebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLint renderbuffer)
	{
		glBindFramebuffer(target, ID);
		glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
	}
	inline GLvoid framebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, const RenderBuffer & renderbuffer)
	{
		glBindFramebuffer(target, ID);
		glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer.getID());
	}
	inline GLvoid framebufferTexture2D(GLenum target, GLenum attachment, GLenum texttarget, GLuint texture, GLint level)
	{
		glBindFramebuffer(target, ID);
		glFramebufferTexture2D(target, attachment, texttarget, texture, level);
	}
	inline GLvoid framebufferTexture2D(GLenum target, GLenum attachment, const Texture2D & texture, GLint level)
	{
		glBindFramebuffer(target, ID);
		glFramebufferTexture2D(target, attachment, GL_TEXTURE_2D, texture.getID(), level);
	}
	inline GLenum checkFramebufferStatus(GLenum target)
	{
		glBindFramebuffer(target, ID);
		return glCheckFramebufferStatus(target);
	}
	inline static GLvoid blitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield buffers, GLenum filter)
	{
		glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, buffers, filter);
	}
	inline GLvoid blitFramebuffer(const FrameBuffer & dst, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield buffers, GLenum filter)
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, ID);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, dst.ID);

		glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, buffers, filter);

	}
	inline GLvoid blitFramebuffer(GLuint dst, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield buffers, GLenum filter)
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, ID);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, dst);
		
		glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, buffers, filter);
	}
	inline static GLvoid resetFrameBuffer()
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	}
	inline static GLvoid resetFrameBuffer(GLenum target)
	{
		glBindFramebuffer(target, 0);

	}
	~FrameBuffer();
public:
	GLuint ID;
};

