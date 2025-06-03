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

// 游戏界面

class GameScene :public Scene
{
public:
	// 当前游戏状态
	enum class GameState 
	{
		GameRunning,         // 运行
		GamePaused,          // 暂停
		GamePlayBack,        // 回放
		GameLoad             // 读取
	};

public:
	// 跳转阵营(红->黑\黑->红)
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
		// 棋盘大小，设置棋盘位置
		Vector2 size = board.get_size();
		board.set_pos(260, (getheight() - (int)size.y) / 2);

		// 设置棋子管理器的回调函数，当棋子管理器中移动了棋子，执行回调函数，更换阵营
		chess_manager.set_callback_change([&](int val)
			{
				this->switch_to();
			});

		// 当有一方的将被吃后，调用该回调函数
		chess_manager.set_callback_win([&](int val)
			{
				if (current_turn == ChessPiece::Camp::Red)
				{
					MessageBox(GetHWnd(), _T("红方胜利！"), _T("游戏结束！"), MB_OK);
				}
				else {
					MessageBox(GetHWnd(), _T("黑方胜利！"), _T("游戏结束！"), MB_OK);
				}

				HWND hwnd = GetHWnd();
				int ret = MessageBox(hwnd, L"是否保存游戏？", L"保存确认", MB_YESNO | MB_ICONQUESTION | MB_TOPMOST);
				if (ret == IDYES)
				{
					chess_manager.save_game_record("data/save.txt");
				}
				if (fstate == GameState::GameRunning)
				{
					chess_manager.save_game_record(SceneManager::instance()->get_player_account()->add_game_record());
				}

				chess_manager.reset();

				//保存游戏记录
				if (fstate == GameState::GameRunning) {
					chess_manager.save_game_record(SceneManager::instance()->get_player_account()->
						add_game_record(current_turn,chess_manager.get_ai_difficulty()));
				}
				SceneManager::instance()->switch_to(SceneManager::SceneType::Menu);
			});

		// 黑方移动和红方移动的提示(静态图片)
		black_tip.set_image("black_tip");
		black_tip.set_position({5,15});
		black_tip.set_size({ 250,55 });

		red_tip.set_image("red_tip");
		red_tip.set_position({ 5,15 });
		red_tip.set_size({ 250,55 });

		// 悔棋按钮
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
				int ret = MessageBox(hwnd, L"是否保存游戏？", L"保存确认", MB_YESNO | MB_ICONQUESTION | MB_TOPMOST);
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
		std::cout << "游戏开始" << std::endl;

		// 进入该界面时，把当前阵营改成红色方
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

		// 不同方打印不同的提示
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
		std::cout << "游戏退出" << std::endl;
		// 退出游戏界面时，棋子管理器重新设置
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
	Board board;  // 游戏棋盘

	ChessManager chess_manager;   // 棋子管理器

	ChessPiece::Camp current_turn = ChessPiece::Camp::Black;     // 当前需要移动的阵营

	// 静态图片
	StaticImage red_tip;
	StaticImage black_tip;

	Button repentance;   // 悔棋按钮

	Animation ai; // AI动画

	GameState state = GameState::GameRunning;     // 游戏状态
	GameState fstate = GameState::GameRunning;    // 初始状态
	// 暂停页面
	PauseScene pause_scene;

	// 回放时计算每次操作间隔的时间的计时器
	Timer timer_playback;

	std::string load_path = "data/save.txt"; // 游戏记录路径
};