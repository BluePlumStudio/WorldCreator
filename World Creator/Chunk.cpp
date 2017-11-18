#include "Chunk.h"

using namespace std;

Chunk::Chunk()
{
	memset(blockID, 0, sizeof(GLuint)*DEFAULT_CHUNK_SIZE_X*DEFAULT_CHUNK_SIZE_Y*DEFAULT_CHUNK_SIZE_Z);
	drawList.init();
	drawList.setVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	drawList.setVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
	drawList.setVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(5 * sizeof(GLfloat)));
	drawList.setDataStride(8);
	drawList.setDrawMode(GL_QUADS);

	++chunkCount;
	ID = chunkCount;

}

GLvoid Chunk::init(glm::ivec3 & location)
{
	this->location = location;
}

Chunk::Chunk(glm::ivec3 & location)
{
	memset(blockID, 0, sizeof(GLuint)*DEFAULT_CHUNK_SIZE_X*DEFAULT_CHUNK_SIZE_Y*DEFAULT_CHUNK_SIZE_Z);
	this->location = location;
	drawList.init();
	drawList.setVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	drawList.setVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
	drawList.setVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(5 * sizeof(GLfloat)));
	drawList.setDataStride(8);
	drawList.setDrawMode(GL_QUADS);

	++chunkCount;
	ID = chunkCount;
}

Chunk::Chunk(const Chunk & right)
{
	memcpy(blockID, right.blockID, sizeof(GLuint)*DEFAULT_CHUNK_SIZE_X*DEFAULT_CHUNK_SIZE_Y*DEFAULT_CHUNK_SIZE_Z);
	this->location = right.location;
	drawList.init();
	drawList = right.drawList;
	drawList.setVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	drawList.setVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
	drawList.setVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(5 * sizeof(GLfloat)));
	drawList.setDataStride(8);
	drawList.setDrawMode(GL_QUADS);

	++chunkCount;
	ID = chunkCount;
}

GLuint Chunk::getID() const
{
	return ID;
}

Chunk & Chunk::operator=(const Chunk & right)
{
	memcpy(blockID, right.blockID, sizeof(right.blockID));
	this->location = right.location;
	drawList = right.drawList;

	return*this;
}

Chunk::~Chunk()
{
	--chunkCount;
}

GLuint Chunk::chunkCount = 0;

ofstream & operator<<(ofstream & left,const Chunk & right)
{
	//left << right.location.x << right.location.y << right.location.z;
	left.write((char *)right.blockID, sizeof(right.blockID));
	return left;
}

ifstream & operator>>(ifstream & left, Chunk & right)
{
	//left >> right.location.x;
	//left >> right.location.y;
	//left >> right.location.z;
	left.read((char *)right.blockID, sizeof(right.blockID));
	return left;
}