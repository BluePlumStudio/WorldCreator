#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <GL/glew.h>

inline GLenum errorCheck()
{
	using namespace std;
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		cout << "错误代码：" << error << " ";
		if (error == GL_INVALID_OPERATION)
		{
			cout << "无效操作" << endl;
		}
		if (error == GL_INVALID_ENUM)
		{
			cout << "无效值" << endl;
		}
		cout << endl;
	}
	return error;
}

class StdShaderProgram
{
public:
	StdShaderProgram();
	StdShaderProgram(const StdShaderProgram & right);
	StdShaderProgram & operator=(const StdShaderProgram & right);
	GLint init(const GLchar * vertexShaderPath, const GLchar * fragmentShaderPath);
	GLint init();
	inline GLuint getID()const
	{
		return ID;
	}
	inline GLvoid use()
	{
		glUseProgram(ID);
	}
	static inline GLvoid resetProgram()
	{
		glUseProgram(0);
	}
	static inline GLvoid uniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, GLfloat* value)
	{
		glUniformMatrix4fv(location, count, transpose, value);
	}
	static inline GLvoid uniform1i(GLint location, GLint v0)
	{
		glUniform1i(location, v0);
	}
	static inline GLvoid uniform1d(GLint location, GLdouble x)
	{
		glUniform1d(location, x);
	}
	static inline GLvoid uniform1f(GLint location, GLfloat v0)
	{
		glUniform1f(location, v0);
	}
	static inline GLvoid uniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
	{
		glUniform3f(location, v0, v1, v2);
	}
	static inline GLint getUniformLocation(GLuint program, const GLchar * name)
	{
		return glGetUniformLocation(program, name);
	}
	inline GLint getUniformLocation(const GLchar * name)
	{
		return glGetUniformLocation(ID, name);
	}
	static inline GLint getUniformLocation(const StdShaderProgram & program, const GLchar * name)
	{
		return glGetUniformLocation(program.getID(), name);
	}
	inline GLvoid deleteProgram()
	{
		if (glIsProgram(ID))
		{
			glDeleteProgram(ID);
		}

		if (glIsShader(VSID))
		{
			glDeleteShader(VSID);
		}

		if (glIsShader(FSID))
		{
			glDeleteShader(FSID);
		}
		ID = 0;
		VSID = 0;
		FSID = 0;
	}
	~StdShaderProgram();
private:
	GLuint ID;
	GLuint VSID;
	GLuint FSID;
public:
	std::string vertexShaderPath;
	std::string fragmentShaderPath;
};

