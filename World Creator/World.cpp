#include "World.h"

using namespace std;

LocationInChunk::LocationInChunk()
{
	locationInArray = { 0, 0, 0 };
	index = -1;
}

LocationInChunk::LocationInChunk(const LocationInChunk & right)
{
	iterator = right.iterator;
	locationInArray = right.locationInArray;
	index = right.index;
}

LocationInChunk & LocationInChunk::operator = (LocationInChunk & right)
{
	iterator = right.iterator;
	locationInArray = right.locationInArray;
	index = right.index;
	return *this;
}

LocationInChunk::~LocationInChunk()
{
}

/*============================================================*/

World::World()
{
	if (WORLD_MAX_LOADED_CHUNKS_COUNT <= (DEFAULT_DRAW_CHUNKS_COUNT_X*DEFAULT_DRAW_CHUNKS_COUNT_Y*DEFAULT_DRAW_CHUNKS_COUNT_Z))
	{
		throw runtime_error("最大加载Chunk数小于等于渲染Chunk数");
	}
	chunks.clear();
	
}

GLvoid World::sortChunks()
{
	//double b = glfwGetTime();
	sort(chunks.begin(), chunks.end(), less<Chunk>());
	//cout << glfwGetTime() - b << endl;
	sortChunksIterators();
	
}

GLvoid World::sortChunksIterators()
{
	//double b = glfwGetTime();
	sort(chunksSortedIterators.begin(), chunksSortedIterators.end(), Less());
	//cout << glfwGetTime() - b << endl;
}

GLint World::getChunkIndex(const glm::ivec3 & chunkLocation)const
{
	if (!chunks.size())
	{
		return -1;
	}

	GLint low = 0;
	GLint high = chunksSortedIterators.size() - 1;
	while (low <= high)
	{
		GLint mid = (low + high) / 2;

		if ((*chunksSortedIterators[mid]).location.x < chunkLocation.x)
		{
			low = mid + 1;
		}
		else if ((*chunksSortedIterators[mid]).location.x > chunkLocation.x)
		{
			high = mid - 1;
		}
		else
		{
			if ((*chunksSortedIterators[mid]).location.y < chunkLocation.y)
			{
				low = mid + 1;
			}
			else if ((*chunksSortedIterators[mid]).location.y > chunkLocation.y)
			{
				high = mid - 1;
			}
			else
			{
				if ((*chunksSortedIterators[mid]).location.z < chunkLocation.z)
				{
					low = mid + 1;
				}
				else if ((*chunksSortedIterators[mid]).location.z > chunkLocation.z)
				{
					high = mid - 1;
				}
				else
				{
					//cout << "Yes" << endl;
					return chunksSortedIterators[mid] - chunks.begin();
				}
			}
		}
	}
	return -1;
}

vector<Chunk>::iterator World::getChunkIterator(const glm::ivec3 & chunkLocation)
{
	if (!chunks.size())
	{
		return chunks.end();
	}

	GLint low = 0;
	GLint high = chunksSortedIterators.size() - 1;
	while (low <= high)
	{
		GLint mid = (low + high) / 2;

		if ((*chunksSortedIterators[mid]).location.x < chunkLocation.x)
		{
			low = mid + 1;
		}
		else if ((*chunksSortedIterators[mid]).location.x > chunkLocation.x)
		{
			high = mid - 1;
		}
		else
		{
			if ((*chunksSortedIterators[mid]).location.y < chunkLocation.y)
			{
				low = mid + 1;
			}
			else if ((*chunksSortedIterators[mid]).location.y > chunkLocation.y)
			{
				high = mid - 1;
			}
			else
			{
				if ((*chunksSortedIterators[mid]).location.z < chunkLocation.z)
				{
					low = mid + 1;
				}
				else if ((*chunksSortedIterators[mid]).location.z > chunkLocation.z)
				{
					high = mid - 1;
				}
				else
				{
					//cout << "Yes" << endl;
					return chunksSortedIterators[mid];
				}
			}
		}
	}
	return chunks.end();
}

