#include "GUIRenderer.h"

using namespace std;

/**/

IMGUIRenderer::IMGUIRenderer()
{
}

GLint IMGUIRenderer::init(const GLchar * fontPath, GLuint positionLocation, GLuint texCoordsLocation, GLuint colorLocation, FT_UInt width, FT_UInt height)
{
	if (widgetsDrawList.init())
	{
		return 1;
	}
	widgetsDrawList.setDataStride(8);
	widgetsDrawList.setDrawMode(GL_TRIANGLES);
	widgetsDrawList.setVertexAttribPointer(positionLocation, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 8, (GLvoid*)0);
	widgetsDrawList.setVertexAttribPointer(texCoordsLocation, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 8, (GLvoid*)(2 * sizeof(GLfloat)));
	widgetsDrawList.setVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 8, (GLvoid*)(4 * sizeof(GLfloat)));

	lastWidgetsDrawListSize = 0;

	strings.clear();
	setFontMode(Font::Mode::Normal);

	return textRenderer.init(fontPath, positionLocation, texCoordsLocation, colorLocation, width, height);

}

GLvoid IMGUIRenderer::texts(string caption, glm::vec4 & color, glm::vec2 & position, GLfloat scale)
{
	strings.resize(strings.size() + 1);
	strings[strings.size() - 1] = caption;

	textRenderer.getStringData(color,
		glm::vec3(position, 0.0f),
		scale,
		strings[strings.size() - 1],
		fontMode);
}

GLvoid IMGUIRenderer::rectangle(glm::vec2 & position, glm::vec2 & size, glm::vec4 & color)
{
	glm::vec2 texCoords = { 0.0f, 0.0f };
	DrawList::getRectangleDrawData(position, size, texCoords, texCoords, color, widgetsDrawList);
}

GUIWidget::GUIWidgetState IMGUIRenderer::pushButton(GUIPushButton & pushButton, std::string caption, glm::vec4 & color, GLfloat scale, glm::vec2 & position, glm::vec2 & size)
{
	GLuint id = pushButton.getID();
	GUIWidget::GUIWidgetState widgetState = GUIWidget::GUIWidgetState::Normal;

	//strings.push_back(TextRenderer::String());
	strings.resize(strings.size() + 1);
	strings[strings.size() - 1] = caption;

	textRenderer.getStringData(color,
		glm::vec3(position.x + size.x / 2.0f - (textRenderer.getStringWidth(caption)) * scale / 2.0f, position.y + size.y / 2.0f - (textRenderer.getStringHeight(caption)) * scale / 2.0f, 0.0f),
		scale,
		strings[strings.size() - 1],
		fontMode);

	if (GUIPushButton::isInside(state, position, size))
	{
		state.hotObjectID = id;
		if (state.isMouseLButtonPress)
		{
			state.activeObjectID = id;
		}
	}

	if (state.hotObjectID == id)
	{
		if (state.activeObjectID == id)
		{
			GUIPushButton::getDrawData(position, size, GUIWidget::GUIWidgetState::Active, widgetsDrawList);
			widgetState = GUIWidget::GUIWidgetState::Active;
		}
		else
		{
			strings.push_back(TextRenderer::String());
			strings[strings.size() - 1] = caption;
			textRenderer.getStringData(color,
				glm::vec3(state.cursorPosition, 0.0f),
				1.0f,
				strings[strings.size() - 1],
				fontMode);
			GUIPushButton::getDrawData(position, size, GUIWidget::GUIWidgetState::Hot, widgetsDrawList);
			widgetState = GUIWidget::GUIWidgetState::Hot;
		}
	}
	else
	{
		GUIPushButton::getDrawData(position, size, GUIWidget::GUIWidgetState::Normal, widgetsDrawList);
	}

	if (!state.isMouseLButtonPress&&
		state.hotObjectID == id &&
		state.activeObjectID == id)
	{
		widgetState = GUIWidget::GUIWidgetState::Click;
	}

	return widgetState;
}

GUIWidget::GUIWidgetState IMGUIRenderer::label(GUILabel & label, std::string caption, glm::vec4 & captionColor, GLfloat captionScale, glm::vec2 & position, glm::vec2 & size, glm::vec4 & color)
{
	GLuint id = label.getID();
	GUIWidget::GUIWidgetState widgetState = GUIWidget::GUIWidgetState::Normal;

	strings.push_back(TextRenderer::String());
	strings[strings.size() - 1] = caption;
	textRenderer.getStringData(captionColor,
		glm::vec3(position.x + size.x / 2.0f - (textRenderer.getStringWidth(caption)) * captionScale / 2.0f, position.y + size.y / 2.0f - (textRenderer.getStringHeight(caption)) * captionScale / 2.0f, 0.0f),
		captionScale,
		strings[strings.size() - 1],
		fontMode);

	/*
	if (GUILabel::isInside(state, position, size))
	{
		state.hotObjectID = id;
		if (state.isMouseLButtonPress)
		{
			state.activeObjectID = id;
		}
	}
	*/

	GUILabel::getDrawData(position, size, color, widgetsDrawList);

	/*
	if (state.hotObjectID == id)
	{
		if (state.activeObjectID == id)
		{
			widgetState = GUIWidget::GUIWidgetState::Active;
		}
		else
		{
			widgetState = GUIWidget::GUIWidgetState::Hot;
		}
	}

	if (!state.isMouseLButtonPress&&
		state.hotObjectID == id &&
		state.activeObjectID == id)
	{
		widgetState = GUIWidget::GUIWidgetState::Click;
	}
	*/

	return widgetState;
}

IMGUIRenderer::~IMGUIRenderer()
{

}
