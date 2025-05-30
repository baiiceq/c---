#pragma once

#include "scene.h"
#include "atlas.h"
#include "timer.h"
#include "camera.h"
#include "animation.h"
#include "scene_manager.h"
#include "button.h"
#include "static_image.h"

// 主菜单界面

class MenuScene : public Scene
{
public:
	MenuScene()
	{
		// 初始化各种按钮
		startgame.set_pos(280, 240);
		startgame.set_size(240, 60);
		startgame.set_image("startgame");
		startgame.set_on_click([&]()
			{
				SceneManager::instance()->switch_to(SceneManager::SceneType::Select);
			});

		setting.set_pos(280, 360);
		setting.set_size(240, 60);
		setting.set_image("setting");
		setting.set_on_click([&]()
			{
				
			});

		exit.set_pos(280, 480);
		exit.set_size(240, 60);
		exit.set_image("exit");
		exit.set_on_click([&]()
			{
				::exit(0);
			});

		title.set_image("title");
		title.set_position({ 248,90 });
		title.set_size({ 303,86 });
	}

	~MenuScene() = default;

	void on_enter()
	{
	}

	void on_update(int delta)
	{
		startgame.on_update(delta);
		setting.on_update(delta);
		exit.on_update(delta);
	}

	void on_render(const Camera& camera)
	{
		startgame.on_render(camera);
		setting.on_render(camera);
		exit.on_render(camera);
		title.on_render(camera);
	}

	void on_input(const ExMessage& msg)
	{
		startgame.on_input(msg);
		setting.on_input(msg);
		exit.on_input(msg);
	}

	void on_exit()
	{
		std::cout << "退出主菜单" << std::endl;
	}

private:

	Button startgame;
	Button setting;
	Button exit;
	StaticImage title;

};