LocationInChunk World::getLocationInChunk(const glm::ivec3 blockWorldCoords)
{
	LocationInChunk locationInChunk;
	glm::ivec3 chunkLocation;

	/* example
	block (-17,0,-17)
	block (-16,0,-16)
	*/

	chunkLocation.x = TRANSFORM_WORLD_COORDS_INTO_CHUNK_LOCATION_X(blockWorldCoords.x);
	chunkLocation.y = TRANSFORM_WORLD_COORDS_INTO_CHUNK_LOCATION_Y(blockWorldCoords.y);
	chunkLocation.z = TRANSFORM_WORLD_COORDS_INTO_CHUNK_LOCATION_Z(blockWorldCoords.z);
	locationInChunk.locationInArray.x = TRANSFORM_WORLD_COORDS_INTO_ARRAY_LOCATION_IN_CHUNK_X(blockWorldCoords.x);
	locationInChunk.locationInArray.y = TRANSFORM_WORLD_COORDS_INTO_ARRAY_LOCATION_IN_CHUNK_Y(blockWorldCoords.y);
	locationInChunk.locationInArray.z = TRANSFORM_WORLD_COORDS_INTO_ARRAY_LOCATION_IN_CHUNK_Z(blockWorldCoords.z);
	/*
	chunkLocation = getChunkLocation(blockWorldCoords);
	locationInChunk.locationInArray = getArrayLocationChunk(blockWorldCoords);
	*/
	
	locationInChunk.iterator = getChunkIterator(chunkLocation);
	if (locationInChunk.iterator == chunks.end())
	{
		locationInChunk.index = -1;

	}
	else
	{
		locationInChunk.index = locationInChunk.iterator - chunks.begin();
	}
	return locationInChunk;
}

