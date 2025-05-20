#pragma once
#include "util.h"
#include "scene.h"
#include "board.h"
#include "scene_manager.h"
#include "chess_manager.h"
#include "static_image.h"

#include <iostream>
#include <graphics.h>


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
		board.set_pos(260, (getheight() - size.y) / 2);

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

		black_tip.set_image("black_tip");
		black_tip.set_position({5,15});
		black_tip.set_size({ 250,55 });

		red_tip.set_image("red_tip");
		red_tip.set_position({ 5,15 });
		red_tip.set_size({ 250,55 });

		repentance.set_pos(50, 90);
		repentance.set_size(160, 60);
		repentance.set_image("repentance");
	}
	~GameScene() = default;

	void on_enter()
	{
		std::cout << "游戏开始" << std::endl;

		current_turn = ChessPiece::Camp::Red;
		
	}

	void on_update(int delta)
	{
		chess_manager.on_update(delta);
		ResourcesManager::instance()->get_camera()->on_update(delta);

		repentance.on_update(delta);
	}

	void on_render(const Camera& camera)
	{
		board.on_render(camera);
		chess_manager.on_render(camera);

		if (current_turn == ChessPiece::ChessPiece::Camp::Black)
		{
			black_tip.on_render(camera);
		}
		else
		{
			red_tip.on_render(camera);
		}

		repentance.on_render(camera);

	}
	void on_input(const ExMessage& msg)
	{
		chess_manager.on_input(msg, current_turn);

		repentance.on_input(msg);

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

	// 静态图片
	StaticImage red_tip;
	StaticImage black_tip;

	Button repentance;   // 悔棋按钮
};