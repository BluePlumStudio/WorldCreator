#include "Block.h"


DrawFaces::DrawFaces(GLboolean front, GLboolean back, GLboolean left, GLboolean right, GLboolean top, GLboolean bottom)
{
	this->front = front;
	this->back = back;
	this->left = left;
	this->right = right;
	this->top = top;
	this->bottom = bottom;
}

DrawFaces::~DrawFaces()
{
}

Block::Block()
{
}

Block::~Block()
{

}

/*============================================================*/

/*0：空气*/

BlockAir::BlockAir()
{
	ID = 0;
	name = "air";
}

GLuint BlockAir::getID()
{
	return ID;
}

const GLchar * BlockAir::getName()
{
	return name;
}

GLvoid BlockAir::getDrawData(std::vector<GLfloat> & vertices, DrawFaces & faces, glm::ivec3 & location)
{
	
}

BlockAir::~BlockAir()
{
}

/*1：石头*/

BlockStone::BlockStone()
{
	ID = 1;
	name = "stone";
}

GLuint BlockStone::getID()
{
	return ID;
}

const GLchar * BlockStone::getName()
{
	return name;
}

GLvoid BlockStone::getDrawData(std::vector<GLfloat> & vertices, DrawFaces & faces, glm::ivec3 & location)
{
	GLuint size = 0;
	if (faces.front)
	{
		size = vertices.size();
		vertices.resize(size + 32);

		vertices[size] = location.x + 1.0f;
		vertices[size + 1] = location.y + 0.0f;
		vertices[size + 2] = location.z + 0.0f;
		vertices[size + 3] = 0.1f;
		vertices[size + 4] = 1.0f;
		vertices[size + 5] = 0.0f;
		vertices[size + 6] = 0.0f;
		vertices[size + 7] = -1.0f;

		vertices[size + 8] = location.x + 0.0f;
		vertices[size + 9] = location.y + 0.0f;
		vertices[size + 10] = location.z + 0.0f;
		vertices[size + 11] = 0.2f;
		vertices[size + 12] = 1.0f;
		vertices[size + 13] = 0.0f;
		vertices[size + 14] = 0.0f;
		vertices[size + 15] = -1.0f;

		vertices[size + 16] = location.x + 0.0f;
		vertices[size + 17] = location.y + 1.0f;
		vertices[size + 18] = location.z + 0.0f;
		vertices[size + 19] = 0.2f;
		vertices[size + 20] = 0.9f;
		vertices[size + 21] = 0.0f;
		vertices[size + 22] = 0.0f;
		vertices[size + 23] = -1.0f;

		vertices[size + 24] = location.x + 1.0f;
		vertices[size + 25] = location.y + 1.0f;
		vertices[size + 26] = location.z + 0.0f;
		vertices[size + 27] = 0.1f;
		vertices[size + 28] = 0.9f;
		vertices[size + 29] = 0.0f;
		vertices[size + 30] = 0.0f;
		vertices[size + 31] = -1.0f;

		/*
		size = vertices.size();
		vertices.resize(size + 20);

		vertices[size] = location.x + 1.0f;
		vertices[size + 1] = location.y + 0.0f;
		vertices[size + 2] = location.z + 0.0f;
		vertices[size + 3] = 0.1f;
		vertices[size + 4] = 1.0f;

		vertices[size + 5] = location.x + 0.0f;
		vertices[size + 6] = location.y + 0.0f;
		vertices[size + 7] = location.z + 0.0f;
		vertices[size + 8] = 0.2f;
		vertices[size + 9] = 1.0f;

		vertices[size + 10] = location.x + 0.0f;
		vertices[size + 11] = location.y + 1.0f;
		vertices[size + 12] = location.z + 0.0f;
		vertices[size + 13] = 0.2f;
		vertices[size + 14] = 0.9f;

		vertices[size + 15] = location.x + 1.0f;
		vertices[size + 16] = location.y + 1.0f;
		vertices[size + 17] = location.z + 0.0f;
		vertices[size + 18] = 0.1f;
		vertices[size + 19] = 0.9f;
		*/
	}
	if (faces.back)
	{
		size = vertices.size();
		vertices.resize(size + 32);

		vertices[size] = location.x + 0.0f;
		vertices[size + 1] = location.y + 0.0f;
		vertices[size + 2] = location.z + 1.0f;
		vertices[size + 3] = 0.1f;
		vertices[size + 4] = 1.0f;
		vertices[size + 5] = 0.0f;
		vertices[size + 6] = 0.0f;
		vertices[size + 7] = 1.0f;

		vertices[size + 8] = location.x + 1.0f;
		vertices[size + 9] = location.y + 0.0f;
		vertices[size + 10] = location.z + 1.0f;
		vertices[size + 11] = 0.2f;
		vertices[size + 12] = 1.0f;
		vertices[size + 13] = 0.0f;
		vertices[size + 14] = 0.0f;
		vertices[size + 15] = 1.0f;

		vertices[size + 16] = location.x + 1.0f;
		vertices[size + 17] = location.y + 1.0f;
		vertices[size + 18] = location.z + 1.0f;
		vertices[size + 19] = 0.2f;
		vertices[size + 20] = 0.9f;
		vertices[size + 21] = 0.0f;
		vertices[size + 22] = 0.0f;
		vertices[size + 23] = 1.0f;

		vertices[size + 24] = location.x + 0.0f;
		vertices[size + 25] = location.y + 1.0f;
		vertices[size + 26] = location.z + 1.0f;
		vertices[size + 27] = 0.1f;
		vertices[size + 28] = 0.9f;
		vertices[size + 29] = 0.0f;
		vertices[size + 30] = 0.0f;
		vertices[size + 31] = 1.0f;
		/*
		size = vertices.size();
		vertices.resize(size + 20);

		vertices[size] = location.x + 0.0f;
		vertices[size + 1] = location.y + 0.0f;
		vertices[size + 2] = location.z + 1.0f;
		vertices[size + 3] = 0.1f;
		vertices[size + 4] = 1.0f;

		vertices[size + 5] = location.x + 1.0f;
		vertices[size + 6] = location.y + 0.0f;
		vertices[size + 7] = location.z + 1.0f;
		vertices[size + 8] = 0.2f;
		vertices[size + 9] = 1.0f;

		vertices[size + 10] = location.x + 1.0f;
		vertices[size + 11] = location.y + 1.0f;
		vertices[size + 12] = location.z + 1.0f;
		vertices[size + 13] = 0.2f;
		vertices[size + 14] = 0.9f;

		vertices[size + 15] = location.x + 0.0f;
		vertices[size + 16] = location.y + 1.0f;
		vertices[size + 17] = location.z + 1.0f;
		vertices[size + 18] = 0.1f;
		vertices[size + 19] = 0.9f;
		*/
	}
	if (faces.left)
	{
		size = vertices.size();
		vertices.resize(size + 32);

		vertices[size] = location.x + 0.0f;
		vertices[size + 1] = location.y + 0.0f;
		vertices[size + 2] = location.z + 0.0f;
		vertices[size + 3] = 0.1f;
		vertices[size + 4] = 1.0f;
		vertices[size + 5] = -1.0f;
		vertices[size + 6] = 0.0f;
		vertices[size + 7] = 0.0f;

		vertices[size + 8] = location.x + 0.0f;
		vertices[size + 9] = location.y + 0.0f;
		vertices[size + 10] = location.z + 1.0f;
		vertices[size + 11] = 0.2f;
		vertices[size + 12] = 1.0f;
		vertices[size + 13] = -1.0f;
		vertices[size + 14] = 0.0f;
		vertices[size + 15] = 0.0f;

		vertices[size + 16] = location.x + 0.0f;
		vertices[size + 17] = location.y + 1.0f;
		vertices[size + 18] = location.z + 1.0f;
		vertices[size + 19] = 0.2f;
		vertices[size + 20] = 0.9f;
		vertices[size + 21] = -1.0f;
		vertices[size + 22] = 0.0f;
		vertices[size + 23] = 0.0f;

		vertices[size + 24] = location.x + 0.0f;
		vertices[size + 25] = location.y + 1.0f;
		vertices[size + 26] = location.z + 0.0f;
		vertices[size + 27] = 0.1f;
		vertices[size + 28] = 0.9f;
		vertices[size + 29] = -1.0f;
		vertices[size + 30] = 0.0f;
		vertices[size + 31] = 0.0f;

		/*
		size = vertices.size();
		vertices.resize(size + 20);

		vertices[size] = location.x + 0.0f;
		vertices[size + 1] = location.y + 0.0f;
		vertices[size + 2] = location.z + 0.0f;
		vertices[size + 3] = 0.1f;
		vertices[size + 4] = 1.0f;

		vertices[size + 5] = location.x + 0.0f;
		vertices[size + 6] = location.y + 0.0f;
		vertices[size + 7] = location.z + 1.0f;
		vertices[size + 8] = 0.2f;
		vertices[size + 9] = 1.0f;

		vertices[size + 10] = location.x + 0.0f;
		vertices[size + 11] = location.y + 1.0f;
		vertices[size + 12] = location.z + 1.0f;
		vertices[size + 13] = 0.2f;
		vertices[size + 14] = 0.9f;

		vertices[size + 15] = location.x + 0.0f;
		vertices[size + 16] = location.y + 1.0f;
		vertices[size + 17] = location.z + 0.0f;
		vertices[size + 18] = 0.1f;
		vertices[size + 19] = 0.9f;
		*/
	}
	if (faces.right)
	{
		size = vertices.size();
		vertices.resize(size + 32);

		vertices[size] = location.x + 1.0f;
		vertices[size + 1] = location.y + 0.0f;
		vertices[size + 2] = location.z + 1.0f;
		vertices[size + 3] = 0.1f;
		vertices[size + 4] = 1.0f;
		vertices[size + 5] = 1.0f;
		vertices[size + 6] = 0.0f;
		vertices[size + 7] = 0.0f;

		vertices[size + 8] = location.x + 1.0f;
		vertices[size + 9] = location.y + 0.0f;
		vertices[size + 10] = location.z + 0.0f;
		vertices[size + 11] = 0.2f;
		vertices[size + 12] = 1.0f;
		vertices[size + 13] = 1.0f;
		vertices[size + 14] = 0.0f;
		vertices[size + 15] = 0.0f;

		vertices[size + 16] = location.x + 1.0f;
		vertices[size + 17] = location.y + 1.0f;
		vertices[size + 18] = location.z + 0.0f;
		vertices[size + 19] = 0.2f;
		vertices[size + 20] = 0.9f;
		vertices[size + 21] = 1.0f;
		vertices[size + 22] = 0.0f;
		vertices[size + 23] = 0.0f;

		vertices[size + 24] = location.x + 1.0f;
		vertices[size + 25] = location.y + 1.0f;
		vertices[size + 26] = location.z + 1.0f;
		vertices[size + 27] = 0.1f;
		vertices[size + 28] = 0.9f;
		vertices[size + 29] = 1.0f;
		vertices[size + 30] = 0.0f;
		vertices[size + 31] = 0.0f;

		/*
		size = vertices.size();
		vertices.resize(size + 20);

		vertices[size] = location.x + 1.0f;
		vertices[size + 1] = location.y + 0.0f;
		vertices[size + 2] = location.z + 1.0f;
		vertices[size + 3] = 0.1f;
		vertices[size + 4] = 1.0f;

		vertices[size + 5] = location.x + 1.0f;
		vertices[size + 6] = location.y + 0.0f;
		vertices[size + 7] = location.z + 0.0f;
		vertices[size + 8] = 0.2f;
		vertices[size + 9] = 1.0f;

		vertices[size + 10] = location.x + 1.0f;
		vertices[size + 11] = location.y + 1.0f;
		vertices[size + 12] = location.z + 0.0f;
		vertices[size + 13] = 0.2f;
		vertices[size + 14] = 0.9f;

		vertices[size + 15] = location.x + 1.0f;
		vertices[size + 16] = location.y + 1.0f;
		vertices[size + 17] = location.z + 1.0f;
		vertices[size + 18] = 0.1f;
		vertices[size + 19] = 0.9f;
		*/
	}
	if (faces.top)
	{
		size = vertices.size();
		vertices.resize(size + 32);

		vertices[size] = location.x + 0.0f;
		vertices[size + 1] = location.y + 1.0f;
		vertices[size + 2] = location.z + 1.0f;
		vertices[size + 3] = 0.1f;
		vertices[size + 4] = 1.0f;
		vertices[size + 5] = 0.0f;
		vertices[size + 6] = 1.0f;
		vertices[size + 7] = 0.0f;

		vertices[size + 8] = location.x + 1.0f;
		vertices[size + 9] = location.y + 1.0f;
		vertices[size + 10] = location.z + 1.0f;
		vertices[size + 11] = 0.2f;
		vertices[size + 12] = 1.0f;
		vertices[size + 13] = 0.0f;
		vertices[size + 14] = 1.0f;
		vertices[size + 15] = 0.0f;

		vertices[size + 16] = location.x + 1.0f;
		vertices[size + 17] = location.y + 1.0f;
		vertices[size + 18] = location.z + 0.0f;
		vertices[size + 19] = 0.2f;
		vertices[size + 20] = 0.9f;
		vertices[size + 21] = 0.0f;
		vertices[size + 22] = 1.0f;
		vertices[size + 23] = 0.0f;

		vertices[size + 24] = location.x + 0.0f;
		vertices[size + 25] = location.y + 1.0f;
		vertices[size + 26] = location.z + 0.0f;
		vertices[size + 27] = 0.1f;
		vertices[size + 28] = 0.9f;
		vertices[size + 29] = 0.0f;
		vertices[size + 30] = 1.0f;
		vertices[size + 31] = 0.0f;

		/*
		size = vertices.size();
		vertices.resize(size + 20);

		vertices[size] = location.x + 0.0f;
		vertices[size + 1] = location.y + 1.0f;
		vertices[size + 2] = location.z + 1.0f;
		vertices[size + 3] = 0.1f;
		vertices[size + 4] = 1.0f;

		vertices[size + 5] = location.x + 1.0f;
		vertices[size + 6] = location.y + 1.0f;
		vertices[size + 7] = location.z + 1.0f;
		vertices[size + 8] = 0.2f;
		vertices[size + 9] = 1.0f;

		vertices[size + 10] = location.x + 1.0f;
		vertices[size + 11] = location.y + 1.0f;
		vertices[size + 12] = location.z + 0.0f;
		vertices[size + 13] = 0.2f;
		vertices[size + 14] = 0.9f;

		vertices[size + 15] = location.x + 0.0f;
		vertices[size + 16] = location.y + 1.0f;
		vertices[size + 17] = location.z + 0.0f;
		vertices[size + 18] = 0.1f;
		vertices[size + 19] = 0.9f;
		*/
	}
	if (faces.bottom)
	{
		size = vertices.size();
		vertices.resize(size + 32);

		vertices[size] = location.x + 0.0f;
		vertices[size + 1] = location.y + 0.0f;
		vertices[size + 2] = location.z + 0.0f;
		vertices[size + 3] = 0.1f;
		vertices[size + 4] = 1.0f;
		vertices[size + 5] = 0.0f;
		vertices[size + 6] = -1.0f;
		vertices[size + 7] = 0.0f;

		vertices[size + 8] = location.x + 1.0f;
		vertices[size + 9] = location.y + 0.0f;
		vertices[size + 10] = location.z + 0.0f;
		vertices[size + 11] = 0.2f;
		vertices[size + 12] = 1.0f;
		vertices[size + 13] = 0.0f;
		vertices[size + 14] = -1.0f;
		vertices[size + 15] = 0.0f;

		vertices[size + 16] = location.x + 1.0f;
		vertices[size + 17] = location.y + 0.0f;
		vertices[size + 18] = location.z + 1.0f;
		vertices[size + 19] = 0.2f;
		vertices[size + 20] = 0.9f;
		vertices[size + 21] = 0.0f;
		vertices[size + 22] = -1.0f;
		vertices[size + 23] = 0.0f;

		vertices[size + 24] = location.x + 0.0f;
		vertices[size + 25] = location.y + 0.0f;
		vertices[size + 26] = location.z + 1.0f;
		vertices[size + 27] = 0.1f;
		vertices[size + 28] = 0.9f;
		vertices[size + 29] = 0.0f;
		vertices[size + 30] = -1.0f;
		vertices[size + 31] = 0.0f;

		/*
		size = vertices.size();
		vertices.resize(size + 20);

		vertices[size] = location.x + 0.0f;
		vertices[size + 1] = location.y + 0.0f;
		vertices[size + 2] = location.z + 0.0f;
		vertices[size + 3] = 0.1f;
		vertices[size + 4] = 1.0f;

		vertices[size + 5] = location.x + 1.0f;
		vertices[size + 6] = location.y + 0.0f;
		vertices[size + 7] = location.z + 0.0f;
		vertices[size + 8] = 0.2f;
		vertices[size + 9] = 1.0f;

		vertices[size + 10] = location.x + 1.0f;
		vertices[size + 11] = location.y + 0.0f;
		vertices[size + 12] = location.z + 1.0f;
		vertices[size + 13] = 0.2f;
		vertices[size + 14] = 0.9f;

		vertices[size + 15] = location.x + 0.0f;
		vertices[size + 16] = location.y + 0.0f;
		vertices[size + 17] = location.z + 1.0f;
		vertices[size + 18] = 0.1f;
		vertices[size + 19] = 0.9f;
		*/
	}
}

