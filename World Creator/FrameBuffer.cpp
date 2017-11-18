#include "FrameBuffer.h"


FrameBuffer::FrameBuffer()
{
}

GLint FrameBuffer::init()
{
	glGenFramebuffers(1, &ID);

	glBindFramebuffer(GL_FRAMEBUFFER, ID);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	if (!glIsFramebuffer(ID))
	{
		return 1;
	}

	return 0;
}

FrameBuffer::~FrameBuffer()
{
	GLvoid deleteFrameBuffer();
}
