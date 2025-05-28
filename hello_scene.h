#pragma once
#include "scene.h"
#include "animation.h"
#include "button.h"
#include "static_image.h"
#include "scene_manager.h"

class HelloScene : public Scene {
public:
	HelloScene() {
		OnceLoginButton.set_pos(280,240);
		OnceLoginButton.set_image("once_login");
		OnceLoginButton.set_size(240, 60);
		OnceLoginButton.set_on_click([]() {
			SceneManager::instance()->switch_to(SceneManager::SceneType::Menu);
			});

		PlayerLoginButton.set_pos(280,330);
		PlayerLoginButton.set_image("account_login");
		PlayerLoginButton.set_size(240, 60);
		PlayerLoginButton.set_on_click([]() {
			SceneManager::instance()->switch_to(SceneManager::SceneType::Login);
			});

		RegisterButton.set_pos(280,420);
		RegisterButton.set_image("register");
		RegisterButton.set_size(240, 60);
		RegisterButton.set_on_click([]() {
			SceneManager::instance()->switch_to(SceneManager::SceneType::Register);
			});

		ExitButton.set_pos(280,510);
		ExitButton.set_image("exit");
		ExitButton.set_size(240, 60);
		ExitButton.set_on_click([]() {
			exit(0);
			});
	}
	~HelloScene() = default;
	void on_enter() {}
	void on_exit() {}
	void on_update(int delta) {
		//Hello.on_update(delta);
	}
	void on_render(const Camera& camera) {
		//Hello.on_render(camera);
		OnceLoginButton.on_render(camera);
		PlayerLoginButton.on_render(camera);
		RegisterButton.on_render(camera);
		ExitButton.on_render(camera);
	}
	void on_input(const ExMessage& message) {
		OnceLoginButton.on_input(message);
		PlayerLoginButton.on_input(message);
		RegisterButton.on_input(message);
		ExitButton.on_input(message);
	}
private:
	/*Animation Hello;*/
	Button OnceLoginButton;
	Button PlayerLoginButton;
	Button RegisterButton;
	Button ExitButton;
};