BlockStone::~BlockStone()
{
}

/*2：草*/

BlockGrass::BlockGrass()
{
	ID = 2;
	name = "grass";
}

GLuint BlockGrass::getID()
{
	return ID;
}

const GLchar * BlockGrass::getName()
{
	return name;
}

GLvoid BlockGrass::getDrawData(std::vector<GLfloat> & vertices, DrawFaces & faces, glm::ivec3 & location)
{
	GLuint size = 0;
	if (faces.front)
	{
		size = vertices.size();
		vertices.resize(size + 32);

		vertices[size] = location.x + 1.0f;
		vertices[size + 1] = location.y + 0.0f;
		vertices[size + 2] = location.z + 0.0f;
		vertices[size + 3] = 0.2f;
		vertices[size + 4] = 1.0f;
		vertices[size + 5] = 0.0f;
		vertices[size + 6] = 0.0f;
		vertices[size + 7] = -1.0f;

		vertices[size + 8] = location.x + 0.0f;
		vertices[size + 9] = location.y + 0.0f;
		vertices[size + 10] = location.z + 0.0f;
		vertices[size + 11] = 0.3f;
		vertices[size + 12] = 1.0f;
		vertices[size + 13] = 0.0f;
		vertices[size + 14] = 0.0f;
		vertices[size + 15] = -1.0f;

		vertices[size + 16] = location.x + 0.0f;
		vertices[size + 17] = location.y + 1.0f;
		vertices[size + 18] = location.z + 0.0f;
		vertices[size + 19] = 0.3f;
		vertices[size + 20] = 0.9f;
		vertices[size + 21] = 0.0f;
		vertices[size + 22] = 0.0f;
		vertices[size + 23] = -1.0f;

		vertices[size + 24] = location.x + 1.0f;
		vertices[size + 25] = location.y + 1.0f;
		vertices[size + 26] = location.z + 0.0f;
		vertices[size + 27] = 0.2f;
		vertices[size + 28] = 0.9f;
		vertices[size + 29] = 0.0f;
		vertices[size + 30] = 0.0f;
		vertices[size + 31] = -1.0f;
	}
	if (faces.back)
	{
		size = vertices.size();
		vertices.resize(size + 32);

		vertices[size] = location.x + 0.0f;
		vertices[size + 1] = location.y + 0.0f;
		vertices[size + 2] = location.z + 1.0f;
		vertices[size + 3] = 0.2f;
		vertices[size + 4] = 1.0f;
		vertices[size + 5] = 0.0f;
		vertices[size + 6] = 0.0f;
		vertices[size + 7] = 1.0f;

		vertices[size + 8] = location.x + 1.0f;
		vertices[size + 9] = location.y + 0.0f;
		vertices[size + 10] = location.z + 1.0f;
		vertices[size + 11] = 0.3f;
		vertices[size + 12] = 1.0f;
		vertices[size + 13] = 0.0f;
		vertices[size + 14] = 0.0f;
		vertices[size + 15] = 1.0f;

		vertices[size + 16] = location.x + 1.0f;
		vertices[size + 17] = location.y + 1.0f;
		vertices[size + 18] = location.z + 1.0f;
		vertices[size + 19] = 0.3f;
		vertices[size + 20] = 0.9f;
		vertices[size + 21] = 0.0f;
		vertices[size + 22] = 0.0f;
		vertices[size + 23] = 1.0f;

		vertices[size + 24] = location.x + 0.0f;
		vertices[size + 25] = location.y + 1.0f;
		vertices[size + 26] = location.z + 1.0f;
		vertices[size + 27] = 0.2f;
		vertices[size + 28] = 0.9f;
		vertices[size + 29] = 0.0f;
		vertices[size + 30] = 0.0f;
		vertices[size + 31] = 1.0f;
	}
	if (faces.left)
	{
		size = vertices.size();
		vertices.resize(size + 32);

		vertices[size] = location.x + 0.0f;
		vertices[size + 1] = location.y + 0.0f;
		vertices[size + 2] = location.z + 0.0f;
		vertices[size + 3] = 0.2f;
		vertices[size + 4] = 1.0f;
		vertices[size + 5] = -1.0f;
		vertices[size + 6] = 0.0f;
		vertices[size + 7] = 0.0f;

		vertices[size + 8] = location.x + 0.0f;
		vertices[size + 9] = location.y + 0.0f;
		vertices[size + 10] = location.z + 1.0f;
		vertices[size + 11] = 0.3f;
		vertices[size + 12] = 1.0f;
		vertices[size + 13] = -1.0f;
		vertices[size + 14] = 0.0f;
		vertices[size + 15] = 0.0f;

		vertices[size + 16] = location.x + 0.0f;
		vertices[size + 17] = location.y + 1.0f;
		vertices[size + 18] = location.z + 1.0f;
		vertices[size + 19] = 0.3f;
		vertices[size + 20] = 0.9f;
		vertices[size + 21] = -1.0f;
		vertices[size + 22] = 0.0f;
		vertices[size + 23] = 0.0f;

		vertices[size + 24] = location.x + 0.0f;
		vertices[size + 25] = location.y + 1.0f;
		vertices[size + 26] = location.z + 0.0f;
		vertices[size + 27] = 0.2f;
		vertices[size + 28] = 0.9f;
		vertices[size + 29] = -1.0f;
		vertices[size + 30] = 0.0f;
		vertices[size + 31] = 0.0f;
	}
	if (faces.right)
	{

		size = vertices.size();
		vertices.resize(size + 32);

		vertices[size] = location.x + 1.0f;
		vertices[size + 1] = location.y + 0.0f;
		vertices[size + 2] = location.z + 1.0f;
		vertices[size + 3] = 0.2f;
		vertices[size + 4] = 1.0f;
		vertices[size + 5] = 1.0f;
		vertices[size + 6] = 0.0f;
		vertices[size + 7] = 0.0f;

		vertices[size + 8] = location.x + 1.0f;
		vertices[size + 9] = location.y + 0.0f;
		vertices[size + 10] = location.z + 0.0f;
		vertices[size + 11] = 0.3f;
		vertices[size + 12] = 1.0f;
		vertices[size + 13] = 1.0f;
		vertices[size + 14] = 0.0f;
		vertices[size + 15] = 0.0f;

		vertices[size + 16] = location.x + 1.0f;
		vertices[size + 17] = location.y + 1.0f;
		vertices[size + 18] = location.z + 0.0f;
		vertices[size + 19] = 0.3f;
		vertices[size + 20] = 0.9f;
		vertices[size + 21] = 1.0f;
		vertices[size + 22] = 0.0f;
		vertices[size + 23] = 0.0f;

		vertices[size + 24] = location.x + 1.0f;
		vertices[size + 25] = location.y + 1.0f;
		vertices[size + 26] = location.z + 1.0f;
		vertices[size + 27] = 0.2f;
		vertices[size + 28] = 0.9f;
		vertices[size + 29] = 1.0f;
		vertices[size + 30] = 0.0f;
		vertices[size + 31] = 0.0f;
	}
	if (faces.top)
	{
		size = vertices.size();
		vertices.resize(size + 32);

		vertices[size] = location.x + 0.0f;
		vertices[size + 1] = location.y + 1.0f;
		vertices[size + 2] = location.z + 1.0f;
		vertices[size + 3] = 0.3f;
		vertices[size + 4] = 1.0f;
		vertices[size + 5] = 0.0f;
		vertices[size + 6] = 1.0f;
		vertices[size + 7] = 0.0f;

		vertices[size + 8] = location.x + 1.0f;
		vertices[size + 9] = location.y + 1.0f;
		vertices[size + 10] = location.z + 1.0f;
		vertices[size + 11] = 0.4f;
		vertices[size + 12] = 1.0f;
		vertices[size + 13] = 0.0f;
		vertices[size + 14] = 1.0f;
		vertices[size + 15] = 0.0f;

		vertices[size + 16] = location.x + 1.0f;
		vertices[size + 17] = location.y + 1.0f;
		vertices[size + 18] = location.z + 0.0f;
		vertices[size + 19] = 0.4f;
		vertices[size + 20] = 0.9f;
		vertices[size + 21] = 0.0f;
		vertices[size + 22] = 1.0f;
		vertices[size + 23] = 0.0f;

		vertices[size + 24] = location.x + 0.0f;
		vertices[size + 25] = location.y + 1.0f;
		vertices[size + 26] = location.z + 0.0f;
		vertices[size + 27] = 0.3f;
		vertices[size + 28] = 0.9f;
		vertices[size + 29] = 0.0f;
		vertices[size + 30] = 1.0f;
		vertices[size + 31] = 0.0f;

	}
	if (faces.bottom)
	{
		size = vertices.size();
		vertices.resize(size + 32);

		vertices[size] = location.x + 0.0f;
		vertices[size + 1] = location.y + 0.0f;
		vertices[size + 2] = location.z + 0.0f;
		vertices[size + 3] = 0.4f;
		vertices[size + 4] = 1.0f;
		vertices[size + 5] = 0.0f;
		vertices[size + 6] = -1.0f;
		vertices[size + 7] = 0.0f;

		vertices[size + 8] = location.x + 1.0f;
		vertices[size + 9] = location.y + 0.0f;
		vertices[size + 10] = location.z + 0.0f;
		vertices[size + 11] = 0.5f;
		vertices[size + 12] = 1.0f;
		vertices[size + 13] = 0.0f;
		vertices[size + 14] = -1.0f;
		vertices[size + 15] = 0.0f;

		vertices[size + 16] = location.x + 1.0f;
		vertices[size + 17] = location.y + 0.0f;
		vertices[size + 18] = location.z + 1.0f;
		vertices[size + 19] = 0.5f;
		vertices[size + 20] = 0.9f;
		vertices[size + 21] = 0.0f;
		vertices[size + 22] = -1.0f;
		vertices[size + 23] = 0.0f;

		vertices[size + 24] = location.x + 0.0f;
		vertices[size + 25] = location.y + 0.0f;
		vertices[size + 26] = location.z + 1.0f;
		vertices[size + 27] = 0.4f;
		vertices[size + 28] = 0.9f;
		vertices[size + 29] = 0.0f;
		vertices[size + 30] = -1.0f;
		vertices[size + 31] = 0.0f;


	}
}

