#include "Game.h"

#ifdef WIN32
#include <Windows.h>
#endif

using namespace std;


GLfloat Game::windowWidth = 0;
GLfloat Game::windowHeight = 0;
Camera Game::camera;
GLint Game::gameCount = 0;
GLboolean Game::keyPress[1024] = {};
GLboolean Game::mouseButtonPress[512] = {};
GLboolean Game::isShowDebugInfo = false;
GLboolean Game::isShowHUD = true;


Game::Game()
{
	if (gameCount)
	{
		throw runtime_error("Game对象不能超过1个！");
	}
	gameCount++;

}

GLint Game::init()
{
	if (glfwInit() != GLFW_TRUE)
	{
		cout << "GLFW初始化失败！" << endl;
		return 1;
	}
	cout << "GLFW初始化成功！" << endl;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	windowWidth = DEFAULT_WINDOW_WIDTH;
	windowHeight = DEFAULT_WINDOW_HEIGHT;
	window = glfwCreateWindow((int)windowWidth, (int)windowHeight, "World Creator", nullptr, nullptr);
	if (window == nullptr)
	{
		cout << "GLFW创建主窗口失败！" << endl;
		glfwTerminate();
		return 1;
	}
	cout << "GLFW创建主窗口成功！" << endl;
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	/*
	glfwMaximizeWindow(window);
	GLint w, h;
	glfwGetWindowSize(window, &w, &h);
	windowWidth = static_cast<GLfloat>(w);
	windowHeight = static_cast<GLfloat>(h);
	*/
	glViewport(0, 0, GLsizei(windowWidth), GLsizei(windowHeight));

	if (glewInit() != GLEW_OK)
	{
		cout << "GLEW初始化失败！" << endl;
		return 1;
	}
	cout << "GLEW初始化成功！" << endl;

	//设置窗口初始色
	PipeLine::clearColor(0.0f, 0.0f, 0.0f, 1.0f);
	PipeLine::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//glfwMaximizeWindow(window);

	/*关闭垂直同步*/
#ifdef WIN32
	typedef BOOL(APIENTRY *PFNWGLSWAPINTERVALFARPROC)(int);
	PFNWGLSWAPINTERVALFARPROC wglSwapIntervalEXT = 0;
	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALFARPROC)wglGetProcAddress("wglSwapIntervalEXT");
	//wglSwapIntervalEXT(1);
	wglSwapIntervalEXT(0);