GLvoid World::updateChunks()
{
	if (chunks.size() <= 0)
	{
		return;
	}

	glm::ivec3 blockLocation;
	LocationInChunk blockLocationInChunk;

	for (vector<Chunk>::iterator it = chunks.begin(); it != chunks.end(); ++it)
	{
		for (GLuint x = 0; x < DEFAULT_CHUNK_SIZE_X; ++x)
		{
			for (GLuint y = 0; y < DEFAULT_CHUNK_SIZE_Y; ++y)
			{
				for (GLuint z = 0; z < DEFAULT_CHUNK_SIZE_Z; ++z)
				{
					if (!(*it).blockID[x][y][z])
					{
						continue;
					}

					blockLocation = { (*it).location.x*DEFAULT_CHUNK_SIZE_X + x,
						(*it).location.y*DEFAULT_CHUNK_SIZE_Y + y,
						(*it).location.z*DEFAULT_CHUNK_SIZE_Z + z };

					GLboolean faces[6] = { 0 };

					//前 后
					if (!z)
					{
						blockLocationInChunk = getLocationInChunk(glm::ivec3(blockLocation.x, blockLocation.y, blockLocation.z - 1));
						if (blockLocationInChunk.iterator != chunks.end())
						{
							faces[0] = !(*blockLocationInChunk.iterator).blockID
								[blockLocationInChunk.locationInArray.x]
							[blockLocationInChunk.locationInArray.y]
							[blockLocationInChunk.locationInArray.z];
						}
						else
						{
							faces[0] = true;
						}
						faces[1] = !(*it).blockID[x][y][z + 1];
					}
					else if (z == DEFAULT_CHUNK_SIZE_Z - 1)
					{
						blockLocationInChunk = getLocationInChunk(glm::ivec3(blockLocation.x, blockLocation.y, blockLocation.z + 1));
						if (blockLocationInChunk.iterator != chunks.end())
						{
							faces[1] = !(*blockLocationInChunk.iterator).blockID
								[blockLocationInChunk.locationInArray.x]
							[blockLocationInChunk.locationInArray.y]
							[blockLocationInChunk.locationInArray.z];
						}
						else
						{
							faces[1] = true;
						}
						faces[0] = !(*it).blockID[x][y][z - 1];
					}
					else
					{
						faces[0] = !(*it).blockID[x][y][z - 1];
						faces[1] = !(*it).blockID[x][y][z + 1];
					}

					//左 右
					if (!x)
					{
						blockLocationInChunk = getLocationInChunk(glm::ivec3(blockLocation.x - 1, blockLocation.y, blockLocation.z));
						if (blockLocationInChunk.iterator != chunks.end())
						{
							faces[2] = !(*blockLocationInChunk.iterator).blockID
								[blockLocationInChunk.locationInArray.x]
							[blockLocationInChunk.locationInArray.y]
							[blockLocationInChunk.locationInArray.z];
						}
						else
						{
							faces[2] = true;
						}
						faces[3] = !(*it).blockID[x + 1][y][z];
					}
					else if (x == DEFAULT_CHUNK_SIZE_X - 1)
					{
						blockLocationInChunk = getLocationInChunk(glm::ivec3(blockLocation.x + 1, blockLocation.y, blockLocation.z));
						if (blockLocationInChunk.iterator != chunks.end())
						{
							faces[3] = !(*blockLocationInChunk.iterator).blockID
								[blockLocationInChunk.locationInArray.x]
							[blockLocationInChunk.locationInArray.y]
							[blockLocationInChunk.locationInArray.z];
						}
						else
						{
							faces[3] = true;
						}
						faces[2] = !(*it).blockID[x - 1][y][z];
					}
					else
					{
						faces[2] = !(*it).blockID[x - 1][y][z];
						faces[3] = !(*it).blockID[x + 1][y][z];
					}
					//上 下
					if (y == DEFAULT_CHUNK_SIZE_Y - 1)
					{
						blockLocationInChunk = getLocationInChunk(glm::ivec3(blockLocation.x, blockLocation.y + 1, blockLocation.z));
						if (blockLocationInChunk.iterator != chunks.end())
						{
							faces[4] = !(*blockLocationInChunk.iterator).blockID
								[blockLocationInChunk.locationInArray.x]
							[blockLocationInChunk.locationInArray.y]
							[blockLocationInChunk.locationInArray.z];
						}
						else
						{
							faces[4] = true;
						}
						faces[5] = !(*it).blockID[x][y - 1][z];
					}
					else if (!y)
					{
						blockLocationInChunk = getLocationInChunk(glm::ivec3(blockLocation.x, blockLocation.y - 1, blockLocation.z));
						if (blockLocationInChunk.iterator != chunks.end())
						{
							faces[5] = !(*blockLocationInChunk.iterator).blockID
								[blockLocationInChunk.locationInArray.x]
							[blockLocationInChunk.locationInArray.y]
							[blockLocationInChunk.locationInArray.z];
						}
						else
						{
							faces[5] = true;
						}
						faces[4] = !(*it).blockID[x][y + 1][z];
					}
					else
					{
						faces[4] = !(*it).blockID[x][y + 1][z];
						faces[5] = !(*it).blockID[x][y - 1][z];
					}

					DrawFaces drawFaces(faces[0], faces[1], faces[2], faces[3], faces[4], faces[5]);

					blocks.data[(*it).blockID[x][y][z]]->getDrawData((*it).drawList.data, drawFaces, blockLocation);

				}

			}
		}
		(*it).drawList.updateData();
		(*it).drawList.data.clear();
	}
}

