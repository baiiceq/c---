#pragma once
#include "util.h"
#include "scene.h"
#include "scene_manager.h"

#include <iostream>


class GameScene :public Scene
{
public:
	GameScene() = default;
	~GameScene() = default;

	void on_enter()
	{
		std::cout << "游戏开始" << std::endl;
	}

	void on_update(int delta)
	{
	}

	void on_render(const Camera& camera)
	{
		settextcolor(RGB(255, 0, 0));
		outtextxy(15, 15, _T("xxxxxxxx"));
	}

	void on_input(const ExMessage& msg)
	{
	}

	void on_exit()
	{
		std::cout << "游戏退出" << std::endl;
	}
};