#endif

	memset(keyPress, 0, sizeof(keyPress));
	renderFunctions[GAME_STATE_ACTIVE] = &Game::gameActiveRender;
	renderFunctions[GAME_STATE_MENU] = &Game::gameMenuRender;
	gameState = GAME_STATE_MENU;
	//gameState = GAME_STATE_ACTIVE;

	/*着色器程序初始化*/
	if (worldProgram.init("Shaders/world.vert", "Shaders/world.frag"))
	{
		return 1;
	}

	if (whiteProgram.init("Shaders/white.vert", "Shaders/white.frag"))
	{
		return 1;
	}

	if (textProgram.init("Shaders/char.vert", "Shaders/char.frag"))
	{
		return 1;
	}

	if (logoProgram.init("Shaders/logo.vert", "Shaders/logo.frag"))
	{
		return 1;
	}

	if (backgroundProgram.init("Shaders/background.vert", "Shaders/background.frag"))
	{
		return 1;
	}

	if (textMSDFProgram.init("Shaders/char_msdf.vert", "Shaders/char_msdf.frag"))
	{
		return 1;
	}

	if (GUIProgram.init("Shaders/GUI.vert", "Shaders/GUI.frag"))
	{
		return 1;
	}

	if (screenProgram.init("Shaders/screen.vert", "Shaders/screen.frag"))
	{
		return 1;
	}
	
	/*纹理初始化*/
	if (blocksTexture.init("Resources/Textures/blocks.png", GL_TEXTURE0))
	{
		return 1;
	}

	if (logoTexture.init("Resources/Textures/Logo_full.png", GL_TEXTURE0))
	{
		return 1;
	}
	vector<pair<GLenum, GLint>>parameters;//纹理环绕、缩放参数
	parameters.push_back(make_pair<GLenum, GLint>(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	parameters.push_back(make_pair<GLenum, GLint>(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	parameters.push_back(make_pair<GLenum, GLint>(GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	parameters.push_back(make_pair<GLenum, GLint>(GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	logoTexture.texParameterivec(parameters);

	if (backgroundTexture.init("Resources/Textures/background.png", GL_TEXTURE0))
	{
		return 1;
	}
	backgroundTexture.texParameterivec(parameters);

	if (widgetsTexture.init("Resources/Textures/widgets.png", GL_TEXTURE0))
	{
		return 1;
	}
	
	/*GUI初始化*/
	if (GUIRenderer.init("Resources/Fonts/AdobeHeitiStd-Regular.otf", 0, 1, 2, 0, 16))
	{
		return 1;
	}
	GUIRenderer.textRenderer.texParameterivec(parameters);
	//Label
	GUILabel::setTexCoordsNormal(glm::vec2(0.0f, 0.0f), glm::vec2(0.5f, 0.125f));
	//Slider
	GUISlider::setSliderColorNormal(glm::vec4(0.0f, 0.0f, 0.0f, 0.5f));
	GUISlider::setSliderColorActive(glm::vec4(0.0f, 0.0f, 0.0f, 0.5f));
	GUISlider::setSliderColorHot(glm::vec4(0.0f, 0.0f, 0.0f, 0.5f));
	GUISlider::setBarColorNormal(glm::vec4(0.0f, 0.0f, 0.0f, 0.5f));
	//PushButton
	GUIPushButton::setTexCoordsNormal(glm::vec2(0.0f, 0.125f), glm::vec2(0.5f, 0.125f));
	GUIPushButton::setTexCoordsActive(glm::vec2(0.0f, 0.25f), glm::vec2(0.5f, 0.125f));
	GUIPushButton::setTexCoordsHot(glm::vec2(0.0f, 0.375f), glm::vec2(0.5f, 0.125f));
	GUIPushButton::setColorNormal(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	GUIPushButton::setColorActive(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	GUIPushButton::setColorHot(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	//GUIRenderer.setFontMode(Font::Mode::MSDF);
	/*相机初始化*/
	camera.init(glm::vec3(0.0f, 32.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.2f, 10.0f);

	return 0;
}

GLint Game::run()
{
	GLint ret;
	while (!(ret = (this->*renderFunctions[gameState])()) && !glfwWindowShouldClose(window));
	glfwTerminate();

	return ret;
}

GLint Game::gameActiveRender()
{
	isShowDebugInfo = false;
	isShowHUD = true;
	memset(keyPress, 0, sizeof(keyPress));//重置键盘
	glfwSetKeyCallback(window, gameActiveKeyCallback);
	glfwSetCursorPosCallback(window, gameActiveCursorCallback);
	glfwSetCursorPos(window, camera.getLastMousePosX(), camera.getLastMousePosY());
	glfwSetMouseButtonCallback(window, gameActiveMouseButtonCallback);

	WorldDefault worldDefault;
	worldDefault.init(options.maxLoadedChunksCount);
	worldDefault.updateChunks();
	currentBlockIndex = 1;//当前手中方块的索引

	/*============================================================*/
	//获取所有着色器变量位置
	GLint worldTextureBlocksLoc = -1;
	GLint worldMVPLoc = -1;
	GLint worldMVLoc = -1;
	GLint worldNormalMatLoc = -1;

	GLint textTextureTextLoc = -1;
	GLint textMVPLoc = -1;

	GLint GUITextureGUILoc = -1;
	GLint GUIMVPLoc = -1;

	GLint screenTextureScreenLoc = -1;
	GLint screenMVPLoc = -1;
	GLint screenWindowWidthLoc = -1;
	GLint screenWindowHeightLoc = -1;

	worldTextureBlocksLoc = worldProgram.getUniformLocation("texture_blocks");
	worldMVPLoc = worldProgram.getUniformLocation("MVP_vs");
	worldMVLoc = worldProgram.getUniformLocation("MV_vs");
	worldNormalMatLoc = worldProgram.getUniformLocation("normal_mat_vs");

	textTextureTextLoc = textProgram.getUniformLocation("texture_text");
	textMVPLoc = textProgram.getUniformLocation("MVP_vs");

	GUITextureGUILoc = GUIProgram.getUniformLocation("texture_GUI");
	GUIMVPLoc = GUIProgram.getUniformLocation("MVP_vs");

	screenTextureScreenLoc = screenProgram.getUniformLocation("texture_screen");
	screenMVPLoc = screenProgram.getUniformLocation("MVP_vs");
	screenWindowWidthLoc = screenProgram.getUniformLocation("window_width");
	screenWindowHeightLoc = screenProgram.getUniformLocation("window_height");

	TextRenderer::String textVersion = "版本:Alpha 0.5.0";
	GUIRenderer.textRenderer.getStringData(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, windowHeight - GUIRenderer.textRenderer.size.y, 0.0f), 1.0f, textVersion);

	DrawList crosshair;//准星
	crosshair.init(3);
	crosshair.data.resize(12);
	crosshair.data[0] = -0.03f*windowHeight / windowWidth;
	crosshair.data[1] = 0.0f;
	crosshair.data[2] = 0.0f;

	crosshair.data[3] = 0.03f*windowHeight / windowWidth;
	crosshair.data[4] = 0.0f;
	crosshair.data[5] = 0.0f;

	crosshair.data[6] = 0.0f;
	crosshair.data[7] = -0.03f;
	crosshair.data[8] = 0.0f;

	crosshair.data[9] = 0.0f;
	crosshair.data[10] = 0.03f;
	crosshair.data[11] = 0.0f;
	crosshair.updateData();
	crosshair.setVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 3, (GLvoid*)0);
	crosshair.setDrawMode(GL_LINES);
	crosshair.setDataStride(3);

	DrawList screenDrawList;
	screenDrawList.init(5);
	screenDrawList.data.push_back(0.0f);
	screenDrawList.data.push_back(0.0f);
	screenDrawList.data.push_back(0.0f);
	screenDrawList.data.push_back(0.0f);
	screenDrawList.data.push_back(0.0f);

	screenDrawList.data.push_back(windowWidth);
	screenDrawList.data.push_back(0.0f);
	screenDrawList.data.push_back(0.0f);
	screenDrawList.data.push_back(1.0f);
	screenDrawList.data.push_back(0.0f);

	screenDrawList.data.push_back(windowWidth);
	screenDrawList.data.push_back(windowHeight);
	screenDrawList.data.push_back(0.0f);
	screenDrawList.data.push_back(1.0f);
	screenDrawList.data.push_back(1.0f);

	screenDrawList.data.push_back(windowWidth);
	screenDrawList.data.push_back(windowHeight);
	screenDrawList.data.push_back(0.0f);
	screenDrawList.data.push_back(1.0f);
	screenDrawList.data.push_back(1.0f);

	screenDrawList.data.push_back(0.0f);
	screenDrawList.data.push_back(windowHeight);
	screenDrawList.data.push_back(0.0f);
	screenDrawList.data.push_back(0.0f);
	screenDrawList.data.push_back(1.0f);

	screenDrawList.data.push_back(0.0f);
	screenDrawList.data.push_back(0.0f);
	screenDrawList.data.push_back(0.0f);
	screenDrawList.data.push_back(0.0f);
	screenDrawList.data.push_back(0.0f);
	screenDrawList.setDataStride(5);
	screenDrawList.setDrawMode(GL_TRIANGLES);
	screenDrawList.setVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 5, (GLvoid*)0);
	screenDrawList.setVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 5, (GLvoid*)(3 * sizeof(GLfloat)));
	screenDrawList.updateData();


	GUILabel labelInfo;

	FrameBuffer fbo;
	if (fbo.init())
	{
		return 1;
	}

	RenderBuffer rboDepthStencil;
	if (rboDepthStencil.init())
	{
		return 1;
	}
	rboDepthStencil.renderbufferStorage(GL_DEPTH24_STENCIL8, windowWidth, windowHeight, GL_RENDERBUFFER);

	Texture2D textureColor;
	if (textureColor.init(GL_TEXTURE0))
	{
		return 1;
	}
	textureColor.texImage2D(0, GL_RGB, windowWidth, windowHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	textureColor.texParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	textureColor.texParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	fbo.framebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureColor, 0);
	fbo.framebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboDepthStencil);

	if (fbo.checkFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		return 1;
	}

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	double currentTime = glfwGetTime();
	double lastTime = currentTime;

	while (gameState == GAME_STATE_ACTIVE)
	{
		glfwPollEvents();
		currentTime = glfwGetTime();
		float deltaTime = float(currentTime - lastTime);
		camera.setMoveSpeedS(deltaTime*camera.getMoveSpeed());
		gameActiveControl();

		fbo.bind(GL_DRAW_FRAMEBUFFER);
		/*============================================================*/
		PipeLine::clearColor(0.4941176470588235f, 0.7294117647058824f, 1.0f, 1.0f);
		PipeLine::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		/*============================================================*/
		//渲染世界
		worldProgram.use();
		PipeLine::frontFace(GL_CCW);
		PipeLine::cullFace(GL_BACK);
		PipeLine::enable(GL_CULL_FACE);
		PipeLine::enable(GL_DEPTH_TEST);
		PipeLine::enable(GL_BLEND);
		PipeLine::blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		PipeLine::lineWidth(2.0f);
		PipeLine::pointSize(2.0f);
		PipeLine::alphaFunc(GL_GREATER, 0.45f);


		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		view = glm::lookAt(camera.getPosition(), camera.getPosition() + camera.getTarget(), camera.getUp());
		projection = glm::perspective(options.FOV, windowWidth / windowHeight, 0.01f, 128.0f);
		model;
		
		glm::mat4 MVP = projection*view*model;
		glm::mat4 MV = model;
		glm::mat4 MVNormal = glm::mat4(glm::mat3(glm::transpose(glm::inverse(model))));

		worldProgram.uniformMatrix4fv(worldMVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));
		worldProgram.uniformMatrix4fv(worldMVLoc, 1, GL_FALSE, glm::value_ptr(MV));
		worldProgram.uniformMatrix4fv(worldNormalMatLoc, 1, GL_FALSE, glm::value_ptr(MVNormal));

		blocksTexture.bind(worldTextureBlocksLoc);
		worldDefault.draw();
		worldDefault.updateDrawChunks(camera.getPosition());
		if (mouseButtonPress[GLFW_MOUSE_BUTTON_LEFT])
		{
			destroyBlock(worldDefault);
		}
		else if (mouseButtonPress[GLFW_MOUSE_BUTTON_RIGHT])
		{
			setBlock(worldDefault);
		}

		/*离屏渲染*/
		FrameBuffer::resetFrameBuffer();
		PipeLine::clearColor(0.4941176470588235f, 0.7294117647058824f, 1.0f, 1.0f);
		PipeLine::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		screenProgram.use();

		projection = glm::ortho(0.0f, windowWidth, 0.0f, windowHeight);
		screenProgram.uniformMatrix4fv(screenMVPLoc, 1, GL_FALSE, glm::value_ptr(projection));
		screenProgram.uniform1i(screenWindowWidthLoc, GLint(windowWidth));
		screenProgram.uniform1i(screenWindowHeightLoc, GLint(windowHeight));

		textureColor.bind(screenTextureScreenLoc);

		screenDrawList.draw();
		/**/

		//渲染准星
		if (isShowHUD)
		{
			whiteProgram.use();
			PipeLine::disable(GL_DEPTH_TEST);
			crosshair.draw();
		}

		//绘制文字

		//绘制GUI
		PipeLine::disable(GL_DEPTH_TEST);
		GUIProgram.use();

		widgetsTexture.bind(GUITextureGUILoc);

		projection = glm::ortho(0.0f, windowWidth, 0.0f, windowHeight);
		GUIProgram.uniformMatrix4fv(GUIMVPLoc, 1, GL_FALSE, glm::value_ptr(projection));
		GUIRenderer.prepare(window, mouseButtonPress);

		if (isShowDebugInfo)
		{
			stringstream ss;
			ss.precision(4);
			ss.setf(ios::showpoint);
			ss.setf(ios::fixed);
			ss << "版本：Alpha 0.5.0" << "\n"
				<< "当前方块 : " << worldDefault.blocks.data[currentBlockIndex]->getName() << "\n"
				<< "坐标 : " << camera.getPosition().x << " " << camera.getPosition().y << " " << camera.getPosition().z << "\n"
				<< "已加载Chunk : " << worldDefault.chunksSortedIterators.size();
			if (GUIRenderer.label(labelInfo,
				ss.str(),
				glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
				1.0f,
				glm::vec2(0.0f, windowHeight - GUIRenderer.textRenderer.getStringHeight(ss.str()) - 20.0f),
				glm::vec2(GUIRenderer.textRenderer.getStringWidth(ss.str()) + 20.0f, GUIRenderer.textRenderer.getStringHeight(ss.str()) + 20.0f),
				glm::vec4(0.0f, 0.0f, 0.0f, 0.5f)))
			{

			}
		}

		GUIRenderer.finish();
		GUIRenderer.drawWidgets();
		GUIRenderer.drawTexts(GUITextureGUILoc);

		/*============================================================*/
		glfwSwapBuffers(window);
		lastTime = currentTime;
	}
	
	Texture2D::resetTexture();
	StdShaderProgram::resetProgram();
	FrameBuffer::resetFrameBuffer();
	RenderBuffer::resetRenderBuffer();
	DrawList::resetDrawList();

	return 0;
}
GLint Game::gameMenuRender()
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	memset(keyPress, 0, sizeof(keyPress));
	glfwSetKeyCallback(window, gameMenuKeyCallback);
	glfwSetCursorPosCallback(window, gameMenuCursorCallback);
	glfwSetCursorPos(window, windowWidth / 2.0, windowHeight / 2.0);
	glfwSetMouseButtonCallback(window, gameMenuMouseButtonCallback);

	GLint logoTextureMainLoc = -1;
	GLint logoMVPLoc = -1;

	GLint backgroundTextureMainLoc = -1;
	GLint backgroundMVPLoc = -1;

	GLint textTextureTextLoc = -1;
	GLint textMVPLoc = -1;

	GLint textMSDFTextureTextLoc = -1;
	GLint textMSDFMVPLoc = -1;

	GLint GUITextureGUILoc = -1;
	GLint GUIMVPLoc = -1;

	logoTextureMainLoc = logoProgram.getUniformLocation("texture_main");
	logoMVPLoc = logoProgram.getUniformLocation("MVP_vs");

	backgroundTextureMainLoc = backgroundProgram.getUniformLocation("texture_main");
	backgroundMVPLoc = backgroundProgram.getUniformLocation("MVP_vs");

	textTextureTextLoc = textProgram.getUniformLocation("texture_text");
	textMVPLoc = textProgram.getUniformLocation("MVP_vs");

	textMSDFTextureTextLoc = textMSDFProgram.getUniformLocation("texture_text");
	textMSDFMVPLoc = textMSDFProgram.getUniformLocation("MVP_vs");

	GUITextureGUILoc = GUIProgram.getUniformLocation("texture_GUI");
	GUIMVPLoc = GUIProgram.getUniformLocation("MVP_vs");

	/*加载界面*/
	PipeLine::clearColor(0.3f, 0.3f, 0.3f, 1.0f);
	PipeLine::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	PipeLine::enable(GL_CULL_FACE);
	PipeLine::enable(GL_BLEND);
	PipeLine::enable(GL_LINE_SMOOTH);
	PipeLine::frontFace(GL_CCW);
	PipeLine::cullFace(GL_BACK);
	PipeLine::blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	PipeLine::lineWidth(2.0f);
	PipeLine::alphaFunc(GL_GREATER, 0.5f);

	GUIProgram.use();

	widgetsTexture.bind(GUITextureGUILoc);

	glm::mat4 projection;
	projection = glm::ortho(0.0f, windowWidth, 0.0f, windowHeight);
	GUIProgram.uniformMatrix4fv(GUIMVPLoc, 1, GL_FALSE, glm::value_ptr(projection));
	GUIRenderer.prepare(window, mouseButtonPress);

	GUIRenderer.texts("加载中。。。", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(windowWidth / 2.0f - GUIRenderer.textRenderer.getStringWidth("加载中。。。") / 2.0f, 42.0f), 1.0f);
	GUIRenderer.finish();
	GUIRenderer.drawWidgets();
	GUIRenderer.drawTexts(GUITextureGUILoc);

	StdShaderProgram::resetProgram();
	glfwSwapBuffers(window);
	//
#ifndef _DEBUG
	for (wchar_t ch = 33; ch < 127; ++ch)
	{
		if (GUIRenderer.textRenderer.characters.find(ch) == GUIRenderer.textRenderer.characters.end())
		{
			GUIRenderer.textRenderer.addCharacter(ch);
		}
	}

	for (wchar_t ch = 0x4E00; ch < 0x9FA5; ++ch)
	{
		if (GUIRenderer.textRenderer.characters.find(ch) == GUIRenderer.textRenderer.characters.end())
		{
			GUIRenderer.textRenderer.addCharacter(ch);
		}
	}
#endif

	GUIPushButton pushButtonOption;
	GUIPushButton pushButtonStart;
	GUIPushButton pushButtonQuit;
	/*背景图片*/
	DrawList background;
	background.init(5);
	background.data.push_back(-1.0f);
	background.data.push_back(-1.0f);
	background.data.push_back(0.0f);
	background.data.push_back(0.0f);
	background.data.push_back(1.0f);

	background.data.push_back(1.0f);
	background.data.push_back(-1.0f);
	background.data.push_back(0.0f);
	background.data.push_back(1.0f);
	background.data.push_back(1.0f);

	background.data.push_back(1.0f);
	background.data.push_back(1.0f);
	background.data.push_back(0.0f);
	background.data.push_back(1.0f);
	background.data.push_back(0.0f);

	background.data.push_back(1.0f);
	background.data.push_back(1.0f);
	background.data.push_back(0.0f);
	background.data.push_back(1.0f);
	background.data.push_back(0.0f);

	background.data.push_back(-1.0f);
	background.data.push_back(1.0f);
	background.data.push_back(0.0f);
	background.data.push_back(0.0f);
	background.data.push_back(0.0f);

	background.data.push_back(-1.0f);
	background.data.push_back(-1.0f);
	background.data.push_back(0.0f);
	background.data.push_back(0.0f);
	background.data.push_back(1.0f);

	background.setDataStride(5);
	background.setVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 5, (GLvoid*)0);
	background.setVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 5, (GLvoid*)(3 * sizeof(GLfloat)));
	background.updateData();
	/*LOGO*/
	DrawList gameLogo;
	gameLogo.init(5);
	gameLogo.data.push_back(-1.6f*windowHeight / windowWidth);
	gameLogo.data.push_back(0.1f);
	gameLogo.data.push_back(0.0f);
	gameLogo.data.push_back(0.0f);
	gameLogo.data.push_back(1.0f);

	gameLogo.data.push_back(1.6f*windowHeight / windowWidth);
	gameLogo.data.push_back(0.1f);
	gameLogo.data.push_back(0.0f);
	gameLogo.data.push_back(1.0f);
	gameLogo.data.push_back(1.0f);

	gameLogo.data.push_back(1.6f*windowHeight / windowWidth);
	gameLogo.data.push_back(0.9f);
	gameLogo.data.push_back(0.0f);
	gameLogo.data.push_back(1.0f);
	gameLogo.data.push_back(0.0f);

	gameLogo.data.push_back(1.6f*windowHeight / windowWidth);
	gameLogo.data.push_back(0.9f);
	gameLogo.data.push_back(0.0f);
	gameLogo.data.push_back(1.0f);
	gameLogo.data.push_back(0.0f);

	gameLogo.data.push_back(-1.6f*windowHeight / windowWidth);
	gameLogo.data.push_back(0.9f);
	gameLogo.data.push_back(0.0f);
	gameLogo.data.push_back(0.0f);
	gameLogo.data.push_back(0.0f);

	gameLogo.data.push_back(-1.6f*windowHeight / windowWidth);
	gameLogo.data.push_back(0.1f);
	gameLogo.data.push_back(0.0f);
	gameLogo.data.push_back(0.0f);
	gameLogo.data.push_back(1.0f);

	gameLogo.setDataStride(5);
	gameLogo.setVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 5, (GLvoid*)0);
	gameLogo.setVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 5, (GLvoid*)(3 * sizeof(GLfloat)));
	gameLogo.updateData();

	double currentTime = glfwGetTime();
	double lastTime = currentTime;

	while (gameState == GAME_STATE_MENU&&!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		gameMenuControl();
		currentTime = glfwGetTime();
		float deltaTime = float(currentTime - lastTime);
		/*============================================================*/
		PipeLine::clearColor(0.0f, 0.0f, 0.0f, 1.0f);
		PipeLine::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		PipeLine::disable(GL_DEPTH_TEST);
		PipeLine::enable(GL_CULL_FACE);
		PipeLine::enable(GL_BLEND);
		PipeLine::enable(GL_LINE_SMOOTH);
		PipeLine::frontFace(GL_CCW);
		PipeLine::cullFace(GL_BACK);
		PipeLine::blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		PipeLine::lineWidth(2.0f);
		PipeLine::alphaFunc(GL_GREATER, 0.5f);

		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		glm::mat4 MVP = projection*view*model;
		//绘制背景
		backgroundProgram.use();

		backgroundProgram.uniformMatrix4fv(backgroundMVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));

		backgroundTexture.bind(backgroundTextureMainLoc);
		background.draw();
		//绘制Logo
		logoProgram.use();
		glPolygonOffset(0.0f, 1.0f);

		logoProgram.uniformMatrix4fv(logoMVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));

		logoTexture.bind(logoTextureMainLoc);
		gameLogo.draw();

		//绘制GUI
		GUIProgram.use();

		widgetsTexture.bind(GUITextureGUILoc);

		projection = glm::ortho(0.0f, windowWidth, 0.0f, windowHeight);
		GUIProgram.uniformMatrix4fv(GUIMVPLoc, 1, GL_FALSE, glm::value_ptr(projection));
		GUIRenderer.prepare(window, mouseButtonPress);

		GUIRenderer.texts("Powered By Occlusion Engine", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(windowWidth - GUIRenderer.textRenderer.getStringWidth("Powered By Occlusion Engine"), 10.0f), 1.0f);
		GUIRenderer.texts("Version：Alpha 0.6.0 Preview", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 10.0f), 1.0f);

		GUIRenderer.rectangle(glm::vec2(0.0f, 60.0f), glm::vec2(windowWidth, 200.0f), glm::vec4(0.0f, 0.0f, 0.0f, 0.5f));
		if (GUIRenderer.pushButton(pushButtonOption, "选 项", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, glm::vec2(windowWidth / 2.0f - 385.0f, 80.0f), glm::vec2(250.0f, 160.0f)) == GUIWidget::GUIWidgetState::Click)
		{
			GUIRenderer.finish();
			gameMenuOptionsRender();
			GUIRenderer.prepare(window, mouseButtonPress);
		}
		if (GUIRenderer.pushButton(pushButtonStart, "开 始", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, glm::vec2(windowWidth / 2.0f - 125.0f, 80.0f), glm::vec2(250.0f, 160.0f)) == GUIWidget::GUIWidgetState::Click)
		{
			gameState = GAME_STATE_ACTIVE;
		}
		if (GUIRenderer.pushButton(pushButtonQuit, "退 出", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, glm::vec2(windowWidth / 2.0f + 135.0f, 80.0f), glm::vec2(250.0f, 160.0f)) == GUIWidget::GUIWidgetState::Click)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		GUIRenderer.finish();
		GUIRenderer.drawWidgets();
		GUIRenderer.drawTexts(GUITextureGUILoc);
		//textMSDFProgram.use();
		//textMSDFProgram.uniformMatrix4fv(textMSDFMVPLoc, 1, GL_FALSE, glm::value_ptr(projection));
		//GUIRenderer.drawTexts(textMSDFTextureTextLoc);
		
		StdShaderProgram::resetProgram();
		/*============================================================*/
		glfwSwapBuffers(window);
		lastTime = currentTime;
	}

	return 0;
}