GLvoid World::updateChunk(const GLuint chunkIndex)
{
	if (chunkIndex >= chunks.size() || chunkIndex < 0)
	{
		return;
	}

	vector<Chunk>::iterator it = chunks.begin() + chunkIndex;
	glm::ivec3 blockLocation;
	LocationInChunk blockLocationInChunk;

	for (GLuint x = 0; x < DEFAULT_CHUNK_SIZE_X; ++x)
	{
		for (GLuint y = 0; y < DEFAULT_CHUNK_SIZE_Y; ++y)
		{
			for (GLuint z = 0; z < DEFAULT_CHUNK_SIZE_Z; ++z)
			{
				if (!(*it).blockID[x][y][z])
				{
					continue;
				}

				blockLocation = { (*it).location.x*DEFAULT_CHUNK_SIZE_X + x,
					(*it).location.y*DEFAULT_CHUNK_SIZE_Y + y,
					(*it).location.z*DEFAULT_CHUNK_SIZE_Z + z };

				GLboolean faces[6] = { 0 };

				//前 后
				if (!z)
				{
					blockLocationInChunk = getLocationInChunk(glm::ivec3(blockLocation.x, blockLocation.y, blockLocation.z - 1));
					if (blockLocationInChunk.iterator != chunks.end())
					{
						faces[0] = !(*blockLocationInChunk.iterator).blockID
							[blockLocationInChunk.locationInArray.x]
						[blockLocationInChunk.locationInArray.y]
						[blockLocationInChunk.locationInArray.z];
					}
					else
					{
						faces[0] = true;
					}
					faces[1] = !(*it).blockID[x][y][z + 1];
				}
				else if (z == DEFAULT_CHUNK_SIZE_Z - 1)
				{
					blockLocationInChunk = getLocationInChunk(glm::ivec3(blockLocation.x, blockLocation.y, blockLocation.z + 1));
					if (blockLocationInChunk.iterator != chunks.end())
					{
						faces[1] = !(*blockLocationInChunk.iterator).blockID
							[blockLocationInChunk.locationInArray.x]
						[blockLocationInChunk.locationInArray.y]
						[blockLocationInChunk.locationInArray.z];
					}
					else
					{
						faces[1] = true;
					}
					faces[0] = !(*it).blockID[x][y][z - 1];
				}
				else
				{
					faces[0] = !(*it).blockID[x][y][z - 1];
					faces[1] = !(*it).blockID[x][y][z + 1];
				}

				//左 右
				if (!x)
				{
					blockLocationInChunk = getLocationInChunk(glm::ivec3(blockLocation.x - 1, blockLocation.y, blockLocation.z));
					if (blockLocationInChunk.iterator != chunks.end())
					{
						faces[2] = !(*blockLocationInChunk.iterator).blockID
							[blockLocationInChunk.locationInArray.x]
						[blockLocationInChunk.locationInArray.y]
						[blockLocationInChunk.locationInArray.z];
					}
					else
					{
						faces[2] = true;
					}
					faces[3] = !(*it).blockID[x + 1][y][z];
				}
				else if (x == DEFAULT_CHUNK_SIZE_X - 1)
				{
					blockLocationInChunk = getLocationInChunk(glm::ivec3(blockLocation.x + 1, blockLocation.y, blockLocation.z));
					if (blockLocationInChunk.iterator != chunks.end())
					{
						faces[3] = !(*blockLocationInChunk.iterator).blockID
							[blockLocationInChunk.locationInArray.x]
						[blockLocationInChunk.locationInArray.y]
						[blockLocationInChunk.locationInArray.z];
					}
					else
					{
						faces[3] = true;
					}
					faces[2] = !(*it).blockID[x - 1][y][z];
				}
				else
				{
					faces[2] = !(*it).blockID[x - 1][y][z];
					faces[3] = !(*it).blockID[x + 1][y][z];
				}
				//上 下
				if (y == DEFAULT_CHUNK_SIZE_Y - 1)
				{
					blockLocationInChunk = getLocationInChunk(glm::ivec3(blockLocation.x, blockLocation.y + 1, blockLocation.z));
					if (blockLocationInChunk.iterator != chunks.end())
					{
						faces[4] = !(*blockLocationInChunk.iterator).blockID
							[blockLocationInChunk.locationInArray.x]
						[blockLocationInChunk.locationInArray.y]
						[blockLocationInChunk.locationInArray.z];
					}
					else
					{
						faces[4] = true;
					}
					faces[5] = !(*it).blockID[x][y - 1][z];
				}
				else if (!y)
				{
					blockLocationInChunk = getLocationInChunk(glm::ivec3(blockLocation.x, blockLocation.y - 1, blockLocation.z));
					if (blockLocationInChunk.iterator != chunks.end())
					{
						faces[5] = !(*blockLocationInChunk.iterator).blockID
							[blockLocationInChunk.locationInArray.x]
						[blockLocationInChunk.locationInArray.y]
						[blockLocationInChunk.locationInArray.z];
					}
					else
					{
						faces[5] = true;
					}
					faces[4] = !(*it).blockID[x][y + 1][z];
				}
				else
				{
					faces[4] = !(*it).blockID[x][y + 1][z];
					faces[5] = !(*it).blockID[x][y - 1][z];
				}

				DrawFaces drawFaces(faces[0], faces[1], faces[2], faces[3], faces[4], faces[5]);

				blocks.data[(*it).blockID[x][y][z]]->getDrawData((*it).drawList.data, drawFaces, blockLocation);

			}

		}
	}
	(*it).drawList.updateData();
	(*it).drawList.data.clear();
}

