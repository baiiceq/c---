#pragma once

#include <graphics.h>
#include "camera.h"

// ҳ��ĳ������

class Scene
{
public:
	Scene() = default;
	~Scene() = default;

	// ����ҳ��
	virtual void on_enter() = 0;
	// ����ҳ��
	virtual void on_update(int delta) = 0;
	// ��Ⱦҳ��
	virtual void on_render(const Camera& camera) = 0;
	// ��������
	virtual void on_input(const ExMessage& msg) = 0;
	// �˳�ҳ��
	virtual void on_exit() = 0;

private:

};