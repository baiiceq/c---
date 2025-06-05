#pragma once
#include "util.h"
#include "scene.h"
#include "board.h"
#include "scene_manager.h"
#include "chess_manager.h"
#include "static_image.h"
#include "chess_server.h"
#include "chess_client.h"


#include <iostream>
#include <graphics.h>

class OnlineScene :public Scene
{
public:
	// ��ǰ����״̬
	enum class OnlineState
	{
		Waiting,         // �ȴ�
		Racing,          // ��ʼ
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
	OnlineScene()
	{
		// ���̴�С����������λ��
		Vector2 size = board.get_size();
		board.set_pos(260, (getheight() - (int)size.y) / 2);

		// �������ӹ������Ļص������������ӹ��������ƶ������ӣ�ִ�лص�������������Ӫ
		chess_manager.set_callback_change([&](int val)
			{
				this->switch_to();
				if (is_my_turn)
				{
					last_own_move = val;
					finish_send = false;
					is_my_turn = false;
				}
				else
				{
					last_opposite_move = val;
				}
			});

		// ����һ���Ľ����Ժ󣬵��øûص�����
		chess_manager.set_callback_win([&](int val)
			{
				this->switch_to();
				if (is_my_turn)
				{
					last_own_move = val;
					finish_send = false;
					is_my_turn = false;
				}
				else
				{
					last_opposite_move = val;
				}

				if (!finish_send && client)
				{
					if (client->send_move(last_own_move, is_host))
					{
						finish_send = true;
					}
				}

				if (current_turn == ChessPiece::Camp::Black)
				{
					MessageBox(GetHWnd(), _T("�췽ʤ����"), _T("��Ϸ������"), MB_OK);
				}
				else {
					MessageBox(GetHWnd(), _T("�ڷ�ʤ����"), _T("��Ϸ������"), MB_OK);
				}

				if (is_host)
				{
					chess_manager.save_game_record(SceneManager::instance()->get_player_account()->add_game_record(current_turn));
				}
				else 
				{
					chess_manager.save_game_record(SceneManager::instance()->get_player_account()->add_game_record(current_turn == ChessPiece::Camp::Black ? ChessPiece::Camp::Red : ChessPiece::Camp::Black));
				}
				SceneManager::instance()->switch_to(SceneManager::SceneType::Menu);
			});

		// �ڷ��ƶ��ͺ췽�ƶ�����ʾ(��̬ͼƬ)
		black_tip.set_image("black_tip");
		black_tip.set_position({ 5,15 });
		black_tip.set_size({ 250,55 });

		red_tip.set_image("red_tip");
		red_tip.set_position({ 5,15 });
		red_tip.set_size({ 250,55 });

		anim_waiting_players.add_frame(ResourcesManager::instance()->find_image("waiting_players"), 11);
		anim_waiting_players.set_position({ 420,300 });
		anim_waiting_players.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		anim_waiting_players.set_loop(true);
		anim_waiting_players.set_interval(300);

		anim_waiting_move.add_frame(ResourcesManager::instance()->find_image("waiting_move"), 8);
		anim_waiting_move.set_position({ 140,400 });
		anim_waiting_move.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		anim_waiting_move.set_loop(true);
		anim_waiting_move.set_interval(300);

		exit.set_pos(280, 480);
		exit.set_size(240, 60);
		exit.set_image("exit");
		exit.set_on_click([&]()
			{
				SceneManager::instance()->switch_to(SceneManager::SceneType::Menu);
			});

		timer_retry.set_one_shot(false);
		timer_retry.set_wait_time(RETRY_INTERVAL);
		timer_retry.set_on_timeout([&]()
			{
				if (client && client->join())
				{
					timer_retry.pause(); 
					SceneManager::instance()->get_player_account()->add_game_record(0);
					state = OnlineState::Racing;
				}
				else
				{
					retry_times++;
					if (retry_times >= MAX_RETRY)
					{
						timer_retry.pause();  
						MessageBox(GetHWnd(), _T("��������������ʧ�ܣ�"), _T("��ʾ"), MB_OK);
						SceneManager::instance()->switch_to(SceneManager::SceneType::Menu);
					}
				}
			});

	}
	~OnlineScene() = default;