GLvoid World::updateChunk(vector<Chunk>::iterator chunkIterator)
{
	if (chunkIterator == chunks.end())
	{
		return;
	}

	glm::ivec3 blockLocation;
	LocationInChunk blockLocationInChunk;

	for (GLuint x = 0; x < DEFAULT_CHUNK_SIZE_X; ++x)
	{
		for (GLuint y = 0; y < DEFAULT_CHUNK_SIZE_Y; ++y)
		{
			for (GLuint z = 0; z < DEFAULT_CHUNK_SIZE_Z; ++z)
			{
				if (!(*chunkIterator).blockID[x][y][z])
				{
					continue;
				}

				blockLocation = { (*chunkIterator).location.x*DEFAULT_CHUNK_SIZE_X + x,
					(*chunkIterator).location.y*DEFAULT_CHUNK_SIZE_Y + y,
					(*chunkIterator).location.z*DEFAULT_CHUNK_SIZE_Z + z };
				//double b = glfwGetTime();
				/*
				blockLocationInChunk[0] = getLocationInChunk(glm::ivec3(blockLocation.x, blockLocation.y, blockLocation.z - 1));
				blockLocationInChunk[1] = getLocationInChunk(glm::ivec3(blockLocation.x, blockLocation.y, blockLocation.z + 1));
				blockLocationInChunk[2] = getLocationInChunk(glm::ivec3(blockLocation.x - 1, blockLocation.y, blockLocation.z));
				blockLocationInChunk[3] = getLocationInChunk(glm::ivec3(blockLocation.x + 1, blockLocation.y, blockLocation.z));
				blockLocationInChunk[4] = getLocationInChunk(glm::ivec3(blockLocation.x, blockLocation.y + 1, blockLocation.z));
				blockLocationInChunk[5] = getLocationInChunk(glm::ivec3(blockLocation.x, blockLocation.y - 1, blockLocation.z));

				GLboolean faces[6] = { 0 };
				for (size_t i = 0; i < 6; ++i)
				{
					if (blockLocationInChunk[i].iterator != chunks.end())
					{
						if (!(*blockLocationInChunk[i].iterator).blockID[blockLocationInChunk[i].locationInArray.x][blockLocationInChunk[i].locationInArray.y][blockLocationInChunk[i].locationInArray.z])
						{
							faces[i] = GL_TRUE;
							//cout << "面：" << faces[i] << " 绘制！" << endl;
						}
						else
						{
							faces[i] = GL_FALSE;
						}
					}
					else
					{
						faces[i] = GL_TRUE;
					}
				}
				*/
				GLboolean faces[6] = { 0 };

				//前 后
				if (!z)
				{
					blockLocationInChunk = getLocationInChunk(glm::ivec3(blockLocation.x, blockLocation.y, blockLocation.z - 1));
					if (blockLocationInChunk.iterator != chunks.end())
					{
						faces[0] = !(*blockLocationInChunk.iterator).blockID
							[blockLocationInChunk.locationInArray.x]
						[blockLocationInChunk.locationInArray.y]
						[blockLocationInChunk.locationInArray.z];
					}
					else
					{
						faces[0] = true;
					}
					faces[1] = !(*chunkIterator).blockID[x][y][z + 1];
				}
				else if (z == DEFAULT_CHUNK_SIZE_Z - 1)
				{
					blockLocationInChunk = getLocationInChunk(glm::ivec3(blockLocation.x, blockLocation.y, blockLocation.z + 1));
					if (blockLocationInChunk.iterator != chunks.end())
					{
						faces[1] = !(*blockLocationInChunk.iterator).blockID
							[blockLocationInChunk.locationInArray.x]
						[blockLocationInChunk.locationInArray.y]
						[blockLocationInChunk.locationInArray.z];
					}
					else
					{
						faces[1] = true;
					}
					faces[0] = !(*chunkIterator).blockID[x][y][z - 1];
				}
				else
				{
					faces[0] = !(*chunkIterator).blockID[x][y][z - 1];
					faces[1] = !(*chunkIterator).blockID[x][y][z + 1];
				}

				//左 右
				if (!x)
				{
					blockLocationInChunk = getLocationInChunk(glm::ivec3(blockLocation.x - 1, blockLocation.y, blockLocation.z));
					if (blockLocationInChunk.iterator != chunks.end())
					{
						faces[2] = !(*blockLocationInChunk.iterator).blockID
							[blockLocationInChunk.locationInArray.x]
						[blockLocationInChunk.locationInArray.y]
						[blockLocationInChunk.locationInArray.z];
					}
					else
					{
						faces[2] = true;
					}
					faces[3] = !(*chunkIterator).blockID[x + 1][y][z];
				}
				else if (x == DEFAULT_CHUNK_SIZE_X - 1)
				{
					blockLocationInChunk = getLocationInChunk(glm::ivec3(blockLocation.x + 1, blockLocation.y, blockLocation.z));
					if (blockLocationInChunk.iterator != chunks.end())
					{
						faces[3] = !(*blockLocationInChunk.iterator).blockID
							[blockLocationInChunk.locationInArray.x]
						[blockLocationInChunk.locationInArray.y]
						[blockLocationInChunk.locationInArray.z];
					}
					else
					{
						faces[3] = true;
					}
					faces[2] = !(*chunkIterator).blockID[x - 1][y][z];
				}
				else
				{
					faces[2] = !(*chunkIterator).blockID[x - 1][y][z];
					faces[3] = !(*chunkIterator).blockID[x + 1][y][z];
				}
				//上 下
				if (y == DEFAULT_CHUNK_SIZE_Y - 1)
				{
					blockLocationInChunk = getLocationInChunk(glm::ivec3(blockLocation.x, blockLocation.y + 1, blockLocation.z));
					if (blockLocationInChunk.iterator != chunks.end())
					{
						faces[4] = !(*blockLocationInChunk.iterator).blockID
							[blockLocationInChunk.locationInArray.x]
						[blockLocationInChunk.locationInArray.y]
						[blockLocationInChunk.locationInArray.z];
					}
					else
					{
						faces[4] = true;
					}
					faces[5] = !(*chunkIterator).blockID[x][y - 1][z];
				}
				else if (!y)
				{
					blockLocationInChunk = getLocationInChunk(glm::ivec3(blockLocation.x, blockLocation.y - 1, blockLocation.z));
					if (blockLocationInChunk.iterator != chunks.end())
					{
						faces[5] = !(*blockLocationInChunk.iterator).blockID
							[blockLocationInChunk.locationInArray.x]
						[blockLocationInChunk.locationInArray.y]
						[blockLocationInChunk.locationInArray.z];
					}
					else
					{
						faces[5] = true;
					}
					faces[4] = !(*chunkIterator).blockID[x][y + 1][z];
				}
				else
				{
					faces[4] = !(*chunkIterator).blockID[x][y + 1][z];
					faces[5] = !(*chunkIterator).blockID[x][y - 1][z];
				}

				//cout << glfwGetTime() - b << endl;
				DrawFaces drawFaces(faces[0], faces[1], faces[2], faces[3], faces[4], faces[5]);

				blocks.data[(*chunkIterator).blockID[x][y][z]]->getDrawData((*chunkIterator).drawList.data, drawFaces, blockLocation);

			}

		}
	}
	(*chunkIterator).drawList.updateData();
	(*chunkIterator).drawList.data.clear();
}

