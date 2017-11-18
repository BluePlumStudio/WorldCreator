#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>

#include "DrawList.h"
#include "TextRenderer.h"
#include "GUIWidget.h"
#include "GUIPushButton.h"
#include "GUISlider.h"
#include "GUILabel.h"

//#include "GUIRenderer.cpp"

class IMGUIRenderer
{
public:

	IMGUIRenderer();
	GLint init(const GLchar * fontPath, GLuint positionLocation, GLuint texCoordsLocation, GLuint colorLocation, FT_UInt width = 0, FT_UInt height = 16);
	//GLboolean isInside(GUIState & state, glm::vec2 & position, glm::vec2 & size);
	
	GLvoid texts(std::string caption, glm::vec4 & color, glm::vec2 & position, GLfloat scale);

	GLvoid rectangle(glm::vec2 & position, glm::vec2 & size, glm::vec4 & color);

	GUIWidget::GUIWidgetState pushButton(GUIPushButton & pushButton, std::string caption, glm::vec4 & captionColor, GLfloat captionScale, glm::vec2 & position, glm::vec2 & size);
	
	template<typename T>
	GUIWidget::GUIWidgetState slider(GUISlider & slider, glm::vec2 & position, glm::vec2 & size, T min, T max, T & value)
	{
		GUIWidget::GUIWidgetState widgetState = GUIWidget::GUIWidgetState::Normal;
		GLuint id = slider.getID();
		glm::vec2 sliderPosition = { 0.0f, 0.0f };

		if (value > max)
		{
			value = max;
		}
		else if (value < min)
		{
			value = min;
		}

		sliderPosition.x = position.x + static_cast<GLfloat>(value - min) / (max - min)*size.x + 4.0f;
		sliderPosition.y = position.y;

		if (GUISlider::isInside(state, position, size + glm::vec2(GUI_SLIDER_WIDTH, 0.0f)) || 
			GUISlider::isInside(state, sliderPosition - glm::vec2(GUI_SLIDER_WIDTH / 2.0f, GUI_SLIDER_EXTENDED_HEIGHT), glm::vec2(GUI_SLIDER_WIDTH, size.y + GUI_SLIDER_EXTENDED_HEIGHT * 2.0f)))
		{
			state.hotObjectID = id;
			if (state.isMouseLButtonPress)
			{
				state.activeObjectID = id;
			}
		}

		if (state.hotObjectID == id)
		{
			std::stringstream ss;
			ss << value;
			strings.push_back(TextRenderer::String(ss.str()));
			textRenderer.getStringData(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
				glm::vec3(state.cursorPosition.x, state.cursorPosition.y + 5.0f, 0.0f),
				1.0f,
				strings[strings.size() - 1],
				fontMode);
			if (state.activeObjectID == id)
			{

				GUISlider::getDrawData(position, size, sliderPosition, GUIWidget::GUIWidgetState::Active, widgetsDrawList);
				widgetState = GUIWidget::GUIWidgetState::Active;
			}
			else
			{
				GUISlider::getDrawData(position, size, sliderPosition, GUIWidget::GUIWidgetState::Hot, widgetsDrawList);
				widgetState = GUIWidget::GUIWidgetState::Hot;
			}
		}
		else
		{
			GUISlider::getDrawData(position, size, sliderPosition, GUIWidget::GUIWidgetState::Normal, widgetsDrawList);
		}

		if (state.activeObjectID == id)
		{
			T valueOffsets = static_cast<T>((state.cursorPosition.x - sliderPosition.x) / (size.x)*(max - min));
			if (!valueOffsets)
			{
				return widgetState;
			}

			widgetState = GUIWidget::GUIWidgetState::Change;
			value += valueOffsets;
			if (value > max)
			{
				value = max;
			}
			else if (value < min)
			{
				value = min;
			}
		}

		return widgetState;
	}

	GUIWidget::GUIWidgetState label(GUILabel & label, std::string caption, glm::vec4 & captionColor, GLfloat captionScale, glm::vec2 & position, glm::vec2 & size, glm::vec4 & color);
	//GUIWidget::GUIWidgetState line(GUILine & line, glm::vec2 & position, glm::vec2 & size, glm::vec4 & color);

	inline GLvoid setFontMode(Font::Mode mode = Font::Mode::Normal)
	{
		fontMode = mode;

	}
	inline GLvoid prepare(GLFWwindow * window, const GLboolean * mouseButtonPress)
	{
		GLdouble cursorPositionX = 0.0;
		GLdouble cursorPositionY = 0.0;
		GLint windowWidth = 0;
		GLint windowHeight = 0;

		glfwGetWindowSize(window, &windowWidth, &windowHeight);
		glfwGetCursorPos(window, &cursorPositionX, &cursorPositionY);
		cursorPositionY = windowHeight - cursorPositionY;
		state.cursorPosition.x = (GLfloat)cursorPositionX;
		state.cursorPosition.y = (GLfloat)cursorPositionY;
		/*
		state.isMouseLButtonPress = false;
		state.isMouseRButtonPress = false;
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			state.isMouseLButtonPress = true;
		}
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			state.isMouseRButtonPress = true;
		}
		*/
		
		state.isMouseLButtonPress = mouseButtonPress[GLFW_MOUSE_BUTTON_LEFT];
		state.isMouseRButtonPress = mouseButtonPress[GLFW_MOUSE_BUTTON_RIGHT];
		state.hotObjectID = 0;
		//state.activeObjectID = 0;
		strings.clear();
		widgetsDrawList.clearData();

	}
	inline GLvoid drawWidgets()
	{
		widgetsDrawList.draw();
		DrawList::resetDrawListVAO();
		DrawList::resetVertexBuffer();
	}
	inline GLvoid drawTexts(GLint textTextureLocation)
	{
		//textRenderer.drawText(textTextureLocation, "2333", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 96.0f, 0.0f), 1.0f, Font::Mode::MSDF);
		for (GLuint i = 0; i < strings.size(); ++i)
		{
			strings[i].draw(textTextureLocation);
		}
		DrawList::resetDrawListVAO();
		DrawList::resetVertexBuffer();
	}
	inline GLvoid finish()
	{
		if (!state.isMouseLButtonPress)
		{
			state.activeObjectID = 0;
		}

		if (widgetsDrawList.data.size() != lastWidgetsDrawListSize)
		{
			widgetsDrawList.updateData(GL_DYNAMIC_DRAW);
			lastWidgetsDrawListSize = widgetsDrawList.data.size();
		}
		else
		{
			widgetsDrawList.updateSubData(0, lastWidgetsDrawListSize, nullptr);
			widgetsDrawList.updateSubData(0, widgetsDrawList.data.size());
		}
		//std::cout << widgetsDrawList.data.size() << std::endl;

	}
	~IMGUIRenderer();

public:
	GUIState state;
	DrawList widgetsDrawList;
	std::vector<TextRenderer::String> strings;
	Font::Mode fontMode;
	TextRenderer textRenderer;
	GLuint lastWidgetsDrawListSize;
};

