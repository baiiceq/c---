#pragma once

#include "scene.h"
#include "chess_manager.h"
#include "account.h"
#include <iostream>

class SceneManager
{
public:
	enum class SceneType
	{
		Menu,
		Game,
		Setting,
		Select,
		Login,
		Register,
		Hello,
		Myinfo
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

	void set_gamescene_state_to_load(); 
	void set_gamescene_state_to_running();
	void set_gamescene_state_to_playback();
	void set_gamescene_player(bool red, bool black);
	void set_gamescene_difficult(int red, int black);

	void load_player_account(const Account& account);
	void save_player_account();
	Player* get_player_account() const;
private:
	Scene* current_scene = nullptr;

	static SceneManager* manager;

	Scene* menu_scene = nullptr;
	Scene* game_scene = nullptr;
	Scene* setting_scene = nullptr;
	Scene* select_scene = nullptr;
	Scene* login_scene = nullptr;
	Scene* register_scene = nullptr;
	Scene* hello_scene = nullptr;

private:
	Player* player_account = nullptr;
};