#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>

struct Vertex
{
public:
	Vertex()
	{
		position = { 0.0f, 0.0f, 0.0f };
		texCoords = { 0.0f, 0.0f };
	}
	Vertex(const Vertex & vert)
	{
		this->position = vert.position;
		this->texCoords = vert.texCoords;
	}
	Vertex & operator=(Vertex & right)
	{
		this->position = right.position;
		this->texCoords = right.texCoords;
		return *this;
	}
	~Vertex()
	{

	}
public:
	glm::vec3 position;
	glm::vec2 texCoords;
	glm::vec3 Normal;
};
