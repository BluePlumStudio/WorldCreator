#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <iostream>
#include <queue>

#include "Block.h"

class Blocks
{
public:
	Blocks();
	~Blocks();
public:
	std::vector<Block *> data;
private:

};
