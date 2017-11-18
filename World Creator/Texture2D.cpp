#include "Texture2D.h"

using namespace std;

Texture2D::Texture2D()
{
	ID = 0;
	level = GL_TEXTURE0;
}

Texture2D::Texture2D(const Texture2D & right)
{
	GLint width;
	GLint height;
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	if (!glIsTexture(ID))
	{
#ifdef _DEBUG
		cout << "Texture2D£ºTexture2DÉêÇëÊ§°Ü£¡" << endl;
#endif
		throw runtime_error("Texture2D£ºTexture2DÉêÇëÊ§°Ü£¡");
	}
	right.bind();
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
	level = right.level;

	GLuint fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	if (!glIsFramebuffer(fbo))
	{
		resetTexture();
		throw runtime_error("Texture2D£ºFRAMEBUFFER ÉêÇëÊ§°Ü£¡");
	}
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, right.ID, 0);
	bind();
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	//glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, width, height);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, width, height, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	resetTexture();
}

GLint Texture2D::init(GLenum level)
{
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	if (!glIsTexture(ID))
	{
		return 1;
	}
	this->level = level;
	
	return 0;
}

GLint Texture2D::init(const char * texturePath, GLenum level)
{
	ID = 0;
	GLint width = 0;
	GLint height = 0;
	unsigned char* image = nullptr;
	image = SOIL_load_image(texturePath, &width, &height, 0, SOIL_LOAD_RGBA);
	if (!image)
	{
		cout << "ÎÆÀí³õÊ¼»¯Ê§°Ü£¡£º" << texturePath << endl;
		return 1;
	}
	this->level = level;
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	if (!glIsTexture(ID))
	{
		return 1;
	}
	glActiveTexture(level);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
#ifdef _DEBUG
	cout << "ÎÆÀí£º"<<ID<<" ´´½¨³É¹¦£¡" << endl;
#endif

	return 0;
}

GLvoid Texture2D::init(GLuint textureID, GLenum level)
{
	this->ID = textureID;
	this->level = level;
}

Texture2D & Texture2D::operator = (const Texture2D & right)
{
	GLint width;
	GLint height;
	right.bind();
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
	level = right.level;
	
	GLuint fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D, right.ID, 0);
	bind();
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	//glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, width, height);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, width, height, 0);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//resetTexture();
	return *this;
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &ID);
}