GLint Game::gameMenuOptionsRender()
{
	GLint logoTextureMainLoc = -1;
	GLint logoModelLoc = -1;
	GLint logoViewLoc = -1;
	GLint logoMVPLoc = -1;

	GLint textTextureTextLoc = -1;
	GLint textMVPLoc = -1;

	GLint textMSDFTextureTextLoc = -1;
	GLint textMSDFMVPLoc = -1;

	GLint GUITextureGUILoc = -1;
	GLint GUIMVPLoc = -1;

	logoTextureMainLoc = logoProgram.getUniformLocation("texture_main");
	logoModelLoc = logoProgram.getUniformLocation("model_vs");
	logoViewLoc = logoProgram.getUniformLocation("view_vs");
	logoMVPLoc = logoProgram.getUniformLocation("MVP_vs");

	textTextureTextLoc = textProgram.getUniformLocation("texture_text");
	textMVPLoc = textProgram.getUniformLocation("MVP_vs");

	textMSDFTextureTextLoc = textMSDFProgram.getUniformLocation("texture_text");
	textMSDFMVPLoc = textMSDFProgram.getUniformLocation("MVP_vs");

	GUITextureGUILoc = GUIProgram.getUniformLocation("texture_GUI");
	GUIMVPLoc = GUIProgram.getUniformLocation("MVP_vs");

	GUILabel labelMenuOptions;
	GUILabel labelMouseSpeed;
	GUISlider sliderMouseSpeed;
	GUILabel labelMoveSpeed;
	GUISlider sliderMoveSpeed;
	GUILabel labelFOV;
	GUISlider sliderFOV;
	GUILabel labelMaxLoadedChunksCount;
	GUISlider sliderMaxLoadedChunksCount;
	GUIPushButton pushButtonBack;
	GUIPushButton pushButtonContinue;

	double currentTime = glfwGetTime();
	double lastTime = currentTime;

	while (gameState == GAME_STATE_MENU&&!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		gameMenuControl();
		currentTime = glfwGetTime();
		float deltaTime = float(currentTime - lastTime);
		/*============================================================*/
		PipeLine::clearColor(0.4941176470588235f, 0.7294117647058824f, 1.0f, 1.0f);
		PipeLine::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		PipeLine::enable(GL_DEPTH_TEST);
		PipeLine::enable(GL_CULL_FACE);
		PipeLine::enable(GL_BLEND);
		PipeLine::enable(GL_LINE_SMOOTH);
		PipeLine::frontFace(GL_CCW);
		PipeLine::cullFace(GL_BACK);
		PipeLine::blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		PipeLine::lineWidth(2.0f);
		PipeLine::alphaFunc(GL_GREATER, 0.5f);
		logoProgram.use();

		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;

		//绘制GUI
		PipeLine::disable(GL_DEPTH_TEST);
		GUIProgram.use();

		widgetsTexture.bind(GUITextureGUILoc);

		projection = glm::ortho(0.0f, windowWidth, 0.0f, windowHeight);
		GUIProgram.uniformMatrix4fv(GUIMVPLoc, 1, GL_FALSE, glm::value_ptr(projection));
		GUIRenderer.prepare(window, mouseButtonPress);

		/**/
		if (GUIRenderer.label(labelMenuOptions,
			"选 项",
			glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
			1.0f,
			glm::vec2(windowWidth / 2.0 - 50.0f, windowHeight - 32.0f),
			glm::vec2(100.0f, 32.0f),
			glm::vec4(0.0f, 0.0f, 0.0f, 0.5f)))
		{

		}
		/**/
		GUIRenderer.rectangle(glm::vec2(windowWidth / 2.0f, 20.0f), glm::vec2(2.0f, windowHeight - 80.0f), glm::vec4(0.0f, 0.0f, 0.0f, 0.5f));
		/**/
		if (GUIRenderer.label(labelMouseSpeed,
			"鼠标速度",
			glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
			1.0f,
			glm::vec2(windowWidth / 2.0f + 10.0f, windowHeight - 88.0f),
			glm::vec2(GUIRenderer.textRenderer.getStringWidth("鼠标速度") + 10.0f, 32.0f),
			glm::vec4(0.0f, 0.0f, 0.0f, 0.5f)))
		{

		}
		if (GUIRenderer.slider<GLfloat>(sliderMouseSpeed,
			glm::vec2(windowWidth / 2.0f + 10.0f, windowHeight - 100.0f),
			glm::vec2(300.0f, 4.0f),
			0.2f,
			1.0f,
			options.mouseSpeed) == GUIWidget::GUIWidgetState::Change)
		{
			camera.setMouseSpeed(options.mouseSpeed);
		}
		//
		if (GUIRenderer.label(labelMoveSpeed,
			"移动速度",
			glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
			1.0f,
			glm::vec2(windowWidth / 2.0f + 10.0f, windowHeight - 148.0f),
			glm::vec2(GUIRenderer.textRenderer.getStringWidth("移动速度") + 10.0f, 32.0f),
			glm::vec4(0.0f, 0.0f, 0.0f, 0.5f)))
		{

		}
		if (GUIRenderer.slider<GLint>(sliderMoveSpeed,
			glm::vec2(windowWidth / 2.0f + 10.0f, windowHeight - 160.0f),
			glm::vec2(300.0f, 4.0f),
			10,
			40,
			options.moveSpeed) == GUIWidget::GUIWidgetState::Change)
		{
			camera.setMoveSpeed(static_cast<GLfloat>(options.moveSpeed));
		}
		//
		if (GUIRenderer.label(labelFOV,
			"FOV",
			glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
			1.0f,
			glm::vec2(windowWidth / 2.0f + 10.0f, windowHeight - 208.0f),
			glm::vec2(GUIRenderer.textRenderer.getStringWidth("FOV") + 10.0f, 32.0f),
			glm::vec4(0.0f, 0.0f, 0.0f, 0.5f)))
		{

		}
		if (GUIRenderer.slider<GLfloat>(sliderFOV,
			glm::vec2(windowWidth / 2.0f + 10.0f, windowHeight - 220.0f),
			glm::vec2(300.0f, 4.0f),
			45.0f,
			71.0f,
			options.FOV) == GUIWidget::GUIWidgetState::Change)
		{

		}
		//
		if (GUIRenderer.label(labelMaxLoadedChunksCount,
			"最大加载Chunk数量",
			glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
			1.0f,
			glm::vec2(windowWidth / 2.0f + 10.0f, windowHeight - 268.0f),
			glm::vec2(GUIRenderer.textRenderer.getStringWidth("最大加载Chunk数量") + 10.0f, 32.0f),
			glm::vec4(0.0f, 0.0f, 0.0f, 0.5f)))
		{

		}
		if (GUIRenderer.slider<GLint>(sliderMaxLoadedChunksCount,
			glm::vec2(windowWidth / 2.0f + 10.0f, windowHeight - 280.0f),
			glm::vec2(300.0f, 4.0f),
			256,
			1024,
			options.maxLoadedChunksCount) == GUIWidget::GUIWidgetState::Change)
		{

		}
		//
		if (GUIRenderer.pushButton(pushButtonBack,
			"返 回",
			glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
			1.0f,
			glm::vec2(10.0f, 10.0f),
			glm::vec2(100.0f, 50.0f)) == GUIWidget::GUIWidgetState::Click)
		{
			GUIRenderer.finish();
			break;
		}
		if (GUIRenderer.pushButton(pushButtonContinue,
			"继 续",
			glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
			1.0f,
			glm::vec2(windowWidth - 110.0f, 10.0f),
			glm::vec2(100.0f, 50.0f)) == GUIWidget::GUIWidgetState::Click)
		{
			GUIRenderer.finish();
			break;
		}
		GUIRenderer.finish();
		GUIRenderer.drawWidgets();
		GUIRenderer.drawTexts(GUITextureGUILoc);
		//textMSDFProgram.use();
		//textMSDFProgram.uniformMatrix4fv(textMSDFMVPLoc, 1, GL_FALSE, glm::value_ptr(projection));
		//GUIRenderer.drawTexts(textMSDFTextureTextLoc);

		StdShaderProgram::resetProgram();
		/*============================================================*/
		glfwSwapBuffers(window);
		lastTime = currentTime;
	}

	return 0;
}
/*控制*/