	void on_enter()
	{
		std::cout << "��Ϸ��ʼ" << std::endl;

		chess_manager.reset();
		state = OnlineState::Waiting;

		chess_manager.reset();
		current_turn = ChessPiece::Camp::Red;

		// ��ʼ�����磨�����ⲿ�������������ǿͻ��ˣ�
		init_network(ip, port);
	}

	void on_update(int delta)
	{
		if (state == OnlineState::Racing)
		{
			// ��ѯ�Է��߷�
			if (!is_my_turn)
			{
				anim_waiting_move.on_update((float)delta);
				receive_move();  
			}

			if (!finish_send && client)
			{
				if (client->send_move(last_own_move, is_host))
				{
					finish_send = true;
				}
			}

			chess_manager.on_update(delta, current_turn);
			ResourcesManager::instance()->get_camera()->on_update(delta);
		}
		else
		{
			if (is_host)
			{
				anim_waiting_players.on_update((float)delta);
				if (server && server->is_ready())
				{
					SceneManager::instance()->get_player_account()->add_game_record(1);
					state = OnlineState::Racing;
				}
			}
			else
			{
				timer_retry.on_update(delta);
			}
		}
	}

	void on_render(const Camera& camera)
	{
		if (state == OnlineState::Racing)
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

			if (!is_my_turn)
				anim_waiting_move.on_render(camera);
		}
		else if (is_host)
		{
			exit.on_render(camera);
			anim_waiting_players.on_render(camera);
		}
	}

	void on_input(const ExMessage& msg)
	{
		if (state == OnlineState::Racing)
		{
			if (is_my_turn)
			{
				chess_manager.on_input(msg, current_turn);
			}
		}
		else if (is_host)
		{
			exit.on_input(msg);
		}
	}

	void on_exit()
	{
		if (server)
		{
			server->stop();
			delete server;
			server = nullptr;
		}

		if (client)
		{
			delete client;
			client = nullptr;
		}
	}

	void set_state(OnlineState state)
	{
		this->state = state;
	}

	void init_network(const std::string& ip, int port)
	{
		if (is_host)
		{
			server = new ChessServer(ip, port);
			server->start();
			client = new ChessClient(ip, port);  // �����Լ�
			is_my_turn = true;  // ��������
		}
		else 
		{
			client = new ChessClient(ip, port);
			is_my_turn = false; // �ͻ��˺���
		}
	}

	bool receive_move()
	{
		if (!client) return false;
		int move_code = client->get_opponent_move(is_host);
		if (move_code != -1 && move_code != last_opposite_move) 
		{
			Vector2 from, to;
			decode_move_code(move_code, from, to);
			chess_manager.move_piece(from, to, false);
			is_my_turn = true;
			std::cout << "turn���true��\n";
			return true;
		}
		return false;
	}

	void decode_move_code(int code, Vector2& from, Vector2& to)
	{
		from.x = float(code / 1000);
		from.y = float((code / 100) % 10);
		to.x = float(((code / 10) % 10));
		to.y = float((code % 10));
	}

	void set_is_host(bool is_host)
	{
		this->is_host = is_host;
	}

	void set_port(int port)
	{
		this->port = port;
	}

	void set_ip(const std::string& ip)
	{
		this->ip = ip;
	}

private:
	Board board;  // ��Ϸ����

	ChessManager chess_manager;   // ���ӹ�����

	ChessPiece::Camp current_turn = ChessPiece::Camp::Black;     // ��ǰ��Ҫ�ƶ�����Ӫ

	// ��̬ͼƬ
	StaticImage red_tip;
	StaticImage black_tip;

	OnlineState state = OnlineState::Waiting;     // ��Ϸ״̬

	int port;
	std::string ip;

	bool is_host = false;              // �Ƿ�������
	bool is_my_turn = false;           // �Ƿ��ֵ���
	ChessPiece::Camp my_turn;
	ChessServer* server = nullptr;     // ���������
	ChessClient* client = nullptr;     // �ͻ�������ͨ��
	int last_opposite_move = -1;       // ��һ�ν��յ����߷�����ֹ�ظ�����
	int last_own_move = -1;            // ��һ���Լ����߷�

	bool finish_send = true;

	Animation anim_waiting_players;
	Animation anim_waiting_move;
	Button exit;

	const int MAX_RETRY = 5;
	const int RETRY_INTERVAL = 200; 
	int retry_times = 0;
	Timer timer_retry; 
};