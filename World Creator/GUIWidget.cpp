#include "GUIWidget.h"

using namespace std;

GLuint GUIWidget::widgetCount = 0;

GUIWidget::GUIWidget()
{
	state = GUIWidget::GUIWidgetState::None;
	ID = ++widgetCount;
}

GLuint GUIWidget::getID()const
{
	return ID;
}

GLuint GUIWidget::getWidgetCount()const
{
	return widgetCount;
}

GUIWidget::~GUIWidget()
{
	--widgetCount;
}