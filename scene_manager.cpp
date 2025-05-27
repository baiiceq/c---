#include "scene_manager.h"
#include "menu_scene.h"
#include "game_scene.h"
#include "select_scene.h"

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

	current_scene = menu_scene;
	current_scene->on_enter();
}

SceneManager::~SceneManager()
{
	delete menu_scene;
	delete game_scene;
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
