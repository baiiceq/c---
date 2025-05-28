#pragma once
#include <graphics.h>

#include "camera.h"
#include "animation.h"

class Textbox
{
public:
	Textbox();
	~Textbox();
	void Set_Textbox(int x1, int y1, int x2, int y2, int max)
	{
		maxlen = max;
		text = new wchar_t[maxlen];
		text[0] = L'\0';
		left = x1, top = y1, right = x2, bottom = y2;
	}

	wchar_t* get_Textbox()
	{
		return text;
	}

	void Clear()
	{
		if (text != nullptr)
		{
			text[0] = L'\0';
			text_len = 0;
		}
	}

	void on_update(int delta);
	void on_render(const Camera& Camera);
	void on_input(const ExMessage& msg);
private:
	int left = 0, top = 0, right = 0, bottom = 0;	// 控件坐标
	wchar_t* text;							// 控件内容
	size_t text_len = 0;							// 文本框内容长度
	size_t maxlen = 0;							    // 文本框最大内容长度
	Animation cursor;					            // 光标动画
	bool isActive = false;					        // 是否处于活动状态
private:
	bool isInside(int x, int y)
	{
		return (left <= x && x <= right && top <= y && y <= bottom);
	}
};