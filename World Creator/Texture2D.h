#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <SOIL.h>

class Texture2D
{
public:
	Texture2D();
	Texture2D(const Texture2D & right);
	GLint init(GLenum level);
	GLint init(const char * texturePath, GLenum level);
	GLvoid init(GLuint textureID, GLenum level);
	Texture2D & operator=(const Texture2D & right);
	inline GLuint getID()const
	{
		return ID;
	}	
	inline GLuint getLevel()const
	{
		return level;
	}
	inline Texture2D & shallowCopy(const Texture2D & texture)
	{
		this->ID = texture.ID;
		return *this;
	}
	inline Texture2D & move(Texture2D & from)
	{
		ID = from.ID;
		level = from.level;

		from.ID = 0;
		from.level = GL_TEXTURE0;
	}
	inline GLvoid texImage2D(GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels = nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, ID);
		glTexImage2D(GL_TEXTURE_2D, level, internalformat, width, height, border, format, type, pixels);
	}
	inline GLvoid texParameteri(GLenum pname, GLint param)
	{
		glBindTexture(GL_TEXTURE_2D, ID);
		glTexParameteri(GL_TEXTURE_2D, pname, param);
		//glBindTexture(GL_TEXTURE_2D, 0);
	}
	inline GLvoid texParameterivec(std::vector<std::pair<GLenum, GLint>>parameters)
	{
		glBindTexture(GL_TEXTURE_2D, ID);
		for (std::vector<std::pair<GLenum, GLint>>::iterator it = parameters.begin(); it != parameters.end(); ++it)
		{
			glTexParameteri(GL_TEXTURE_2D, (*it).first, (*it).second);
		}
		//glBindTexture(GL_TEXTURE_2D, 0);
	}
	inline GLvoid bind(GLint location)const
	{
		glActiveTexture(level);
		glBindTexture(GL_TEXTURE_2D, ID);
		glUniform1f(location, GLfloat(level - GL_TEXTURE0));
	}
	inline GLvoid bind(GLvoid)const
	{
		glActiveTexture(level);
		glBindTexture(GL_TEXTURE_2D, ID);
	}
	inline static GLvoid resetTexture()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	~Texture2D();
protected:
	GLuint ID;
	GLenum level;
};