// GAME_STATE_ACTIVE
inline GLvoid Game::gameActiveControl()
{
	/*==========键盘==========*/
	/*相机移动*/
	if (keyPress[GLFW_KEY_W])
	{
		camera.moveForward();
	}
	if (keyPress[GLFW_KEY_S])
	{
		camera.moveBackward();
	}
	if (keyPress[GLFW_KEY_A])
	{
		camera.moveLeft();
	}
	if (keyPress[GLFW_KEY_D])
	{
		camera.moveRight();
	}
	if (keyPress[GLFW_KEY_SPACE])
	{
		camera.moveUp();
	}
	if (keyPress[GLFW_KEY_C])
	{
		camera.moveDown();
	}
	/*方块选择*/
	if (keyPress[GLFW_KEY_1])
	{
		currentBlockIndex = 1;
	}
	if (keyPress[GLFW_KEY_2])
	{
		currentBlockIndex = 2;
	}
	if (keyPress[GLFW_KEY_3])
	{
		currentBlockIndex = 3;
	}
	if (keyPress[GLFW_KEY_4])
	{
		currentBlockIndex = 4;
	}
	if (keyPress[GLFW_KEY_ESCAPE])
	{
		gameState = GAME_STATE_MENU;
	}
	/*==========鼠标==========*/


}

