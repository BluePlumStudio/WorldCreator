#pragma once

#define GLEW_STATIC
//#undef _DEBUG

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <ft2build.h>

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <map>

#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Vertex.h"
#include "Camera.h"
#include "DrawList.h"
#include "Blocks.h"
#include "Chunk.h"
#include "World.h"
#include "PipeLine.h"
#include "Font.h"
#include "TextRenderer.h"
#include "GUIRenderer.h"
#include "FrameBuffer.h"

#define DEFAULT_WINDOW_WIDTH 900.0
#define DEFAULT_WINDOW_HEIGHT 506.0

enum GameState
{
	GAME_STATE_ACTIVE,
	GAME_STATE_MENU,
	GAME_STATE_WIN

};

class Game
{
public:
	struct Options
	{
		Options()
		{
			FOV = 70.0f;
			mouseSpeed = 0.2f;
			moveSpeed = 10;
			maxLoadedChunksCount = 512;
		}
		GLfloat FOV;
		GLfloat mouseSpeed;
		GLint moveSpeed;
		GLint maxLoadedChunksCount;
	};
	Game();
	GLint init();
	GLboolean readOptions(const GLchar * filePath);
	GLint run();
	/*控制*/
	// GAME_STATE_ACTIVE
	inline GLvoid gameActiveControl();
	static GLvoid gameActiveKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

	static GLvoid gameActiveCursorCallback(GLFWwindow* window, GLdouble xpos, GLdouble ypos);
	static GLvoid gameActiveMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	GLvoid destroyBlock(World & world);
	GLvoid setBlock(World & world);
	// GAME_STATE_MENU
	inline GLvoid gameMenuControl();
	static GLvoid gameMenuKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

	static GLvoid gameMenuCursorCallback(GLFWwindow* window, GLdouble xpos, GLdouble ypos);
	static GLvoid gameMenuMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	/*程序渲染阶段*/
	GLint gameActiveRender();
	GLint gameMenuRender();
	GLint gameMenuOptionsRender();
	/*其他*/
	inline GLvoid updateNearChunks(World & world, const LocationInChunk & origin);
	~Game();
public:
	static GLboolean keyPress[1024];
	static GLboolean mouseButtonPress[512];

	Options options;

	GLFWwindow* window;
	static GLfloat windowWidth;
	static GLfloat windowHeight;
	static Camera camera;
	GLint currentBlockIndex;
	GLint(Game::*renderFunctions[3])();
	GameState gameState;
	static GLboolean isShowDebugInfo;
	static GLboolean isShowHUD;

	IMGUIRenderer GUIRenderer;
	StdShaderProgram worldProgram;
	StdShaderProgram whiteProgram;
	StdShaderProgram textProgram;
	StdShaderProgram logoProgram;
	StdShaderProgram backgroundProgram;
	StdShaderProgram textMSDFProgram;
	StdShaderProgram GUIProgram;
	StdShaderProgram screenProgram;

	Texture2D blocksTexture;
	Texture2D logoTexture;
	Texture2D backgroundTexture;
	Texture2D widgetsTexture;

private:
	static GLint gameCount;

};

