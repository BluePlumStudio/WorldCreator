#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <iostream>
#include <queue>
#include <vector>

#include "DrawList.h"
#include "Vertex.h"

struct DrawFaces
{
public:
	DrawFaces(GLboolean front = GL_TRUE, GLboolean back = GL_TRUE, GLboolean left = GL_TRUE, GLboolean right = GL_TRUE, GLboolean top = GL_TRUE, GLboolean bottom = GL_TRUE);
	~DrawFaces();

public:
	GLboolean front;
	GLboolean back;
	GLboolean left;
	GLboolean right;
	GLboolean top;
	GLboolean bottom;
};

/*============================================================*/


class Block
{
public:
	Block();
	virtual GLuint getID() = 0;
	virtual const GLchar * getName() = 0;
	virtual GLvoid getDrawData(std::vector<GLfloat> & vertices, DrawFaces & faces, glm::ivec3 & location) = 0;
	virtual ~Block();
public:
protected:
	GLuint ID;
	GLchar * name;
};

/*============================================================*/

/*0：空气*/

class BlockAir :public Block
{
public:
	BlockAir();
	virtual GLuint getID();
	virtual const GLchar * getName();
	virtual GLvoid getDrawData(std::vector<GLfloat> & vertices, DrawFaces & faces, glm::ivec3 & location);
	~BlockAir();

private:

};

/*1：石头*/

class BlockStone :public Block
{
public:
	BlockStone();
	virtual GLuint getID();
	virtual const GLchar * getName();
	virtual GLvoid getDrawData(std::vector<GLfloat> & vertices, DrawFaces & faces, glm::ivec3 & location);
	~BlockStone();

private:

};

/*2：草*/

class BlockGrass :public Block
{
public:
	BlockGrass();
	virtual GLuint getID();
	virtual const GLchar * getName();
	virtual GLvoid getDrawData(std::vector<GLfloat> & vertices, DrawFaces & faces, glm::ivec3 & location);
	~BlockGrass();

private:

};

/*3：泥土*/

class BlockDirt :public Block
{
public:
	BlockDirt();
	virtual GLuint getID();
	virtual const GLchar * getName();
	virtual GLvoid getDrawData(std::vector<GLfloat> & vertices, DrawFaces & faces, glm::ivec3 & location);
	~BlockDirt();

private:

};

/*4：圆石*/

class BlockCobblestone :public Block
{
public:
	BlockCobblestone();
	virtual GLuint getID();
	virtual const GLchar * getName();
	virtual GLvoid getDrawData(std::vector<GLfloat> & vertices, DrawFaces & faces, glm::ivec3 & location);
	~BlockCobblestone();

private:

};
