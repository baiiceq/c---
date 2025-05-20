#pragma once
#include "util.h"
#include "scene.h"
#include "board.h"
#include "scene_manager.h"
#include "chess_manager.h"
#include "static_image.h"

#include <iostream>
#include <graphics.h>


// ��Ϸ����

class GameScene :public Scene
{

public:
	// ��ת��Ӫ(��->��\��->��)
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
		// ���̴�С����������λ��
		Vector2 size = board.get_size();
		board.set_pos(260, (getheight() - size.y) / 2);

		// �������ӹ������Ļص������������ӹ��������ƶ������ӣ�ִ�лص�������������Ӫ
		chess_manager.set_callback_change([&]()
			{
				this->switch_to();
			});

		// ����һ���Ľ����Ժ󣬵��øûص�����
		chess_manager.set_callback_win([&]()
			{
				if (current_turn == ChessPiece::Camp::Black)
				{
					MessageBox(GetHWnd(), _T("�췽ʤ����"), _T("��Ϸ������"), MB_OK);
				}
				else {
					MessageBox(GetHWnd(), _T("�ڷ�ʤ����"), _T("��Ϸ������"), MB_OK);
				}
				SceneManager::instance()->switch_to(SceneManager::SceneType::Menu);
			});

		// �ڷ��ƶ��ͺ췽�ƶ�����ʾ(��̬ͼƬ)
		black_tip.set_image("black_tip");
		black_tip.set_position({5,15});
		black_tip.set_size({ 250,55 });

		red_tip.set_image("red_tip");
		red_tip.set_position({ 5,15 });
		red_tip.set_size({ 250,55 });

		// ���尴ť
		repentance.set_pos(50, 90);
		repentance.set_size(160, 60);
		repentance.set_image("repentance");
		repentance.set_on_click([&]()
			{
				chess_manager.undo_move();
			});
	}
	~GameScene() = default;

	void on_enter()
	{
		std::cout << "��Ϸ��ʼ" << std::endl;

		// ����ý���ʱ���ѵ�ǰ��Ӫ�ĳɺ�ɫ��
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

		// ��ͬ����ӡ��ͬ����ʾ
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
		std::cout << "��Ϸ�˳�" << std::endl;
		// �˳���Ϸ����ʱ�����ӹ�������������
		chess_manager.reset();
	}

private:
	Board board;  // ��Ϸ����

	ChessManager chess_manager;   // ���ӹ�����

	ChessPiece::Camp current_turn = ChessPiece::Camp::Black;     // ��ǰ��Ҫ�ƶ�����Ӫ

	// ��̬ͼƬ
	StaticImage red_tip;
	StaticImage black_tip;

	Button repentance;   // ���尴ť
};