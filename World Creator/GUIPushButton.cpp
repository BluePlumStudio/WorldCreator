#include "GUIPushButton.h"

using namespace std;

glm::vec2 GUIPushButton::texCoordsNormal =	{ 0.0f, 0.125f };
glm::vec2 GUIPushButton::texSizeNormal =	{ 0.5f, 0.125f };
glm::vec4 GUIPushButton::colorNormal =		{ 1.0f, 1.0f, 1.0f, 1.0f };

glm::vec2 GUIPushButton::texCoordsActive =	{ 0.0f, 0.25f };
glm::vec2 GUIPushButton::texSizeActive =	{ 0.5f, 0.125f };
glm::vec4 GUIPushButton::colorActive =		{ 1.0f, 1.0f, 1.0f, 1.0f };

glm::vec2 GUIPushButton::texCoordsHot =		{ 0.0f, 0.375f };
glm::vec2 GUIPushButton::texSizeHot =		{ 0.5f, 0.125f };
glm::vec4 GUIPushButton::colorHot =			{ 1.0f, 1.0f, 1.0f, 1.0f };

GUIPushButton::GUIPushButton()
{

}

GUIPushButton::~GUIPushButton()
{

}
