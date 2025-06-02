#include "scene_manager.h"
#include "menu_scene.h"
#include "game_scene.h"
#include "select_scene.h"
#include "online_scene.h"
#include "login_scene.h"
#include "register_scene.h"
#include "hello_scene.h"
#include "ranklist_scene.h"
#include "myinfo_scene.h"
#include "setting_scene.h"

SceneManager* SceneManager::manager = nullptr;

SceneManager* SceneManager::instance()
{
	if (!manager)
		manager = new SceneManager();

	return manager;
}

SceneManager::SceneManager()
{
	menu_scene = new MenuScene();
	game_scene = new GameScene();
	select_scene = new SelectScene();
	online_scene = new OnlineScene();
	login_scene = new LoginScene();
	register_scene = new RegisterScene();
	hello_scene = new HelloScene();
	ranklist_scene = new RankListScene();
	myinfo_scene = new MyInfoScene();
	setting_scene = new SettingScene();
	current_scene = hello_scene;
	current_scene->on_enter();
}

SceneManager::~SceneManager()
{
	delete menu_scene;
	delete game_scene;
	delete select_scene;
	delete online_scene;
	delete login_scene;
	delete register_scene;
	delete hello_scene;
	delete ranklist_scene;
	delete myinfo_scene;
	delete setting_scene;
}

void SceneManager::set_current_scene(Scene* scene)
{
	current_scene = scene;
	current_scene->on_enter();
}

void SceneManager::switch_to(SceneType type)
{
	current_scene->on_exit();
	switch (type)
	{
	case SceneType::Menu:
		current_scene = menu_scene;
		break;
	case SceneType::Game:
		current_scene = game_scene;
		break;
	case SceneType::Setting:
		current_scene = setting_scene;
		break;
	case SceneType::Select:
		current_scene = select_scene;
		break;
	case SceneType::Login:
		current_scene = login_scene;
		break;
	case SceneType::Hello:
		current_scene = hello_scene;
		break;
	case SceneType::Online:
		current_scene = online_scene;
		break;
	case SceneType::Register:
		current_scene = register_scene;
		break;
	case SceneType::Ranklist:
		current_scene = ranklist_scene;
		break;
	case SceneType::Myinfo:
		current_scene = myinfo_scene;
		break;
	default:
		break;
	}
	current_scene->on_enter();
}

void SceneManager::on_update(int delta)
{
	current_scene->on_update(delta);
}

void SceneManager::on_render(const Camera& camera)
{
	current_scene->on_render(camera);
}

void SceneManager::on_input(ExMessage& msg)
{
	current_scene->on_input(msg);
}

void SceneManager::set_gamescene_state_to_load()
{
	GameScene* gs = (GameScene*)game_scene;
	gs->set_state(GameScene::GameState::GameLoad);
}

void SceneManager::set_gamescene_state_to_running()
{
	GameScene* gs = (GameScene*)game_scene;
	gs->set_state(GameScene::GameState::GameRunning);
}

void SceneManager::set_gamescene_state_to_playback()
{
	GameScene* gs = (GameScene*)game_scene;
	gs->set_state(GameScene::GameState::GamePlayBack);
}

void SceneManager::set_gamescene_player(bool red, bool black)
{
	GameScene* gs = (GameScene*)game_scene;
	gs->set_player(red, black);
}

void SceneManager::set_gamescene_difficult(int red, int black)
{
	GameScene* gs = (GameScene*)game_scene;
	gs->set_difficulty(red, black);
}

void SceneManager::load_player_account(const Account& account)
{
	player_account= new Player(account);
}

void SceneManager::save_player_account()
{
	if (player_account)
		player_account->save();
}

Player* SceneManager::get_player_account()const
{
	return player_account;
}
void SceneManager::set_online_host(bool is_host)
{
	OnlineScene* os = (OnlineScene*)online_scene;
	os->set_is_host(is_host);
}

void SceneManager::set_online_ip(const std::string& ip)
{
	OnlineScene* os = (OnlineScene*)online_scene;
	os->set_ip(ip);
}

void SceneManager::set_online_port(int port)
{
	OnlineScene* os = (OnlineScene*)online_scene;
	os->set_port(port);
}
void SceneManager::set_gamescene_load_path(const std::string& path)
{
	GameScene* gs = (GameScene*)game_scene;
	gs->set_load_path(path);
}
void SceneManager::set_gamescene_limit_time(int time)
{
	GameScene* gs = (GameScene*)game_scene;
	gs->set_chess_manager_turn_time(time);
}
int SceneManager::get_gamescene_limit_time()
{
	GameScene* gs = (GameScene*)game_scene;
	return gs->get_chess_manager_turn_time();
}
