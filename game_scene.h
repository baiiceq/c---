#pragma once
#include "util.h"
#include "scene.h"
#include "board.h"
#include "scene_manager.h"
#include "chess_manager.h"

#include <iostream>


class GameScene :public Scene
{
public:
	GameScene()
	{
		Vector2 size = board.get_size();
		board.set_pos((getwidth() - size.x) / 2, (getheight() - size.y) / 2);
		std::cout << (getwidth() - size.x) / 2 << " " << (getheight() - size.y) / 2 << std::endl;
	}
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
		board.on_render(camera);
		chess_manager.on_render(camera);
	}

	void on_input(const ExMessage& msg)
	{
		chess_manager.on_input(msg);
	}

	void on_exit()
	{
		std::cout << "游戏退出" << std::endl;
	}

private:
	Board board;

	ChessManager chess_manager;
};