GLvoid World::draw()
{
	for (std::vector<Chunk>::iterator it = chunks.begin(); it != chunks.end(); ++it)
	{
		(*it).drawList.draw();
	}
}

World::~World()
{
}

/*============================================================*/

WorldDefault::WorldDefault()
{
}

GLvoid WorldDefault::init(GLint maxLoadedChunksCount, GLint drawChunksCountX, GLint drawChunksCountY, GLint drawChunksCountZ)
{
	this->maxLoadedChunksCount = maxLoadedChunksCount;
	this->drawChunksCountX = drawChunksCountX;
	this->drawChunksCountY = drawChunksCountY;
	this->drawChunksCountZ = drawChunksCountZ;
	lastChunkLocation = { 0, -100, 0 };
	lastPlayerLocationi = { 0, -100, 0 };
	chunks.resize(maxLoadedChunksCount + 16);
	chunks.clear();
	for (GLint x = -6; x < 6; ++x)
	{
		for (GLint z = -6; z < 6; ++z)
		{

			Chunk chunk(glm::ivec3(x, 0, z));
			if (!readChunkFile(glm::ivec3(x, 0, z), chunk))
			{
				rebuildChunk(chunk);
			}
			addChunk(chunk);

		}
	}
	
	//chunksSortedIterators.resize(chunks.size());
	for (GLuint i = 0; i < chunks.size(); ++i)
	{
		chunksSortedIterators.push_back(chunks.begin() + i);
	}

	sortChunksIterators();
}

