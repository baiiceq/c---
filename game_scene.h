#pragma once
#include "util.h"
#include "scene.h"
#include "board.h"
#include "scene_manager.h"
#include "chess_manager.h"
#include "static_image.h"
#include "pause_scene.h"

#include <iostream>
#include <graphics.h>

extern std::atomic<bool> ai_thinking; // AI˼��״̬

// ��Ϸ����

class GameScene :public Scene
{
private:
	// ��ǰ��Ϸ״̬
	enum class GameState 
	{
		GameRunning,         // ����
		GamePaused           // ��ͣ
	};

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

		pause_scene.set_callback_continue([&]()
			{
				state = GameState::GameRunning;
			});

		pause_scene.set_callback_exit([&]()
			{
				HWND hwnd = GetHWnd();  
				int ret = MessageBox(hwnd, L"�Ƿ񱣴���Ϸ��", L"����ȷ��", MB_YESNO | MB_ICONQUESTION | MB_TOPMOST);
				if (ret == IDYES)
				{
					chess_manager.save_game_record("data/save.txt");
				}
			});
	}
	~GameScene() = default;

	void on_enter()
	{
		std::cout << "��Ϸ��ʼ" << std::endl;

		chess_manager.reset();

		// ����ý���ʱ���ѵ�ǰ��Ӫ�ĳɺ�ɫ��
		current_turn = ChessPiece::Camp::Red;
		
	}

	void on_update(int delta)
	{
		if (ai_thinking == true)//���ܳ�����
			return;
		if (state == GameState::GameRunning)
		{
			chess_manager.on_update(delta);
			ResourcesManager::instance()->get_camera()->on_update(delta);

			repentance.on_update(delta);
		}
		else
		{
			pause_scene.on_update(delta);
		}
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
		if(ai_thinking == true)
		{
			//ai����
		}

		if (state == GameState::GamePaused)
		{
			pause_scene.on_render(camera);
		}
	}
	void on_input(const ExMessage& msg)
	{
		if(ai_thinking==true)
			return;
		if (state == GameState::GameRunning)
		{
			if (msg.message == WM_KEYDOWN && msg.vkcode == VK_ESCAPE)
			{
				state = GameState::GamePaused;
			}

			chess_manager.on_input(msg, current_turn);

			repentance.on_input(msg);
		}
		else
		{
			pause_scene.on_input(msg);
		}
	}

	void on_exit()
	{
		std::cout << "��Ϸ�˳�" << std::endl;
		// �˳���Ϸ����ʱ�����ӹ�������������
	}

private:
	Board board;  // ��Ϸ����

	ChessManager chess_manager;   // ���ӹ�����

	ChessPiece::Camp current_turn = ChessPiece::Camp::Black;     // ��ǰ��Ҫ�ƶ�����Ӫ

	// ��̬ͼƬ
	StaticImage red_tip;
	StaticImage black_tip;

	Button repentance;   // ���尴ť

	Animation ai; // AI����

	GameState state = GameState::GameRunning;     // ��Ϸ״̬

	// ��ͣҳ��
	PauseScene pause_scene;
};