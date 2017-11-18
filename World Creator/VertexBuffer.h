#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <iostream>
#include <queue>
#include <vector>

class VertexBuffer
{
public:
	VertexBuffer();
	VertexBuffer(const VertexBuffer & right);
	GLint init();
	VertexBuffer & operator=(const VertexBuffer & right);

	inline GLvoid move(VertexBuffer & from)
	{
		data = from.data;
		drawMode = from.drawMode;
		size = from.size;
		VBO = from.VBO;

		from.data.clear();
		from.drawMode = GL_TRIANGLES;
		from.size = 0;
		from.VBO = 0;
	}
	GLvoid updateData(GLenum usage = GL_STATIC_DRAW)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(GLfloat), data.size() ? &data[0] : nullptr, usage);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		size = data.size();
	}
	GLvoid updateSubData(GLintptr offset, GLsizeiptr count)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, offset, count*sizeof(GLfloat), data.size() ? &data[0] : nullptr);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	GLvoid updateSubData(GLintptr offset, GLsizeiptr count, GLfloat * data)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, offset, count*sizeof(GLfloat), data);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	inline GLvoid invalidateBufferData()/*OpenGL 4.3+*/
	{
		glInvalidateBufferData(VBO);
	}
	inline GLvoid invalidateBufferSubData(GLintptr offset, GLsizeiptr count)/*OpenGL 4.3+*/
	{
		glInvalidateBufferSubData(VBO, offset, count*sizeof(GLfloat));
	}

	inline GLvoid clearData()
	{
		data.clear();
	}

	inline GLvoid setVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	inline GLvoid setDrawMode(GLint drawMode)
	{
		this->drawMode = drawMode;
	}
	inline GLint getDrawMode()const
	{
		return drawMode;
	}
	inline GLuint getVBOID()const
	{
		return VBO;
	}
	static inline GLvoid resetVertexBuffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	inline GLvoid bindVBO()
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
	}
	virtual ~VertexBuffer();
public:
	std::vector<GLfloat> data;
protected:
	GLuint	VBO;
	GLint	size;
	GLint	drawMode;
};