BlockGrass::~BlockGrass()
{
}

/*3：泥土*/

BlockDirt::BlockDirt()
{
	ID = 3;
	name = "dirt";
}

GLuint BlockDirt::getID()
{
	return ID;
}

const GLchar * BlockDirt::getName()
{
	return name;
}

GLvoid BlockDirt::getDrawData(std::vector<GLfloat> & vertices, DrawFaces & faces, glm::ivec3 & location)
{
	GLuint size = 0;
	if (faces.front)
	{
		size = vertices.size();
		vertices.resize(size + 32);

		vertices[size] = location.x + 1.0f;
		vertices[size + 1] = location.y + 0.0f;
		vertices[size + 2] = location.z + 0.0f;
		vertices[size + 3] = 0.4f;
		vertices[size + 4] = 1.0f;
		vertices[size + 5] = 0.0f;
		vertices[size + 6] = 0.0f;
		vertices[size + 7] = -1.0f;

		vertices[size + 8] = location.x + 0.0f;
		vertices[size + 9] = location.y + 0.0f;
		vertices[size + 10] = location.z + 0.0f;
		vertices[size + 11] = 0.5f;
		vertices[size + 12] = 1.0f;
		vertices[size + 13] = 0.0f;
		vertices[size + 14] = 0.0f;
		vertices[size + 15] = -1.0f;

		vertices[size + 16] = location.x + 0.0f;
		vertices[size + 17] = location.y + 1.0f;
		vertices[size + 18] = location.z + 0.0f;
		vertices[size + 19] = 0.5f;
		vertices[size + 20] = 0.9f;
		vertices[size + 21] = 0.0f;
		vertices[size + 22] = 0.0f;
		vertices[size + 23] = -1.0f;

		vertices[size + 24] = location.x + 1.0f;
		vertices[size + 25] = location.y + 1.0f;
		vertices[size + 26] = location.z + 0.0f;
		vertices[size + 27] = 0.4f;
		vertices[size + 28] = 0.9f;
		vertices[size + 29] = 0.0f;
		vertices[size + 30] = 0.0f;
		vertices[size + 31] = -1.0f;
	}
	if (faces.back)
	{
		size = vertices.size();
		vertices.resize(size + 32);

		vertices[size] = location.x + 0.0f;
		vertices[size + 1] = location.y + 0.0f;
		vertices[size + 2] = location.z + 1.0f;
		vertices[size + 3] = 0.4f;
		vertices[size + 4] = 1.0f;
		vertices[size + 5] = 0.0f;
		vertices[size + 6] = 0.0f;
		vertices[size + 7] = 1.0f;

		vertices[size + 8] = location.x + 1.0f;
		vertices[size + 9] = location.y + 0.0f;
		vertices[size + 10] = location.z + 1.0f;
		vertices[size + 11] = 0.5f;
		vertices[size + 12] = 1.0f;
		vertices[size + 13] = 0.0f;
		vertices[size + 14] = 0.0f;
		vertices[size + 15] = 1.0f;

		vertices[size + 16] = location.x + 1.0f;
		vertices[size + 17] = location.y + 1.0f;
		vertices[size + 18] = location.z + 1.0f;
		vertices[size + 19] = 0.5f;
		vertices[size + 20] = 0.9f;
		vertices[size + 21] = 0.0f;
		vertices[size + 22] = 0.0f;
		vertices[size + 23] = 1.0f;

		vertices[size + 24] = location.x + 0.0f;
		vertices[size + 25] = location.y + 1.0f;
		vertices[size + 26] = location.z + 1.0f;
		vertices[size + 27] = 0.4f;
		vertices[size + 28] = 0.9f;
		vertices[size + 29] = 0.0f;
		vertices[size + 30] = 0.0f;
		vertices[size + 31] = 1.0f;
	}
	if (faces.left)
	{
		size = vertices.size();
		vertices.resize(size + 32);

		vertices[size] = location.x + 0.0f;
		vertices[size + 1] = location.y + 0.0f;
		vertices[size + 2] = location.z + 0.0f;
		vertices[size + 3] = 0.4f;
		vertices[size + 4] = 1.0f;
		vertices[size + 5] = -1.0f;
		vertices[size + 6] = 0.0f;
		vertices[size + 7] = 0.0f;

		vertices[size + 8] = location.x + 0.0f;
		vertices[size + 9] = location.y + 0.0f;
		vertices[size + 10] = location.z + 1.0f;
		vertices[size + 11] = 0.5f;
		vertices[size + 12] = 1.0f;
		vertices[size + 13] = -1.0f;
		vertices[size + 14] = 0.0f;
		vertices[size + 15] = 0.0f;

		vertices[size + 16] = location.x + 0.0f;
		vertices[size + 17] = location.y + 1.0f;
		vertices[size + 18] = location.z + 1.0f;
		vertices[size + 19] = 0.5f;
		vertices[size + 20] = 0.9f;
		vertices[size + 21] = -1.0f;
		vertices[size + 22] = 0.0f;
		vertices[size + 23] = 0.0f;

		vertices[size + 24] = location.x + 0.0f;
		vertices[size + 25] = location.y + 1.0f;
		vertices[size + 26] = location.z + 0.0f;
		vertices[size + 27] = 0.4f;
		vertices[size + 28] = 0.9f;
		vertices[size + 29] = -1.0f;
		vertices[size + 30] = 0.0f;
		vertices[size + 31] = 0.0f;
	}
	if (faces.right)
	{

		size = vertices.size();
		vertices.resize(size + 32);

		vertices[size] = location.x + 1.0f;
		vertices[size + 1] = location.y + 0.0f;
		vertices[size + 2] = location.z + 1.0f;
		vertices[size + 3] = 0.4f;
		vertices[size + 4] = 1.0f;
		vertices[size + 5] = 1.0f;
		vertices[size + 6] = 0.0f;
		vertices[size + 7] = 0.0f;

		vertices[size + 8] = location.x + 1.0f;
		vertices[size + 9] = location.y + 0.0f;
		vertices[size + 10] = location.z + 0.0f;
		vertices[size + 11] = 0.5f;
		vertices[size + 12] = 1.0f;
		vertices[size + 13] = 1.0f;
		vertices[size + 14] = 0.0f;
		vertices[size + 15] = 0.0f;

		vertices[size + 16] = location.x + 1.0f;
		vertices[size + 17] = location.y + 1.0f;
		vertices[size + 18] = location.z + 0.0f;
		vertices[size + 19] = 0.5f;
		vertices[size + 20] = 0.9f;
		vertices[size + 21] = 1.0f;
		vertices[size + 22] = 0.0f;
		vertices[size + 23] = 0.0f;

		vertices[size + 24] = location.x + 1.0f;
		vertices[size + 25] = location.y + 1.0f;
		vertices[size + 26] = location.z + 1.0f;
		vertices[size + 27] = 0.4f;
		vertices[size + 28] = 0.9f;
		vertices[size + 29] = 1.0f;
		vertices[size + 30] = 0.0f;
		vertices[size + 31] = 0.0f;
	}
	if (faces.top)
	{
		size = vertices.size();
		vertices.resize(size + 32);

		vertices[size] = location.x + 0.0f;
		vertices[size + 1] = location.y + 1.0f;
		vertices[size + 2] = location.z + 1.0f;
		vertices[size + 3] = 0.4f;
		vertices[size + 4] = 1.0f;
		vertices[size + 5] = 0.0f;
		vertices[size + 6] = 1.0f;
		vertices[size + 7] = 0.0f;

		vertices[size + 8] = location.x + 1.0f;
		vertices[size + 9] = location.y + 1.0f;
		vertices[size + 10] = location.z + 1.0f;
		vertices[size + 11] = 0.5f;
		vertices[size + 12] = 1.0f;
		vertices[size + 13] = 0.0f;
		vertices[size + 14] = 1.0f;
		vertices[size + 15] = 0.0f;

		vertices[size + 16] = location.x + 1.0f;
		vertices[size + 17] = location.y + 1.0f;
		vertices[size + 18] = location.z + 0.0f;
		vertices[size + 19] = 0.5f;
		vertices[size + 20] = 0.9f;
		vertices[size + 21] = 0.0f;
		vertices[size + 22] = 1.0f;
		vertices[size + 23] = 0.0f;

		vertices[size + 24] = location.x + 0.0f;
		vertices[size + 25] = location.y + 1.0f;
		vertices[size + 26] = location.z + 0.0f;
		vertices[size + 27] = 0.4f;
		vertices[size + 28] = 0.9f;
		vertices[size + 29] = 0.0f;
		vertices[size + 30] = 1.0f;
		vertices[size + 31] = 0.0f;

	}
	if (faces.bottom)
	{
		size = vertices.size();
		vertices.resize(size + 32);

		vertices[size] = location.x + 0.0f;
		vertices[size + 1] = location.y + 0.0f;
		vertices[size + 2] = location.z + 0.0f;
		vertices[size + 3] = 0.4f;
		vertices[size + 4] = 1.0f;
		vertices[size + 5] = 0.0f;
		vertices[size + 6] = -1.0f;
		vertices[size + 7] = 0.0f;

		vertices[size + 8] = location.x + 1.0f;
		vertices[size + 9] = location.y + 0.0f;
		vertices[size + 10] = location.z + 0.0f;
		vertices[size + 11] = 0.5f;
		vertices[size + 12] = 1.0f;
		vertices[size + 13] = 0.0f;
		vertices[size + 14] = -1.0f;
		vertices[size + 15] = 0.0f;

		vertices[size + 16] = location.x + 1.0f;
		vertices[size + 17] = location.y + 0.0f;
		vertices[size + 18] = location.z + 1.0f;
		vertices[size + 19] = 0.5f;
		vertices[size + 20] = 0.9f;
		vertices[size + 21] = 0.0f;
		vertices[size + 22] = -1.0f;
		vertices[size + 23] = 0.0f;

		vertices[size + 24] = location.x + 0.0f;
		vertices[size + 25] = location.y + 0.0f;
		vertices[size + 26] = location.z + 1.0f;
		vertices[size + 27] = 0.4f;
		vertices[size + 28] = 0.9f;
		vertices[size + 29] = 0.0f;
		vertices[size + 30] = -1.0f;
		vertices[size + 31] = 0.0f;
	}

}

