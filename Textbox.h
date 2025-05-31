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
		left = x1, top = y1, right = x2, bottom = y2;
		cursor_pos = { float(left ),float(bottom -5 )};
		cursor_index = -1;
	}

	void set_callback(std::function<void()> callback)
	{
		on_change = callback;
	}

	std::wstring get_Textbox()
	{
		return text;
	}

	void Clear()
	{
		text.clear();
	}

	void on_update(int delta);
	void on_render(const Camera& Camera); 
	void on_input(const ExMessage& msg);
private:
	int left = 0, top = 0, right = 0, bottom = 0;	// �ؼ�����
	std::wstring text;				// �ı�������
	size_t maxlen = 0;							    // �ı���������ݳ���
	Animation cursor;					            // ��궯��
	bool isActive = false;					        // �Ƿ��ڻ״̬
	Vector2 cursor_pos;					            // ���λ��
	int  cursor_index;			                // �������λ��
	std::function<void()> on_change;	        // �ı��ص�����
private:
	bool isInside(int x, int y)
	{
		return (left <= x && x <= right && top <= y && y <= bottom);
	}
	void cursor_index_to_pos();
	void change_cursor_index(int);
};