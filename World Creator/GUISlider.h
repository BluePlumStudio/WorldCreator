#pragma once

#include <cmath>

#include "GUIWidget.h"

#define GUI_SLIDER_WIDTH 8.0f
#define GUI_SLIDER_EXTENDED_HEIGHT 8.0f

class GUISlider :public GUIWidget
{
public:
	GUISlider();

	static inline GLvoid setSliderColorNormal(glm::vec4 & color)
	{
		sliderColorNormal = color;
	}

	static inline GLvoid setSliderColorActive(glm::vec4 & color)
	{
		sliderColorActive = color;
	}

	static inline GLvoid setSliderColorHot(glm::vec4 & color)
	{
		sliderColorHot = color;
	}

	static inline GLvoid setBarColorNormal(glm::vec4 & color)
	{
		barColorNormal = color;
	}

	static inline GLvoid getDrawData(const glm::vec2 & barPosition, glm::vec2 barSize, glm::vec2 sliderPosition, GUIWidgetState ObjectState, DrawList & drawList)
	{
		glm::vec2 sliderSize;
		glm::vec2 zero = { 0.0f, 0.0f };

		barSize += glm::vec2(GUI_SLIDER_WIDTH, 0.0f);
		DrawList::getRectangleDrawData(barPosition, barSize, zero, zero, barColorNormal, drawList);

		/*
				 -
				| |
				-----------
		here->  -*---------
				| |
				 -
		*/
		sliderSize.x = GUI_SLIDER_WIDTH;
		sliderSize.y = GUI_SLIDER_EXTENDED_HEIGHT * 2.0f + barSize.y;
		sliderPosition.x -= GUI_SLIDER_WIDTH / 2.0f;
		sliderPosition.y -= GUI_SLIDER_EXTENDED_HEIGHT;

		if (ObjectState == GUIWidgetState::Active)
		{
			DrawList::getRectangleDrawData(sliderPosition, sliderSize, zero, zero, sliderColorActive, drawList);
		}
		else if (ObjectState == GUIWidgetState::Hot)
		{
			DrawList::getRectangleDrawData(sliderPosition, sliderSize, zero, zero, sliderColorHot, drawList);
		}
		else
		{
			DrawList::getRectangleDrawData(sliderPosition, sliderSize, zero, zero, sliderColorNormal, drawList);
		}
	}


	~GUISlider();
private:
	static glm::vec4 sliderColorNormal;
	static glm::vec4 sliderColorActive;
	static glm::vec4 sliderColorHot;
	static glm::vec4 barColorNormal;

	static GLboolean isInited;
};

