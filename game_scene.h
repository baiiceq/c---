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
#include <string>

// ��Ϸ����

class GameScene :public Scene
{
public:
	// ��ǰ��Ϸ״̬
	enum class GameState 
	{
		GameRunning,         // ����
		GamePaused,          // ��ͣ
		GamePlayBack,        // �ط�
		GameLoad             // ��ȡ
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
		board.set_pos(260, (getheight() - (int)size.y) / 2);

		// �������ӹ������Ļص������������ӹ��������ƶ������ӣ�ִ�лص�������������Ӫ
		chess_manager.set_callback_change([&](int val)
			{
				this->switch_to();
			});

		// ����һ���Ľ����Ժ󣬵��øûص�����
		chess_manager.set_callback_win([&](int val)
			{
				if (current_turn == ChessPiece::Camp::Red)
				{
					MessageBox(GetHWnd(), _T("�췽ʤ����"), _T("��Ϸ������"), MB_OK);
				}
				else {
					MessageBox(GetHWnd(), _T("�ڷ�ʤ����"), _T("��Ϸ������"), MB_OK);
				}

				HWND hwnd = GetHWnd();
				int ret = MessageBox(hwnd, L"�Ƿ񱣴���Ϸ��", L"����ȷ��", MB_YESNO | MB_ICONQUESTION | MB_TOPMOST);
				if (ret == IDYES)
				{
					chess_manager.save_game_record("data/save.txt");
				}
				if (fstate == GameState::GameRunning)
				{
					chess_manager.save_game_record(SceneManager::instance()->get_player_account()->add_game_record());
				}

				chess_manager.reset();

				//������Ϸ��¼
				if (fstate == GameState::GameRunning) {
					chess_manager.save_game_record(SceneManager::instance()->get_player_account()->
						add_game_record(current_turn,chess_manager.get_ai_difficulty()));
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
				if(fstate == GameState::GameRunning)
				{
					chess_manager.save_game_record(SceneManager::instance()->get_player_account()-> add_game_record());
				}

				chess_manager.reset();
			});

		timer_interval.set_wait_time(INTERVAL);
		timer_interval.set_one_shot(false);
		timer_interval.set_on_timeout([&]()
			{
				chess_manager.load_one_step();
			});
	}
	~GameScene() = default;

	void on_enter()
	{
		std::cout << "��Ϸ��ʼ" << std::endl;

		// ����ý���ʱ���ѵ�ǰ��Ӫ�ĳɺ�ɫ��
		current_turn = ChessPiece::Camp::Red;

		chess_manager.reset();
		
		if (state == GameState::GameLoad)
		{
			chess_manager.load_game_record(load_path);
			chess_manager.load();
			load_path = "data/save.txt"; 
			state = GameState::GameRunning;
			fstate = GameState::GameLoad;
		}
		else if (state == GameState::GamePlayBack)
		{
			chess_manager.load_game_record(load_path);
			load_path = "data/save.txt";
			timer_interval.restart();
			fstate = GameState::GamePlayBack;
		}
		else if (state == GameState::GamePaused)
		{
			state = GameState::GameRunning;
		}
		else if(state == GameState::GameRunning)
		{
			fstate = GameState::GameRunning;
		}
	}

	void on_update(int delta)
	{
		if (state != GameState::GamePlayBack)
			timer_interval.pause();

		if (state == GameState::GameRunning)
		{
			chess_manager.on_update(delta, current_turn);
			ResourcesManager::instance()->get_camera()->on_update(delta);

			repentance.on_update(delta);
		}
		else if (state == GameState::GamePlayBack)
		{
			chess_manager.on_update(delta, current_turn);
			timer_interval.on_update(delta);
		}
		else if(state == GameState::GamePaused)
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

		if (state == GameState::GamePaused)
		{
			pause_scene.on_render(camera);
		}
	}
	void on_input(const ExMessage& msg)
	{
		if (state == GameState::GameRunning)
		{
			if (msg.message == WM_KEYDOWN && msg.vkcode == VK_ESCAPE)
			{
				state = GameState::GamePaused;
			}

			chess_manager.on_input(msg, current_turn);

			repentance.on_input(msg);
		}
		else if(state == GameState::GamePaused)
		{
			pause_scene.on_input(msg);
		}
	}

	void on_exit()
	{
		std::cout << "��Ϸ�˳�" << std::endl;
		// �˳���Ϸ����ʱ�����ӹ�������������
	}

	void set_state(GameState state)
	{
		this->state = state;
	}

	void set_fstate(GameState fstate)
	{
		this->fstate = fstate;
	}

	void set_player(bool red, bool black)
	{
		chess_manager.set_player(red, black);
	}

	void set_difficulty(int red, int black)
	{
		chess_manager.set_difficulty(red, black);
	}

	void set_load_path(const std::string& path)
	{
		load_path = path;
	}
	void set_chess_manager_turn_time(int time)
	{
		chess_manager.set_turn_time_limit(time);
	}
	int get_chess_manager_turn_time()
	{
		return chess_manager.get_turn_time_limit();
	}
private:
	const int INTERVAL = 1000;
	Timer timer_interval;

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
	GameState fstate = GameState::GameRunning;    // ��ʼ״̬
	// ��ͣҳ��
	PauseScene pause_scene;

	// �ط�ʱ����ÿ�β��������ʱ��ļ�ʱ��
	Timer timer_playback;

	std::string load_path = "data/save.txt"; // ��Ϸ��¼·��
};