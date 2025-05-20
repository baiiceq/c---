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
	void switch_to()
	{
		if (current_turn == ChessPiece::ChessPiece::Camp::Black)
			current_turn = ChessPiece::Camp::Red;
		else
			current_turn = ChessPiece::Camp::Black;
	}

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

		current_turn = ChessPiece::Camp::Black;

		chess_manager.set_callback_change([&]()
			{
				this->switch_to();
			});

		chess_manager.set_callback_win([&]()
			{
				if (current_turn == ChessPiece::Camp::Black)
				{
					MessageBox(GetHWnd(), _T("红方胜利！"), _T("游戏结束！"), MB_OK);
				}
				else {
					MessageBox(GetHWnd(), _T("黑方胜利！"), _T("游戏结束！"), MB_OK);
				}
				SceneManager::instance()->switch_to(SceneManager::SceneType::Menu);
			});
		
	}

	void on_update(int delta)
	{
		chess_manager.on_update(delta);
		ResourcesManager::instance()->get_camera()->on_update(delta);
	}

	void on_render(const Camera& camera)
	{
		board.on_render(camera);
		chess_manager.on_render(camera);
	}

	void on_input(const ExMessage& msg)
	{
		chess_manager.on_input(msg, current_turn);
	}

	void on_exit()
	{
		std::cout << "游戏退出" << std::endl;
		chess_manager.reset();
	}

private:
	Board board;

	ChessManager chess_manager;

	ChessPiece::Camp current_turn = ChessPiece::Camp::Black;
};