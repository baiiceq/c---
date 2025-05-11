#pragma once

#include "scene.h"
#include "atlas.h"
#include "timer.h"
#include "camera.h"
#include "animation.h"
#include "scene_manager.h"
#include "button.h"

class MenuScene : public Scene
{
public:
	MenuScene() = default;
	~MenuScene() = default;

	void on_enter()
	{
		startgame.set_pos(20, 20);
		startgame.set_size(240, 60);
		startgame.set_image("startgame");
		startgame.set_on_click([&]()
			{
				SceneManager::instance()->switch_to(SceneManager::SceneType::Game);
			});
	}

	void on_update(int delta)
	{
		startgame.on_update(delta);
	}

	void on_render(const Camera& camera)
	{
		startgame.on_render(camera);
	}

	void on_input(const ExMessage& msg)
	{
		startgame.on_input(msg);
	}

	void on_exit()
	{
		std::cout << "ÍË³öÖ÷²Ëµ¥" << std::endl;
	}

private:
	Button startgame;
};
