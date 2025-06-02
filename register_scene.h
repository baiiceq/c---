 #pragma once
#include "scene.h"
#include "button.h"
#include "static_image.h"
#include "Textbox.h"
#include "scene_manager.h"
#include "account.h"

class RegisterScene : public Scene
{
public:
	RegisterScene() {
		ConfirmButton.set_pos(280, 380);
		ConfirmButton.set_size(240, 60);
		ConfirmButton.set_image("confirm");
		ConfirmButton.set_on_click([&]() {
			state = account_.ValidateRegister();
			if (state == Account::AccountError::None)
				account_.add_account();
			});
		BackButton.set_pos(280, 460);
		BackButton.set_size(240, 60);
		BackButton.set_image("backmenu");
		BackButton.set_on_click([&]() {
			SceneManager::instance()->switch_to(SceneManager::SceneType::Hello);
			});

		RegisterText.Set_Textbox(280, 240, 520, 280, 12);
		RegisterText.set_callback([&]() {
			account_.get_username() = RegisterText.get_Textbox();
			});
		PasswordText.Set_Textbox(280, 300, 520, 340, 12);
		PasswordText.set_callback([&]() {
			account_.get_password() = PasswordText.get_Textbox();
			});

		account.set_position({ 150, 240 });
		account.set_size({ 130, 40 });
		account.set_image("newusername");

		password.set_position({ 170, 300 });
		password.set_size({ 100, 40 });
		password.set_image("newpassword");

		title.set_image("register");
		title.set_position({ 248, 90 });
		title.set_size({ 401, 86 });

		ExistText.add_frame(ResourcesManager::instance()->find_image("usernameexist"), 1);
		ExistText.set_position({ 320, 380 });
		ExistText.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		ExistText.set_loop(false);
		ExistText.set_interval(5000);
		ExistText.set_on_finished([&]() {
			state = Account::AccountError::Null;});

		RegisterSuccessText.add_frame(ResourcesManager::instance()->find_image("registersuccess"), 1);
		RegisterSuccessText.set_position({ 320, 380 });
		RegisterSuccessText.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		RegisterSuccessText.set_loop(false);
		RegisterSuccessText.set_interval(1000);
		RegisterSuccessText.set_on_finished([&]() {
			SceneManager::instance()->switch_to(SceneManager::SceneType::Login);
			});

		InvalidUsernameText.add_frame(ResourcesManager::instance()->find_image("invalidusername"), 1);
		InvalidUsernameText.set_position({ 320, 380 });
		InvalidUsernameText.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		InvalidUsernameText.set_loop(false);
		InvalidUsernameText.set_interval(5000);
		InvalidUsernameText.set_on_finished([&]() {
			state = Account::AccountError::Null;});

		InvalidPasswordText.add_frame(ResourcesManager::instance()->find_image("invalidpassword"), 1);
		InvalidPasswordText.set_position({ 320, 380 });
		InvalidPasswordText.set_anchor_mode(Animation::AnchorMode::BottomCentered);
		InvalidPasswordText.set_loop(false);
		InvalidPasswordText.set_interval(5000);
		InvalidPasswordText.set_on_finished([&]() {
			state = Account::AccountError::Null;});
	}
	~RegisterScene() {}
	void on_enter() {}
	void on_exit() {
		reset();
	}

	void on_update(int delta) 
	{
		ConfirmButton.on_update(delta);
		BackButton.on_update(delta);
		RegisterText.on_update(delta);
		PasswordText.on_update(delta);
		if(state == Account::AccountError::None) {
			RegisterSuccessText.on_update((float)delta);
		} else if (state == Account::AccountError::UsernameAlreadyExists) {
			ExistText.on_update((float)delta);
		} else if (state == Account::AccountError::InvalidUsername) {
			InvalidUsernameText.on_update((float)delta);
		} else if (state == Account::AccountError::InvalidPassword) {
			InvalidPasswordText.on_update((float)delta);
		}
	}
	void on_render(const Camera& camera) {
		ConfirmButton.on_render(camera);
		BackButton.on_render(camera);
		RegisterText.on_render(camera);
		PasswordText.on_render(camera);
		title.on_render(camera);
		account.on_render(camera);
		password.on_render(camera);
		switch (state) {
		case Account::AccountError::Null:
			break;
		case Account::AccountError::None:
			RegisterSuccessText.on_render(camera);
			break;
		case Account::AccountError::UsernameAlreadyExists:
			ExistText.on_render(camera);
			break;
		case Account::AccountError::InvalidUsername:
			InvalidUsernameText.on_render(camera);
			break;
		case Account::AccountError::InvalidPassword:
			InvalidPasswordText.on_render(camera);
			break;
		default:
			break;
		}
	}
	void on_input(const ExMessage& msg) {
		RegisterText.on_input(msg);
		PasswordText.on_input(msg);
		ConfirmButton.on_input(msg);
		BackButton.on_input(msg);
	}
private:
	void reset() {
		RegisterText.Clear();
		PasswordText.Clear();
		state = Account::AccountError::Null;
		ExistText.reset();
		RegisterSuccessText.reset();
		InvalidUsernameText.reset();
		InvalidPasswordText.reset();
	}
private:
	Account account_;
	Account::AccountError state = Account::AccountError::Null;

	Animation ExistText;
	Animation RegisterSuccessText;
	Animation InvalidUsernameText;
	Animation InvalidPasswordText;

	Button ConfirmButton;
	Button BackButton;
	Textbox RegisterText;
	TextboxSecurity PasswordText;
	StaticImage title;
	StaticImage account;
	StaticImage password;
};