#pragma once
#include <graphics.h>
#include <string>
#include "scene.h"
#include "camera.h"
#include "button.h"
#include "Textbox.h"
#include "scene_manager.h"
#include "resources_manager.h"
#include "account.h"
#include "util.h"

class SettingScene : public Scene
{
public:
    SettingScene()
    {
        username_box.Set_Textbox(300, 120, 500, 170, 32);
        username_box.set_text(L"");
        username_box.set_callback([this]() {
            });

        password_box.Set_Textbox(300, 200, 500, 250, 32);
        password_box.set_text(L"");
        password_box.set_callback([this]() {
            });

        volume_box.Set_Textbox(350, 280, 450, 330, 4);
        volume_box.set_callback([this]() {
            int val = 50;
            try { val = std::stoi(volume_box.get_Textbox()); }
            catch (...) { val = 50; }
            if (val < 0) val = 0;
            if (val > 100) val = 100;
            //set_audio_volume(_T("bgm"), val * 10); // 假设bgm为音乐别名
            });

        countdown_box.Set_Textbox(350, 360, 450, 410, 4);
        countdown_box.set_callback([this]() {
            int val = 30;
            try { val = std::stoi(countdown_box.get_Textbox()); }
            catch (...) { val = 30; }
            if (val < 5) val = 5;
            if (val > 300) val = 300;
            // 可在此处保存倒计时设置
            });

        back_btn.set_pos(280, 430);
        back_btn.set_size(240, 60);
        back_btn.set_image("backmenu");
        back_btn.set_on_click([&]() {
            SceneManager::instance()->switch_to(SceneManager::SceneType::Menu);
            });

        confirm.set_image("confirm");
		confirm.set_pos(280, 500);
        confirm.set_size(240, 60);
        confirm.set_on_click([&]() {
            std::wstring& fusername = SceneManager::instance()->get_player_account()->get_username();
            std::wstring lusername = username_box.get_Textbox();
            std::unordered_map<std::wstring, Account::AccountInfo>& pool = ResourcesManager::instance()->get_account_pool();
            auto it = pool.find(fusername);
            if (it != pool.end()) {
                if(fusername == lusername){}
                else if (pool.find(lusername) != pool.end())
                {
                    MessageBox(nullptr, L"用户名已存在，请更换用户名！", L"错误", MB_OK | MB_ICONERROR);
                    return;
                }
                pool[lusername] = it->second;
                pool.erase(it);
				pool[lusername].password= password_box.get_Textbox();
            }
            auto* player = SceneManager::instance()->get_player_account();
            if (player) {
                player->get_username() = username_box.get_Textbox();
                player->get_password() = password_box.get_Textbox();
            }
            // 可保存音量和倒计时到全局设置
			ResourcesManager::instance()->get_volume() = std::stoi(volume_box.get_Textbox());
            SceneManager::instance()->set_gamescene_limit_time(std::stoi(countdown_box.get_Textbox())*1000);
            SceneManager::instance()->switch_to(SceneManager::SceneType::Menu);
			});
    }

    void on_enter() override
    {
        // 进入时加载当前账号信息
        auto* player = SceneManager::instance()->get_player_account();
        if (player) {
            username_box.set_text(player->get_username());
            password_box.set_text(player->get_password());
        }
        // 假设有全局音量和倒计时设置
		int volume = ResourcesManager::instance()->get_volume();
		volume_box.set_text(std::to_wstring(volume));
		int countdown = SceneManager::instance()->get_gamescene_limit_time();
        countdown /= 1000;
		countdown_box.set_text(std::to_wstring(countdown));
    }

    void on_update(int delta) override
    {
        username_box.on_update(delta);
        password_box.on_update(delta);
        volume_box.on_update(delta);
        countdown_box.on_update(delta);
        back_btn.on_update(delta);
        confirm.on_update(delta);
    }

    void on_render(const Camera& camera) override
    {
        settextstyle(32, 0, _T("微软雅黑"));
        settextcolor(BLACK);
        outtextxy(180, 130, L"用户名");
        outtextxy(180, 210, L"密码");
        outtextxy(180, 290, L"音量");
        outtextxy(180, 370, L"局内倒计时");

        username_box.on_render(camera);
        password_box.on_render(camera);
        volume_box.on_render(camera);
        countdown_box.on_render(camera);
        back_btn.on_render(camera);
		confirm.on_render(camera);
    }

    void on_input(const ExMessage& msg) override
    {
        username_box.on_input(msg);
        password_box.on_input(msg);
        volume_box.on_input(msg);
        countdown_box.on_input(msg);
        back_btn.on_input(msg);
		confirm.on_input(msg);
    }

    void on_exit() override {}

private:
    TextboxSwitch username_box;
    TextboxSwitch password_box;
    TextboxButton volume_box;
    TextboxButton countdown_box;
    Button back_btn;
    Button confirm;
};