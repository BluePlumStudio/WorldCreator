#pragma once

#include "VertexBuffer.h"

class DrawList :public VertexBuffer
{
public:
	DrawList();
	DrawList(const DrawList & right);
	GLint init(GLuint dataStride = 5);
	DrawList & operator=(const DrawList & right);

	inline GLvoid move(DrawList & from)
	{
		VAO = from.VAO;
		dataStride = from.dataStride;

		from.VAO = 0;
		from.dataStride = 5;

		VertexBuffer::move(from);
	}
	inline GLvoid setVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
	{
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	}
	inline GLvoid setDataStride(GLsizei dataStride)
	{
		this->dataStride = dataStride;
	}
	inline GLsizei getDataStride()const
	{
		return dataStride;
	}
	inline GLuint getVAOID()const
	{
		return VAO;
	}

	inline GLvoid bindVAO()
	{
		glBindVertexArray(VAO);
	}

	static inline GLvoid resetDrawListVAO()
	{
		glBindVertexArray(0);
	}

	static inline GLvoid resetDrawList()
	{
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	static GLvoid getRectangleDrawData(const glm::vec2 & position, const glm::vec2 & size, const glm::vec2 texCoords, const glm::vec2 texSize, const glm::vec4 & color, DrawList & drawList);

	GLvoid inline getRectangleDrawData(const glm::vec2 & position, const glm::vec2 & size, const glm::vec2 texCoords, const glm::vec2 texSize, const glm::vec4 & color)
	{
		getRectangleDrawData(position, size, texCoords, texSize, color, *this);
	}

	inline GLvoid DrawList::draw()
	{
		glBindVertexArray(VAO);
		glDrawArrays(drawMode, 0, size / dataStride);
	}
	~DrawList();
public:
private:
	GLuint	VAO;
	GLsizei dataStride;
};