GLvoid Game::gameActiveKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{

	if (key == GLFW_KEY_H && action == GLFW_PRESS)
	{
		static GLboolean isCursorEnable = GL_FALSE;
		isCursorEnable = !isCursorEnable;
		if (isCursorEnable)
		{
#ifdef _DEBUG
			cout << "指针可用！" << endl;
#endif
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else
		{
#ifdef _DEBUG
			cout << "指针不可用！" << endl;
#endif
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}


	if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
	{
		isShowHUD = !isShowHUD;
	}

	if (key == GLFW_KEY_F2 && action == GLFW_PRESS)
	{
		stringstream ss;
		time_t curTime = time(nullptr);
		struct tm* current_time = localtime(&curTime);
		ss <<"Screenshots/"
			<< (current_time->tm_year + 1900) 
			<< "-" << (current_time->tm_mon + 1) 
			<< "-" << (current_time->tm_mday) 
			<< "-" << (current_time->tm_hour) 
			<< "-" << (current_time->tm_min) 
			<< "-" << (current_time->tm_sec) << ".bmp";
		GLuint width = GLuint(windowWidth);
		GLuint height = GLuint(windowHeight);
		/*
		GLubyte * pixels = new GLubyte[8 * width * height];
		memset(pixels, 0, 8 * width * height*sizeof(GLubyte));
		*/
		vector<GLubyte> pixelData(width * height * 3);

		glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, &pixelData[0]);
		for (GLuint i = 0; i < height / 2; i++)
		{
			for (GLuint j = 0; j < width; j++)
			{
				
				GLubyte temp[3] = { 0 };
				temp[0] = pixelData[(i * width + j) * 3 + 0];
				temp[1] = pixelData[(i * width + j) * 3 + 1];
				temp[2] = pixelData[(i * width + j) * 3 + 2];

				pixelData[(i * width + j) * 3 + 0] = pixelData[((height - i - 1) * width + j) * 3 + 0];
				pixelData[(i * width + j) * 3 + 1] = pixelData[((height - i - 1) * width + j) * 3 + 1];
				pixelData[(i * width + j) * 3 + 2] = pixelData[((height - i - 1) * width + j) * 3 + 2];

				pixelData[((height - i - 1) * width + j) * 3 + 0] = temp[0];
				pixelData[((height - i - 1) * width + j) * 3 + 1] = temp[1];
				pixelData[((height - i - 1) * width + j) * 3 + 2] = temp[2];
				
			}
		}
		
		SOIL_save_image(ss.str().c_str(), SOIL_SAVE_TYPE_BMP, width, height, SOIL_LOAD_RGB, &pixelData[0]);
	}


	if (key == GLFW_KEY_F3 && action == GLFW_PRESS)
	{
		isShowDebugInfo = !isShowDebugInfo;
	}

	/**/
	if (action == GLFW_PRESS)
	{
		keyPress[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		keyPress[key] = false;
	}

}

GLvoid Game::gameActiveCursorCallback(GLFWwindow* window, GLdouble xpos, GLdouble ypos)
{
	camera.viewRotate(xpos, ypos);
}

GLvoid Game::gameActiveMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		mouseButtonPress[button] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		mouseButtonPress[button] = false;
	}


}

