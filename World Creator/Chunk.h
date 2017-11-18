#pragma once

#include "Blocks.h"
#include <fstream>

#define DEFAULT_CHUNK_SIZE_X 16
#define DEFAULT_CHUNK_SIZE_Y 128
#define DEFAULT_CHUNK_SIZE_Z 16

class Chunk
{
public:
	Chunk();
	Chunk(glm::ivec3 & location);
	Chunk(const Chunk & right);
	GLvoid init(glm::ivec3 & location);
	GLuint getID() const;
	Chunk & operator=(const Chunk & right);
	inline GLboolean operator>(const Chunk & right)const
	{
		if (location.x > right.location.x)
		{
			return GL_TRUE;
		}
		else
		{
			if (location.x == right.location.x)
			{
				if (location.y > right.location.y)
				{
					return GL_TRUE;
				}
				else
				{
					if (location.y == right.location.y)
					{
						if (location.z > right.location.z)
						{
							return GL_TRUE;
						}
						else
						{
							return GL_FALSE;
						}
					}
					else
					{
						return GL_FALSE;
					}
				}
			}
			else
			{
				return GL_FALSE;
			}
		}
	}
	inline GLboolean operator==(const Chunk & right)const
	{
		if ((location.x == right.location.x) && (location.y == right.location.y) && (location.z == right.location.z))
		{
			return GL_TRUE;
		}
		return GL_FALSE;
	}
	inline GLboolean operator<(const Chunk & right)const
	{
		if (location.x < right.location.x)
		{
			return GL_TRUE;
		}
		else
		{
			if (location.x == right.location.x)
			{
				if (location.y < right.location.y)
				{
					return GL_TRUE;
				}
				else
				{
					if (location.y == right.location.y)
					{
						if (location.z < right.location.z)
						{
							return GL_TRUE;
						}
						else
						{
							return GL_FALSE;
						}
					}
					else
					{
						return GL_FALSE;
					}
				}
			}
			else
			{
				return GL_FALSE;
			}
		}
	}
	~Chunk();

public:
	glm::ivec3 location;
	GLuint blockID[DEFAULT_CHUNK_SIZE_X][DEFAULT_CHUNK_SIZE_Y][DEFAULT_CHUNK_SIZE_Z];
	DrawList drawList;

private:
	GLuint ID;
	static GLuint chunkCount;
};

std::ofstream & operator<<(std::ofstream & left, const Chunk & right);
std::ifstream & operator>>(std::ifstream & left, Chunk & right);