BlockDirt::~BlockDirt()
{

}

/*4：圆石*/

BlockCobblestone::BlockCobblestone()
{
	ID = 4;
	name = "cobblestone";
}

GLuint BlockCobblestone::getID()
{
	return ID;
}

const GLchar * BlockCobblestone::getName()
{
	return name;
}

GLvoid BlockCobblestone::getDrawData(std::vector<GLfloat> & vertices, DrawFaces & faces, glm::ivec3 & location)
{
	GLuint size = 0;
	if (faces.front)
	{
		size = vertices.size();
		vertices.resize(size + 32);

		vertices[size] = location.x + 1.0f;
		vertices[size + 1] = location.y + 0.0f;
		vertices[size + 2] = location.z + 0.0f;
		vertices[size + 3] = 0.5f;
		vertices[size + 4] = 1.0f;
		vertices[size + 5] = 0.0f;
		vertices[size + 6] = 0.0f;
		vertices[size + 7] = -1.0f;

		vertices[size + 8] = location.x + 0.0f;
		vertices[size + 9] = location.y + 0.0f;
		vertices[size + 10] = location.z + 0.0f;
		vertices[size + 11] = 0.6f;
		vertices[size + 12] = 1.0f;
		vertices[size + 13] = 0.0f;
		vertices[size + 14] = 0.0f;
		vertices[size + 15] = -1.0f;

		vertices[size + 16] = location.x + 0.0f;
		vertices[size + 17] = location.y + 1.0f;
		vertices[size + 18] = location.z + 0.0f;
		vertices[size + 19] = 0.6f;
		vertices[size + 20] = 0.9f;
		vertices[size + 21] = 0.0f;
		vertices[size + 22] = 0.0f;
		vertices[size + 23] = -1.0f;

		vertices[size + 24] = location.x + 1.0f;
		vertices[size + 25] = location.y + 1.0f;
		vertices[size + 26] = location.z + 0.0f;
		vertices[size + 27] = 0.5f;
		vertices[size + 28] = 0.9f;
		vertices[size + 29] = 0.0f;
		vertices[size + 30] = 0.0f;
		vertices[size + 31] = -1.0f;
	}
	if (faces.back)
	{
		size = vertices.size();
		vertices.resize(size + 32);

		vertices[size] = location.x + 0.0f;
		vertices[size + 1] = location.y + 0.0f;
		vertices[size + 2] = location.z + 1.0f;
		vertices[size + 3] = 0.5f;
		vertices[size + 4] = 1.0f;
		vertices[size + 5] = 0.0f;
		vertices[size + 6] = 0.0f;
		vertices[size + 7] = 1.0f;

		vertices[size + 8] = location.x + 1.0f;
		vertices[size + 9] = location.y + 0.0f;
		vertices[size + 10] = location.z + 1.0f;
		vertices[size + 11] = 0.6f;
		vertices[size + 12] = 1.0f;
		vertices[size + 13] = 0.0f;
		vertices[size + 14] = 0.0f;
		vertices[size + 15] = 1.0f;

		vertices[size + 16] = location.x + 1.0f;
		vertices[size + 17] = location.y + 1.0f;
		vertices[size + 18] = location.z + 1.0f;
		vertices[size + 19] = 0.6f;
		vertices[size + 20] = 0.9f;
		vertices[size + 21] = 0.0f;
		vertices[size + 22] = 0.0f;
		vertices[size + 23] = 1.0f;

		vertices[size + 24] = location.x + 0.0f;
		vertices[size + 25] = location.y + 1.0f;
		vertices[size + 26] = location.z + 1.0f;
		vertices[size + 27] = 0.5f;
		vertices[size + 28] = 0.9f;
		vertices[size + 29] = 0.0f;
		vertices[size + 30] = 0.0f;
		vertices[size + 31] = 1.0f;
	}
	if (faces.left)
	{
		size = vertices.size();
		vertices.resize(size + 32);

		vertices[size] = location.x + 0.0f;
		vertices[size + 1] = location.y + 0.0f;
		vertices[size + 2] = location.z + 0.0f;
		vertices[size + 3] = 0.5f;
		vertices[size + 4] = 1.0f;
		vertices[size + 5] = -1.0f;
		vertices[size + 6] = 0.0f;
		vertices[size + 7] = 0.0f;

		vertices[size + 8] = location.x + 0.0f;
		vertices[size + 9] = location.y + 0.0f;
		vertices[size + 10] = location.z + 1.0f;
		vertices[size + 11] = 0.6f;
		vertices[size + 12] = 1.0f;
		vertices[size + 13] = -1.0f;
		vertices[size + 14] = 0.0f;
		vertices[size + 15] = 0.0f;

		vertices[size + 16] = location.x + 0.0f;
		vertices[size + 17] = location.y + 1.0f;
		vertices[size + 18] = location.z + 1.0f;
		vertices[size + 19] = 0.6f;
		vertices[size + 20] = 0.9f;
		vertices[size + 21] = -1.0f;
		vertices[size + 22] = 0.0f;
		vertices[size + 23] = 0.0f;

		vertices[size + 24] = location.x + 0.0f;
		vertices[size + 25] = location.y + 1.0f;
		vertices[size + 26] = location.z + 0.0f;
		vertices[size + 27] = 0.5f;
		vertices[size + 28] = 0.9f;
		vertices[size + 29] = -1.0f;
		vertices[size + 30] = 0.0f;
		vertices[size + 31] = 0.0f;
	}
	if (faces.right)
	{

		size = vertices.size();
		vertices.resize(size + 32);

		vertices[size] = location.x + 1.0f;
		vertices[size + 1] = location.y + 0.0f;
		vertices[size + 2] = location.z + 1.0f;
		vertices[size + 3] = 0.5f;
		vertices[size + 4] = 1.0f;
		vertices[size + 5] = 1.0f;
		vertices[size + 6] = 0.0f;
		vertices[size + 7] = 0.0f;

		vertices[size + 8] = location.x + 1.0f;
		vertices[size + 9] = location.y + 0.0f;
		vertices[size + 10] = location.z + 0.0f;
		vertices[size + 11] = 0.6f;
		vertices[size + 12] = 1.0f;
		vertices[size + 13] = 1.0f;
		vertices[size + 14] = 0.0f;
		vertices[size + 15] = 0.0f;

		vertices[size + 16] = location.x + 1.0f;
		vertices[size + 17] = location.y + 1.0f;
		vertices[size + 18] = location.z + 0.0f;
		vertices[size + 19] = 0.6f;
		vertices[size + 20] = 0.9f;
		vertices[size + 21] = 1.0f;
		vertices[size + 22] = 0.0f;
		vertices[size + 23] = 0.0f;

		vertices[size + 24] = location.x + 1.0f;
		vertices[size + 25] = location.y + 1.0f;
		vertices[size + 26] = location.z + 1.0f;
		vertices[size + 27] = 0.5f;
		vertices[size + 28] = 0.9f;
		vertices[size + 29] = 1.0f;
		vertices[size + 30] = 0.0f;
		vertices[size + 31] = 0.0f;
	}
	if (faces.top)
	{
		size = vertices.size();
		vertices.resize(size + 32);

		vertices[size] = location.x + 0.0f;
		vertices[size + 1] = location.y + 1.0f;
		vertices[size + 2] = location.z + 1.0f;
		vertices[size + 3] = 0.5f;
		vertices[size + 4] = 1.0f;
		vertices[size + 5] = 0.0f;
		vertices[size + 6] = 1.0f;
		vertices[size + 7] = 0.0f;

		vertices[size + 8] = location.x + 1.0f;
		vertices[size + 9] = location.y + 1.0f;
		vertices[size + 10] = location.z + 1.0f;
		vertices[size + 11] = 0.6f;
		vertices[size + 12] = 1.0f;
		vertices[size + 13] = 0.0f;
		vertices[size + 14] = 1.0f;
		vertices[size + 15] = 0.0f;

		vertices[size + 16] = location.x + 1.0f;
		vertices[size + 17] = location.y + 1.0f;
		vertices[size + 18] = location.z + 0.0f;
		vertices[size + 19] = 0.6f;
		vertices[size + 20] = 0.9f;
		vertices[size + 21] = 0.0f;
		vertices[size + 22] = 1.0f;
		vertices[size + 23] = 0.0f;

		vertices[size + 24] = location.x + 0.0f;
		vertices[size + 25] = location.y + 1.0f;
		vertices[size + 26] = location.z + 0.0f;
		vertices[size + 27] = 0.5f;
		vertices[size + 28] = 0.9f;
		vertices[size + 29] = 0.0f;
		vertices[size + 30] = 1.0f;
		vertices[size + 31] = 0.0f;

	}
	if (faces.bottom)
	{
		size = vertices.size();
		vertices.resize(size + 32);

		vertices[size] = location.x + 0.0f;
		vertices[size + 1] = location.y + 0.0f;
		vertices[size + 2] = location.z + 0.0f;
		vertices[size + 3] = 0.5f;
		vertices[size + 4] = 1.0f;
		vertices[size + 5] = 0.0f;
		vertices[size + 6] = -1.0f;
		vertices[size + 7] = 0.0f;

		vertices[size + 8] = location.x + 1.0f;
		vertices[size + 9] = location.y + 0.0f;
		vertices[size + 10] = location.z + 0.0f;
		vertices[size + 11] = 0.6f;
		vertices[size + 12] = 1.0f;
		vertices[size + 13] = 0.0f;
		vertices[size + 14] = -1.0f;
		vertices[size + 15] = 0.0f;

		vertices[size + 16] = location.x + 1.0f;
		vertices[size + 17] = location.y + 0.0f;
		vertices[size + 18] = location.z + 1.0f;
		vertices[size + 19] = 0.6f;
		vertices[size + 20] = 0.9f;
		vertices[size + 21] = 0.0f;
		vertices[size + 22] = -1.0f;
		vertices[size + 23] = 0.0f;

		vertices[size + 24] = location.x + 0.0f;
		vertices[size + 25] = location.y + 0.0f;
		vertices[size + 26] = location.z + 1.0f;
		vertices[size + 27] = 0.5f;
		vertices[size + 28] = 0.9f;
		vertices[size + 29] = 0.0f;
		vertices[size + 30] = -1.0f;
		vertices[size + 31] = 0.0f;
	}

}

BlockCobblestone::~BlockCobblestone()
{

}