GLvoid Game::destroyBlock(World & world)
{
	mouseButtonPress[GLFW_MOUSE_BUTTON_LEFT] = GL_FALSE;

	glm::vec3 lastBlockLocationf = camera.getPosition();

	for (GLfloat i = 1.0f; i < 16.0f; i += 0.01f)
	{
		glm::vec3 blockLocationf = camera.getPosition() + camera.getTarget()*i;
		if (blockLocationf.x < 0.0f)
		{
			blockLocationf.x -= 1.0f;
		}
		if (blockLocationf.y < 0.0f)
		{
			blockLocationf.y -= 1.0f;
		}
		if (blockLocationf.z < 0.0f)
		{
			blockLocationf.z -= 1.0f;
		}

		if (glm::ivec3(blockLocationf) == glm::ivec3(lastBlockLocationf))
		{
			lastBlockLocationf = blockLocationf;
			continue;
		}
		LocationInChunk blockLocationInChunk = world.getLocationInChunk(blockLocationf);

		if (blockLocationInChunk.iterator != world.chunks.end())
		{
			if ((*blockLocationInChunk.iterator).blockID[blockLocationInChunk.locationInArray.x][blockLocationInChunk.locationInArray.y][blockLocationInChunk.locationInArray.z])
			{
#ifdef _DEBUG
				cout << "方块摧毁！" << endl;
				cout << blockLocationInChunk.index << " " << blockLocationInChunk.locationInArray.x << " " << blockLocationInChunk.locationInArray.y << " " << blockLocationInChunk.locationInArray.z << endl;
#endif
				(*blockLocationInChunk.iterator).blockID[blockLocationInChunk.locationInArray.x][blockLocationInChunk.locationInArray.y][blockLocationInChunk.locationInArray.z] = 0;
				world.updateChunk(blockLocationInChunk.iterator);

				updateNearChunks(world, blockLocationInChunk);
				break;
			}

		}
	}

}
GLvoid Game::setBlock(World & world)
{
	mouseButtonPress[GLFW_MOUSE_BUTTON_RIGHT] = GL_FALSE;

	glm::vec3 lastBlockLocationf = camera.getPosition() + camera.getTarget()*1.0f;

	for (GLfloat i = 1.0f; i < 16.0f; i += 0.01f)
	{
		glm::vec3 blockLocationf = camera.getPosition() + camera.getTarget()*i;
		if (blockLocationf.x < 0.0f)
		{
			blockLocationf.x -= 1.0f;
		}
		if (blockLocationf.y < 0.0f)
		{
			blockLocationf.y -= 1.0f;
		}
		if (blockLocationf.z < 0.0f)
		{
			blockLocationf.z -= 1.0f;
		}

		if (glm::ivec3(blockLocationf) == glm::ivec3(lastBlockLocationf))
		{
			lastBlockLocationf = blockLocationf;
			continue;
		}
		LocationInChunk blockLocationInChunk = world.getLocationInChunk(blockLocationf);

		if (blockLocationInChunk.iterator != world.chunks.end())
		{
			if ((*blockLocationInChunk.iterator).blockID[blockLocationInChunk.locationInArray.x][blockLocationInChunk.locationInArray.y][blockLocationInChunk.locationInArray.z])
			{
				LocationInChunk lastBlockLocationInChunk = world.getLocationInChunk(lastBlockLocationf);

				if (lastBlockLocationInChunk.iterator != world.chunks.end())
				{
#ifdef _DEBUG
					cout << "方块放置！" << endl;
					cout << lastBlockLocationInChunk.index << " " << lastBlockLocationInChunk.locationInArray.x << " " << lastBlockLocationInChunk.locationInArray.y << " " << lastBlockLocationInChunk.locationInArray.z << endl;
#endif
					(*lastBlockLocationInChunk.iterator).blockID[lastBlockLocationInChunk.locationInArray.x][lastBlockLocationInChunk.locationInArray.y][lastBlockLocationInChunk.locationInArray.z] = currentBlockIndex;
					world.updateChunk(lastBlockLocationInChunk.iterator);

					updateNearChunks(world, lastBlockLocationInChunk);

					break;
				}

			}
			else
			{
				lastBlockLocationf = blockLocationf;
			}

		}
	}
}
// GAME_STATE_MENU

