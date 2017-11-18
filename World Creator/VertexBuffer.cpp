#include "VertexBuffer.h"

using namespace std;

VertexBuffer::VertexBuffer()
{
	VBO = 0;
	size = 0;
	drawMode = GL_TRIANGLES;

}

VertexBuffer::VertexBuffer(const VertexBuffer & right)
{
	drawMode = right.drawMode;

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	if (!glIsBuffer(VBO))
	{
#ifdef _DEBUG
		cout << "VertexBuffer£ºBufferÉêÇëÊ§°Ü£¡" << endl;
#endif
		throw runtime_error("VertexBuffer£ºBufferÉêÇëÊ§°Ü£¡");
	}

	glBindBuffer(GL_COPY_READ_BUFFER, right.VBO);
	glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &size);

	glBindBuffer(GL_COPY_WRITE_BUFFER, VBO);
	glBufferData(GL_COPY_WRITE_BUFFER, size, nullptr, GL_STATIC_DRAW);
	if (size)
	{
		glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, this->size);
	}
	glBindBuffer(GL_COPY_READ_BUFFER, 0);
	glBindBuffer(GL_COPY_WRITE_BUFFER, 0);

	size = size / sizeof(GLfloat);
}

GLint VertexBuffer::init()
{
	size = 0;
	data.clear();
	drawMode = GL_TRIANGLES;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	if (!glIsBuffer(VBO))
	{
#ifdef _DEBUG
		cout << "RederList£ºBufferÉêÇëÊ§°Ü£¡" << endl;
#endif
		return 1;
	}

	return 0;
}

VertexBuffer & VertexBuffer::operator = (const VertexBuffer & right)
{
	glBindBuffer(GL_COPY_READ_BUFFER, right.VBO);
	glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &size);

	glBindBuffer(GL_COPY_WRITE_BUFFER, VBO);
	glBufferData(GL_COPY_WRITE_BUFFER, size, nullptr, GL_STATIC_DRAW);
	if (size)
	{
		glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, this->size);
	}
	glBindBuffer(GL_COPY_READ_BUFFER, 0);
	glBindBuffer(GL_COPY_WRITE_BUFFER, 0);

	size = size / sizeof(GLfloat);

	return *this;
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &VBO);
}
