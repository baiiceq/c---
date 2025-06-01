#pragma once

#include "scene.h"
#include "atlas.h"
#include "timer.h"
#include "camera.h"
#include "animation.h"
#include "scene_manager.h"
#include "button.h"
#include "static_image.h"
#include <fstream>
#include <filesystem>

// 暂停界面

class PauseScene : public Scene
{
public:
	PauseScene()
	{
		continue_game.set_pos(280, 240);
		continue_game.set_size(240, 60);
		continue_game.set_image("startgame");
		continue_game.set_on_click([&]()
			{
				if (callback_continue)
					callback_continue();
			});

		exit.set_pos(280, 340);
		exit.set_size(240, 60);
		exit.set_image("exit");
		exit.set_on_click([&]()
			{
				if (callback_exit)
					callback_exit();
				SceneManager::instance()->switch_to(SceneManager::SceneType::Menu);
			});

		background.set_image("pause_background");
		background.set_size({ 400,240 });
		background.set_position({ 200,200 });

		mask.set_image("pause_mask");
		mask.set_size({ 800,640 });
		mask.set_position({ 0,0 });
	}

	~PauseScene() = default;

	void on_enter()
	{
	}

	void on_update(int delta)
	{
	}

	void on_render(const Camera& camera)
	{
		mask.on_render(camera);
		background.on_render(camera);
		exit.on_render(camera);
		continue_game.on_render(camera);
	}

	void on_input(const ExMessage& msg)
	{
		if (msg.message == WM_KEYDOWN && msg.vkcode == VK_ESCAPE)
		{
			if (callback_continue)
				callback_continue();
		}
		exit.on_input(msg);
		continue_game.on_input(msg);
	}

	void on_exit()
	{
	}

	void set_callback_continue(std::function<void()> callback)
	{
		callback_continue = callback;
	}

	void set_callback_exit(std::function<void()> callback)
	{
		callback_exit = callback;
	}

private:

	Button continue_game;
	Button exit;
	StaticImage background;
	StaticImage mask;

	// 点击继续游戏的回调函数，回到游戏界面
	std::function<void()> callback_continue;

	std::function<void()> callback_exit;
};