GLvoid Game::gameMenuKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS)
	{
		keyPress[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		keyPress[key] = false;
	}
}

GLvoid Game::gameMenuControl()
{

}

GLvoid Game::gameMenuCursorCallback(GLFWwindow* window, GLdouble xpos, GLdouble ypos)
{

}

GLvoid Game::gameMenuMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		mouseButtonPress[button] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		mouseButtonPress[button] = false;
	}
}

/*其 他*/

GLvoid Game::updateNearChunks(World & world, const LocationInChunk & origin)
{
	if (origin.index == -1)
	{
		return;
	}
	glm::ivec3 chunkLocation;
	vector<Chunk>::iterator chunkNeedUpdateIterator = world.chunks.end();

	if (origin.locationInArray.x == 0)
	{
		chunkLocation = (*origin.iterator).location;
		chunkLocation.x--;
		chunkNeedUpdateIterator = world.getChunkIterator(chunkLocation);
		if (chunkNeedUpdateIterator != world.chunks.end())
		{
			world.updateChunk(chunkNeedUpdateIterator);
		}
	}
	else if (origin.locationInArray.x == DEFAULT_CHUNK_SIZE_X - 1)
	{
		chunkLocation = (*origin.iterator).location;
		chunkLocation.x++;
		chunkNeedUpdateIterator = world.getChunkIterator(chunkLocation);
		if (chunkNeedUpdateIterator != world.chunks.end())
		{
			world.updateChunk(chunkNeedUpdateIterator);
		}
	}

	if (origin.locationInArray.y == 0)
	{
		chunkLocation = (*origin.iterator).location;
		chunkLocation.y--;
		chunkNeedUpdateIterator = world.getChunkIterator(chunkLocation);
		if (chunkNeedUpdateIterator != world.chunks.end())
		{
			world.updateChunk(chunkNeedUpdateIterator);
		}
	}
	else if (origin.locationInArray.y == DEFAULT_CHUNK_SIZE_Y - 1)
	{
		chunkLocation = (*origin.iterator).location;
		chunkLocation.y++;
		chunkNeedUpdateIterator = world.getChunkIterator(chunkLocation);
		if (chunkNeedUpdateIterator != world.chunks.end())
		{
			world.updateChunk(chunkNeedUpdateIterator);
		}
	}

	if (origin.locationInArray.z == 0)
	{
		chunkLocation = (*origin.iterator).location;
		chunkLocation.z--;
		chunkNeedUpdateIterator = world.getChunkIterator(chunkLocation);
		if (chunkNeedUpdateIterator != world.chunks.end())
		{
			world.updateChunk(chunkNeedUpdateIterator);
		}
	}
	else if (origin.locationInArray.z == DEFAULT_CHUNK_SIZE_Z - 1)
	{
		chunkLocation = (*origin.iterator).location;
		chunkLocation.z++;
		chunkNeedUpdateIterator = world.getChunkIterator(chunkLocation);
		if (chunkNeedUpdateIterator != world.chunks.end())
		{
			world.updateChunk(chunkNeedUpdateIterator);
		}
	}
}

Game::~Game()
{
}
