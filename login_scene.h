#pragma once
#include "scene.h"
#include "button.h"
#include "static_image.h"
#include "Textbox.h"
#include "scene_manager.h"
#include "account.h"

class LoginScene : public Scene
{
public:
	LoginScene() {
		ConfirmButton.set_pos(280,380);
		ConfirmButton.set_size(240, 60);
		ConfirmButton.set_image("confirm");
		ConfirmButton.set_on_click([&]() {
			state = account_.ValidateLogin();
			if(state==Account::AccountError::None) 
				SceneManager::instance()->load_player_account(account_);
			});

		BackButton.set_pos(280,460);
		BackButton.set_size(240, 60);
		BackButton.set_image("backmenu");
		BackButton.set_on_click([&]() {
			SceneManager::instance()->switch_to(SceneManager::SceneType::Hello);
			});

		LoginText.Set_Textbox(280, 240, 520, 280,12);
		LoginText.set_callback([&]() {
			account_.get_username() = LoginText.get_Textbox();
			});
		PasswordText.Set_Textbox(280, 300, 520, 340, 12);
		PasswordText.set_callback([&]() {
			account_.get_password() = PasswordText.get_Textbox();
			});

		account.set_position({ 170, 240 });
		account.set_size({ 100,40 });
		account.set_image("account");
		
		password.set_position({ 170, 300 });
		password.set_size({ 100,40 });
		password.set_image("password");

		title.set_image("login");
		title.set_position({ 248,90 });
		title.set_size({ 401,86 });

		NotrightText.add_frame(ResourcesManager::instance()->find_image("notright"), 1);
		NotrightText.set_position({ 320, 380 });
		NotrightText.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		NotrightText.set_loop(false);
		NotrightText.set_interval(5000);
		NotrightText.set_on_finished([&]() {
			state = Account::AccountError::Null;});

		LoginSucessText.add_frame(ResourcesManager::instance()->find_image("loginsuccess"), 1);
		LoginSucessText.set_position({ 320, 380 });
		LoginSucessText.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		LoginSucessText.set_loop(false);
		LoginSucessText.set_interval(1000);
		LoginSucessText.set_on_finished([&]() {
			SceneManager::instance()->switch_to(SceneManager::SceneType::Menu);
			});
	}
	~LoginScene() {}
	void on_enter() {}
	void on_exit() {
		reset();
	}
	void on_update(int delta) {
		LoginText.on_update(delta);
		PasswordText.on_update(delta);
		if(state== Account::AccountError::NotRight) {
			NotrightText.on_update(delta);
		} else if(state == Account::AccountError::None) {
			LoginSucessText.on_update(delta);
		}
	}
	void on_render(const Camera& camera) {
		ConfirmButton.on_render(camera);
		BackButton.on_render(camera);
		LoginText.on_render(camera);
		PasswordText.on_render(camera);
		title.on_render(camera);
		account.on_render(camera);
		password.on_render(camera);
		switch(state) {
			case Account::AccountError::Null:
				break;
			case Account::AccountError::None:
				LoginSucessText.on_render(camera);
				break;
			case Account::AccountError::NotRight:
				NotrightText.on_render(camera);
				break;
			default:
				break;
		}
	}
	void on_input(const ExMessage& msg) {
		LoginText.on_input(msg);
		PasswordText.on_input(msg);
		ConfirmButton.on_input(msg);
		BackButton.on_input(msg);
	}
private:
	void reset() {
		LoginText.Clear();
		PasswordText.Clear();
		NotrightText.reset();
		LoginSucessText.reset();
		state = Account::AccountError::Null;
	}
private:
	Account account_;

	Account::AccountError state = Account::AccountError::Null;

	Animation NotrightText;
	Animation LoginSucessText;

	Button ConfirmButton;
	Button BackButton;
	Textbox LoginText;
	TextboxSecurity PasswordText;
	StaticImage title;
	StaticImage account;
	StaticImage password;
};