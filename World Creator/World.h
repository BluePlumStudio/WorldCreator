#pragma once

#include <algorithm>
#include <stack>
#include <thread>
#include <mutex>

#include "Chunk.h"
#include "ShaderProgram.h"

#define DEFAULT_DRAW_CHUNKS_COUNT_X 3
#define DEFAULT_DRAW_CHUNKS_COUNT_Y 1
#define DEFAULT_DRAW_CHUNKS_COUNT_Z 3

#define TRANSFORM_WORLD_COORDS_INTO_CHUNK_LOCATION_X(n) ((n)>>4)
#define TRANSFORM_WORLD_COORDS_INTO_CHUNK_LOCATION_Y(n) ((n)>>7)
#define TRANSFORM_WORLD_COORDS_INTO_CHUNK_LOCATION_Z(n) ((n)>>4)
#define TRANSFORM_WORLD_COORDS_INTO_ARRAY_LOCATION_IN_CHUNK_X(n) ((n)&15)
#define TRANSFORM_WORLD_COORDS_INTO_ARRAY_LOCATION_IN_CHUNK_Y(n) ((n)&127)
#define TRANSFORM_WORLD_COORDS_INTO_ARRAY_LOCATION_IN_CHUNK_Z(n) ((n)&15)

#define WORLD_MAX_LOADED_CHUNKS_COUNT 512

class LocationInChunk
{
public:
	LocationInChunk();
	LocationInChunk(const LocationInChunk & right);
	LocationInChunk & operator=(LocationInChunk & right);
	~LocationInChunk();
public:
	glm::ivec3 locationInArray;
	std::vector<Chunk>::iterator iterator;
	GLint index;
private:

};

/*============================================================*/

class World
{
public:
	class Less
	{
	public:
		Less()
		{

		}
		GLboolean operator()(const std::vector<Chunk>::iterator & left, const std::vector<Chunk>::iterator & right) const
		{
			return *left < *right;
		}
		~Less()
		{

		}

	private:

	};
	World();
	GLvoid sortChunks();
	GLvoid sortChunksIterators();
	inline GLvoid addChunk(Chunk & chunk)
	{
		chunks.push_back(chunk);
	}
	inline GLvoid addChunk(glm::ivec3 & chunkLocation)
	{
		//chunks.push_back(Chunk(chunkLocation));
		chunks.resize(chunks.size() + 1);
		chunks[chunks.size() - 1].init(chunkLocation);
		//chunksSortedIterators.push_back(chunks.end() - 1);
	}
	static inline glm::ivec3 getChunkLocation(const glm::ivec3 & worldCoords)
	{
		return glm::ivec3(TRANSFORM_WORLD_COORDS_INTO_CHUNK_LOCATION_X(worldCoords.x),
			TRANSFORM_WORLD_COORDS_INTO_CHUNK_LOCATION_Y(worldCoords.y),
			TRANSFORM_WORLD_COORDS_INTO_CHUNK_LOCATION_Z(worldCoords.z));
	}
	static inline glm::ivec3 getArrayLocationChunk(const glm::ivec3 & worldCoords)
	{
		return glm::ivec3(TRANSFORM_WORLD_COORDS_INTO_ARRAY_LOCATION_IN_CHUNK_X(worldCoords.x),
			TRANSFORM_WORLD_COORDS_INTO_ARRAY_LOCATION_IN_CHUNK_Y(worldCoords.y),
			TRANSFORM_WORLD_COORDS_INTO_ARRAY_LOCATION_IN_CHUNK_Z(worldCoords.z));
	}
	GLint getChunkIndex(const glm::ivec3 & chunkLocation)const;
	std::vector<Chunk>::iterator getChunkIterator(const glm::ivec3 & chunkLocation);
	LocationInChunk getLocationInChunk(const glm::ivec3 blockWorldCoords);
	GLvoid updateChunks();
	GLvoid updateChunk(const GLuint chunkIndex);
	GLvoid updateChunk(std::vector<Chunk>::iterator chunkIterator);
	virtual GLvoid draw();
	virtual ~World();
public:
	Blocks blocks;
	std::vector<Chunk> chunks;
	std::vector<std::vector<Chunk>::iterator> chunksSortedIterators;
protected:
	

};

/*============================================================*/

class WorldDefault:public World
{
public:
	WorldDefault();
	GLvoid init(GLint maxLoadedChunksCount = WORLD_MAX_LOADED_CHUNKS_COUNT, GLint drawChunksCountX = DEFAULT_DRAW_CHUNKS_COUNT_X, GLint drawChunksCountY = DEFAULT_DRAW_CHUNKS_COUNT_Y, GLint drawChunksCountZ = DEFAULT_DRAW_CHUNKS_COUNT_Z);
	GLvoid rebuildChunk(Chunk & chunk);
	GLvoid rebuildChunk(std::vector<Chunk>::iterator chunkIterator);
	GLvoid updateDrawChunks(const glm::vec3 & worldCoords);
	inline GLvoid draw()
	{
		GLuint size = drawChunksIterators.size();

		for (GLuint i = 0; i < size; ++i)
		{
			(*drawChunksIterators[i]).drawList.draw();
		}
	}
	GLboolean readChunkFile(const glm::ivec3 & chunkLocation,Chunk & chunk);
	GLboolean readChunkFile(const glm::ivec3 & chunkLocation, std::vector<Chunk>::iterator chunkIterator);
	GLboolean writeChunksFile();
	~WorldDefault();

public:
	std::vector<std::vector<Chunk>::iterator> drawChunksIterators;
private:
	glm::ivec3 lastChunkLocation;
	glm::ivec3 lastPlayerLocationi;

	GLint maxLoadedChunksCount;
	GLint drawChunksCountX;
	GLint drawChunksCountY;
	GLint drawChunksCountZ;
};


