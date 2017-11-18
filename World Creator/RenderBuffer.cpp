#include "RenderBuffer.h"


RenderBuffer::RenderBuffer()
{
}

GLint RenderBuffer::init()
{
	glGenRenderbuffers(1, &ID);

	glBindRenderbuffer(GL_RENDERBUFFER, ID);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	if (!glIsRenderbuffer(ID))
	{
		return 1;
	}


	return 0;
}

RenderBuffer::~RenderBuffer()
{
	deleteRenderBuffer();
}
