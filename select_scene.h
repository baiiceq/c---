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
				SceneManager::instance()->switch_to(SceneManager::SceneType::Game);
			});

		back.set_pos(120, 500);
		back.set_size(240, 60);
		back.set_image("backmenu");
		back.set_on_click([&]()
			{
				SceneManager::instance()->switch_to(SceneManager::SceneType::Menu);
			});

		difficulty_selector.set_size({ 120, 80 });
		difficulty_selector.set_position({ 300, 300 });
		difficulty_selector.set_options({ L"简单", L"中等", L"困难" });
	}

	~SelectScene() = default;

	void on_enter()
	{
	}

	void on_update(int delta)
	{
		benji.on_update(delta);
		lianji.on_update(delta);
	}

	void on_render(const Camera& camera)
	{
		benji.on_render(camera);
		lianji.on_render(camera);
		startgame.on_render(camera);
		back.on_render(camera);
		if (isLianji)
		{
			
		}
		else
		{
			difficulty_selector.on_render(camera);
		}
	}

	void on_input(const ExMessage& msg)
	{
		benji.on_input(msg);
		lianji.on_input(msg);
		startgame.on_input(msg);
		back.on_input(msg);
		if (isLianji)
		{

		}
		else
		{
			difficulty_selector.on_input(msg);
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
	bool isLianji = false;
	OptionSelector difficulty_selector;
};
