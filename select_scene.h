#pragma once

#include "scene.h"
#include "atlas.h"
#include "timer.h"
#include "camera.h"
#include "animation.h"
#include "scene_manager.h"
#include "button.h"
#include "static_image.h"
#include "option_selector.h"
#include "text_input.h"

// 选择界面

class SelectScene : public Scene
{
public:
	SelectScene()
	{
		// 初始化各种按钮
		benji.set_pos(120, 50);
		benji.set_size(240, 60);
		benji.set_image("benji");
		benji.set_on_click([&]()
			{
				isLianji = false;
			});

		lianji.set_pos(440, 50);
		lianji.set_size(240, 60);
		lianji.set_image("lianji");
		lianji.set_on_click([&]()
			{
				isLianji = true;
			});

		startgame.set_pos(440, 500);
		startgame.set_size(240, 60);
		startgame.set_image("startgame");
		startgame.set_on_click([&]()
			{
				SceneManager::instance()->set_gamescene_player(is_red_AI, is_black_AI);
				SceneManager::instance()->set_gamescene_difficult((red_difficulty_selector.GetSelected() + 1) * 2, (black_difficulty_selector.GetSelected() + 1) * 2);
				SceneManager::instance()->get_player_account()->add_game_record(is_red_AI, is_black_AI, red_difficulty_selector.GetSelected()+1, black_difficulty_selector.GetSelected()+1);
				SceneManager::instance()->set_gamescene_state_to_running();
				SceneManager::instance()->switch_to(SceneManager::SceneType::Game);
			});

		back.set_pos(120, 500);
		back.set_size(240, 60);
		back.set_image("backmenu");
		back.set_on_click([&]()
			{
				SceneManager::instance()->switch_to(SceneManager::SceneType::Menu);
			});

		load.set_pos(120, 400);
		load.set_size(240, 60);
		load.set_image("load");
		load.set_on_click([&]()
			{
				SceneManager::instance()->set_gamescene_state_to_load();
				SceneManager::instance()->switch_to(SceneManager::SceneType::Game);
			});

		playback.set_pos(440, 400);
		playback.set_size(240, 60);
		playback.set_image("playback");
		playback.set_on_click([&]()
			{
				SceneManager::instance()->set_gamescene_state_to_playback();
				SceneManager::instance()->switch_to(SceneManager::SceneType::Game);
			});

		enter.set_pos(500, 200);
		enter.set_size(240, 60);
		enter.set_image("enter");
		enter.set_on_click([&]()
			{
				SceneManager::instance()->set_online_host(false);
				SceneManager::instance()->set_online_ip(ip_input.get_text());
				SceneManager::instance()->set_online_port(std::stoi(port_input.get_text()));
				SceneManager::instance()->switch_to(SceneManager::SceneType::Online);

			});

		create.set_pos(500, 360);
		create.set_size(240, 60);
		create.set_image("create");
		create.set_on_click([&]()
			{
				SceneManager::instance()->set_online_host(true);
				SceneManager::instance()->set_online_ip(ip_input.get_text());
				SceneManager::instance()->set_online_port(std::stoi(port_input.get_text()));
				SceneManager::instance()->switch_to(SceneManager::SceneType::Online);
			});

		port_input.set_maxlen(5);
		port_input.set_pos(55,200);
		port_input.set_size(400, 60);
		port_input.set_text_when_blank(L"端口");

		ip_input.set_maxlen(15);
		ip_input.set_pos(55, 360);
		ip_input.set_size(400, 60);
		ip_input.set_text_when_blank(L"ip");

		/*difficulty_selector.set_size({ 100, 60 });
		difficulty_selector.set_position({ 300, 300 });
		difficulty_selector.set_options({ L"简单", L"中等", L"困难" });*/

		black_tip.set_image("black_tip1");
		black_tip.set_position({ 188,120 });
		black_tip.set_size({ 101,45 });

		red_tip.set_image("red_tip1");
		red_tip.set_position({ 510,120 });
		red_tip.set_size({ 101,45 });

		red_player_selector.set_position({ 510, 200 });
		red_player_selector.set_size({ 100, 60 });
		red_player_selector.set_options({ L"真人",L"AI" });
		red_player_selector.set_callback([&]()
			{
				is_red_AI = red_player_selector.GetSelected() == 1;
			});

		red_difficulty_selector.set_position({ 510, 300 });
		red_difficulty_selector.set_size({ 100, 60 });
		red_difficulty_selector.set_options({ L"简单",L"普通", L"困难"});
		red_difficulty_selector.set_callback([&]()
			{
				red_AI_difficulty = red_difficulty_selector.GetSelected();
			});

		black_player_selector.set_position({ 188, 200 });
		black_player_selector.set_size({ 100, 60 });
		black_player_selector.set_options({ L"真人",L"AI" });
		black_player_selector.set_callback([&]()
			{
				is_black_AI = black_player_selector.GetSelected() == 1;
			});

		black_difficulty_selector.set_position({ 188, 300 });
		black_difficulty_selector.set_size({ 100, 60 });
		black_difficulty_selector.set_options({ L"简单",L"普通", L"困难" });
		black_difficulty_selector.set_callback([&]()
			{
				black_AI_difficulty = black_difficulty_selector.GetSelected();
			});
	}

	~SelectScene() = default;

	void on_enter()
	{

	}

	void on_update(int delta)
	{
		benji.on_update(delta);
		lianji.on_update(delta);
		if (isLianji)
		{
			ip_input.on_update(delta);
			port_input.on_update(delta);
		}
	}

	void on_render(const Camera& camera)
	{
		benji.on_render(camera);
		lianji.on_render(camera);
		back.on_render(camera);
		if (isLianji)
		{
			enter.on_render(camera);
			create.on_render(camera);
			ip_input.on_render();
			port_input.on_render();
		}
		else
		{
			startgame.on_render(camera);
			load.on_render(camera);
			playback.on_render(camera);
			red_tip.on_render(camera);
			black_tip.on_render(camera);
			//difficulty_selector.on_render(camera);
			red_player_selector.on_render(camera);
			black_player_selector.on_render(camera);
			if (is_red_AI)
			{
				red_difficulty_selector.on_render(camera);
			}

			if (is_black_AI)
			{
				black_difficulty_selector.on_render(camera);
			}
		}
	}

	void on_input(const ExMessage& msg)
	{
		benji.on_input(msg);
		lianji.on_input(msg);
		back.on_input(msg);
		if (isLianji)
		{
			enter.on_input(msg);
			create.on_input(msg);
			ip_input.on_input(msg);
			port_input.on_input(msg);
		}
		else
		{
			startgame.on_input(msg);
			load.on_input(msg);
			playback.on_input(msg);
			red_player_selector.on_input(msg);
			black_player_selector.on_input(msg);
			if (is_red_AI)
			{
				red_difficulty_selector.on_input(msg);
			}

			if (is_black_AI)
			{
				black_difficulty_selector.on_input(msg);
			}
		}
	}

	void on_exit()
	{
	}

private:

	Button benji;
	Button lianji;
	Button startgame;
	Button back;
	Button playback;
	Button load;
	Button enter;
	Button create;
	bool isLianji = false;

	StaticImage red_tip;
	StaticImage black_tip;

	bool is_red_AI = false;
	bool is_black_AI = false;

	int red_AI_difficulty = 0;
	int black_AI_difficulty = 0;

	OptionSelector red_player_selector;
	OptionSelector black_player_selector;
	OptionSelector red_difficulty_selector;
	OptionSelector black_difficulty_selector;

	TextInput port_input;
	TextInput ip_input;
};