GLvoid WorldDefault::updateDrawChunks(const glm::vec3 & worldCoords)
{
	glm::ivec3 chunkLocation;
	glm::ivec3 worldCoordsi = glm::ivec3(worldCoords);
	//GLint chunkIndex = -1;
	vector<Chunk>::iterator chunkIterator = chunks.end();

	if (lastPlayerLocationi == glm::ivec3(worldCoords))
	{
		return;
	}

	lastPlayerLocationi = worldCoords;
	chunkLocation.x = TRANSFORM_WORLD_COORDS_INTO_CHUNK_LOCATION_X(worldCoordsi.x);
	chunkLocation.y = TRANSFORM_WORLD_COORDS_INTO_CHUNK_LOCATION_Y(worldCoordsi.y);
	chunkLocation.z = TRANSFORM_WORLD_COORDS_INTO_CHUNK_LOCATION_Z(worldCoordsi.z);

	if (chunkLocation == lastChunkLocation)
	{
		return;
	}
	lastChunkLocation = chunkLocation;

	drawChunksIterators.clear();

	GLboolean isChunksIteratorsNeedSort = false;
	if (chunks.size() >= maxLoadedChunksCount)
	{
		writeChunksFile();
		chunksSortedIterators.clear();
		chunks.clear();
		cout << "保存世界！" << endl;
	}
	for (GLint x = -drawChunksCountX; x < drawChunksCountX; ++x)
	{
		for (GLint y = -drawChunksCountY; y < drawChunksCountY; ++y)
		{
			for (GLint z = -drawChunksCountZ; z < drawChunksCountZ; ++z)
			{
				glm::ivec3 curChunkLocation = chunkLocation;
				curChunkLocation.x += x;
				curChunkLocation.y += y;
				curChunkLocation.z += z;

				if (curChunkLocation.y < 0)
				{
					continue;
				}
				chunkIterator = getChunkIterator(curChunkLocation);

				if (chunkIterator != chunks.end())
				{
#ifdef _DEBUG
					//cout << "渲染区块：" << chunkIndex << " 重新添加！" << endl;
#endif
					drawChunksIterators.push_back(chunkIterator);
				}
				
				else
				{
					addChunk(curChunkLocation);
					chunkIterator = chunks.end() - 1;
					//读取存档
					if (!readChunkFile(curChunkLocation, chunkIterator))
					{
						if (!curChunkLocation.y)
						{
							rebuildChunk(chunkIterator);
						}
					}
					chunksSortedIterators.push_back(chunkIterator);
					drawChunksIterators.push_back(chunkIterator);
					//sortChunksIterators();
					isChunksIteratorsNeedSort = true;
				}
				
			}
		}
	}
	
	if (isChunksIteratorsNeedSort)
	{
		sortChunksIterators();
		
		for (size_t i = 0; i < drawChunksIterators.size(); ++i)
		{
			updateChunk(drawChunksIterators[i]);

		}
		
	}
	//cout << chunks.size() << endl;
	//cout << chunksSortedIterators.size() << endl;
}

