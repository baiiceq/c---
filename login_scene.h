#pragma once
#include "scene.h"
#include "button.h"
#include "static_image.h"
#include "Textbox.h"
#include "scene_manager.h"

class LoginScene : public Scene
{
public:
	LoginScene() {
		ConfirmButton.set_pos(410,480);
		ConfirmButton.set_size(110, 60);
		ConfirmButton.set_image("confirm");
		ConfirmButton.set_on_click([&]() {
			// Handle login confirmation logic here
			});

		BackButton.set_pos(280,480);
		BackButton.set_size(110, 60);
		BackButton.set_image("backmenu");
		BackButton.set_on_click([&]() {
			SceneManager::instance()->switch_to(SceneManager::SceneType::Hello);
			});

		LoginText.Set_Textbox(280, 240, 520, 300,20);
		PasswordText.Set_Textbox(280, 360, 520, 420, 20);

		account.set_position({ 170, 240 });
		account.set_size({ 100,60 });
		account.set_image("account");
		
		password.set_position({ 170, 360 });
		password.set_size({ 100,60 });
		password.set_image("password");

		title.set_image("title");
		title.set_position({ 248,90 });
		title.set_size({ 303,86 });

	}
	~LoginScene() {}
	void on_enter() {}
	void on_exit() {
		reset();
	}
	void on_update(int delta) {
		ConfirmButton.on_update(delta);
		BackButton.on_update(delta);
		LoginText.on_update(delta);
		PasswordText.on_update(delta);
	}
	void on_render(const Camera& camera) {
		ConfirmButton.on_render(camera);
		BackButton.on_render(camera);
		LoginText.on_render(camera);
		PasswordText.on_render(camera);
		title.on_render(camera);
		account.on_render(camera);
		password.on_render(camera);
	}
	void on_input(const ExMessage& msg) {
		ConfirmButton.on_input(msg);
		BackButton.on_input(msg);
		LoginText.on_input(msg);
		PasswordText.on_input(msg);
	}
private:
	void reset() {
		LoginText.Clear();
		PasswordText.Clear();
	}
private:
	Button ConfirmButton;
	Button BackButton;
	Textbox LoginText;
	Textbox PasswordText;
	StaticImage title;
	StaticImage account;
	StaticImage password;
};