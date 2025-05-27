#pragma once

#include "scene.h"
#include "chess_manager.h"
#include <iostream>

class SceneManager
{
public:
	enum class SceneType
	{
		Menu,
		Game,
		Setting,
		Select
	};

	static SceneManager* instance();

public:
	SceneManager();
	~SceneManager();

	void set_current_scene(Scene* scene);
	
	void switch_to(SceneType type);

	void on_update(int delta);

	void on_render(const Camera& camera);

	void on_input(ExMessage& msg);

private:
	Scene* current_scene = nullptr;

	static SceneManager* manager;

	Scene* menu_scene = nullptr;
	Scene* game_scene = nullptr;
	Scene* setting_scene = nullptr;
	Scene* select_scene = nullptr;
};