GLvoid WorldDefault::rebuildChunk(Chunk & chunk)
{
	
	for (GLuint x = 0; x < DEFAULT_CHUNK_SIZE_X; ++x)
	{
		for (GLuint y = 0; y < 20; ++y)
		{
			for (GLuint z = 0; z < DEFAULT_CHUNK_SIZE_Z; ++z)
			{
				chunk.blockID[x][y][z] = 1;
			}
		}
	}
	for (GLuint x = 0; x < DEFAULT_CHUNK_SIZE_X; ++x)
	{
		for (GLuint y = 20; y < 24; ++y)
		{
			for (GLuint z = 0; z < DEFAULT_CHUNK_SIZE_Z; ++z)
			{
				chunk.blockID[x][y][z] = 3;
			}
		}
	}
	for (GLuint x = 0; x < DEFAULT_CHUNK_SIZE_X; ++x)
	{
		for (GLuint z = 0; z < DEFAULT_CHUNK_SIZE_Z; ++z)
		{
			chunk.blockID[x][24][z] = 2;
		}
	}
	
}

GLvoid WorldDefault::rebuildChunk(vector<Chunk>::iterator chunkIterator)
{

	for (GLuint x = 0; x < DEFAULT_CHUNK_SIZE_X; ++x)
	{
		for (GLuint y = 0; y < 20; ++y)
		{
			for (GLuint z = 0; z < DEFAULT_CHUNK_SIZE_Z; ++z)
			{
				(*chunkIterator).blockID[x][y][z] = 1;
			}
		}
	}
	for (GLuint x = 0; x < DEFAULT_CHUNK_SIZE_X; ++x)
	{
		for (GLuint y = 20; y < 24; ++y)
		{
			for (GLuint z = 0; z < DEFAULT_CHUNK_SIZE_Z; ++z)
			{
				(*chunkIterator).blockID[x][y][z] = 3;
			}
		}
	}
	for (GLuint x = 0; x < DEFAULT_CHUNK_SIZE_X; ++x)
	{
		for (GLuint z = 0; z < DEFAULT_CHUNK_SIZE_Z; ++z)
		{
			(*chunkIterator).blockID[x][24][z] = 2;
		}
	}

}

GLboolean WorldDefault::readChunkFile(const glm::ivec3 & chunkLocation,Chunk & chunk)
{
	ifstream sav;
	stringstream fileNameSS;
	fileNameSS << "Saves/" << chunkLocation.x << " " << chunkLocation.y << " " << chunkLocation.z << ".dat";
	sav.open(fileNameSS.str());
	if (!sav)
	{
#ifdef _DEBUG
		cout << "chunk：" << fileNameSS.str() << " 读取失败！" << endl;
#endif
		return false;
	}
	sav >> chunk;
	//cout << "chunk：" << fileNameSS.str() << " 读取成功！" << endl;
	return true;
}

GLboolean WorldDefault::readChunkFile(const glm::ivec3 & chunkLocation, vector<Chunk>::iterator chunkIterator)
{
	ifstream sav;
	stringstream fileNameSS;
	fileNameSS << "Saves/" << chunkLocation.x << " " << chunkLocation.y << " " << chunkLocation.z << ".dat";
	sav.open(fileNameSS.str());
	if (!sav)
	{
#ifdef _DEBUG
		cout << "chunk：" << fileNameSS.str() << " 读取失败！" << endl;
#endif
		return false;
	}
	sav >> (*chunkIterator);
	//cout << "chunk：" << fileNameSS.str() << " 读取成功！" << endl;
	return true;
}

GLboolean WorldDefault::writeChunksFile()
{
	for (std::vector<Chunk>::iterator it = chunks.begin(); it != chunks.end(); ++it)
	{
		ofstream sav;
		stringstream fileNameSS;
		fileNameSS << "Saves/" << (*it).location.x << " " << (*it).location.y << " " << (*it).location.z << ".dat";

		sav.open(fileNameSS.str());
		if (!sav)
		{
#ifdef _DEBUG
			cout << "chunk：" << fileNameSS.str() << " 写入失败！" << endl;
#endif
			return false;
		}
		sav << (*it);
	}
	return true;
}

WorldDefault::~WorldDefault()
{
	if (!writeChunksFile())
	{
		throw runtime_error("chunk写入失败！");
	}
	cout << "保存世界！" << endl;
}
