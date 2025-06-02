#pragma once
#include <graphics.h>
#include <string>
#include <vector>
#include "scene.h"
#include "camera.h"
#include "button.h"
#include "listview.h"
#include "scene_manager.h"
#include "account.h"
#include "game_scene.h"

// ������Ϣ����
class MyInfoScene : public Scene
{
public:
    MyInfoScene()
    {
        listview.set_pos(0, 80);
        listview.set_size(800, 400);
        listview.set_column_count(5);
        listview.set_column_widths({ 160, 120, 80, 360, 80 });
        listview.set_row_height(60);

        ListView::Item header;
        header.columns = { L"ģʽ", L"����", L"���", L"ʱ��", L"����" };
        listview.set_header(header);

        back_btn.set_pos(420, 550);
        back_btn.set_size(120, 50);
        back_btn.set_image("backmenu");
        back_btn.set_on_click([&]() {
            SceneManager::instance()->switch_to(SceneManager::SceneType::Menu);
            });
    }

    ~MyInfoScene() = default;

    void on_enter() override
    {
        listview.clear_items();
        auto* player = SceneManager::instance()->get_player_account();
        if (!player) return;
        const auto& records = player->get_gamerecords();
		listview.set_button_count(records.size());
        for (size_t i = 0; i < records.size(); ++i) {
            const auto& rec = records[i];
            ListView::Item item;
            item.columns = {
                mode_to_wstring(rec.gameMode),
                rec.opponentName,
                result_to_wstring(rec.result),
                rec.time,
                L"" // ���һ�����գ���ʾ��ť
            };
            listview.add_item(item);
            listview.set_button_callback(i, [&]() {
                std::string path = "data\\move_history\\" + std::string(rec.move_history.begin(), rec.move_history.end()) + ".txt";
                SceneManager::instance()->set_gamescene_load_path(path);
                SceneManager::instance()->set_gamescene_state_to_playback();
				SceneManager::instance()->switch_to(SceneManager::SceneType::Game);
				});
        }
        listview.set_button_image("huifang");
    }

    void on_update(int delta) override
    {
        listview.on_update(delta);
        back_btn.on_update(delta);
    }

    void on_render(const Camera& camera) override
    {
        listview.on_render(camera);
        back_btn.on_render(camera);
    }

    void on_input(const ExMessage& msg) override
    {
        listview.on_input(msg);
        back_btn.on_input(msg);
    }

    void on_exit() override {}

private:
    std::wstring mode_to_wstring(Player::mode m) {
        switch (m) {
        case Player::mode::localpk: return L"���ض�ս";
        case Player::mode::Aipk: return L"�˻���ս";
        case Player::mode::lianjipk: return L"������ս";
        default: return L"-";
        }
    }
    std::wstring result_to_wstring(Player::gameresult r) {
        switch (r) {
        case Player::gameresult::Win: return L"ʤ��";
        case Player::gameresult::Lose: return L"ʧ��";
        case Player::gameresult::Draw: return L"ƽ��";
        case Player::gameresult::Notend: return L"�ж�";
        case Player::gameresult::Redwin: return L"��ʤ";
        case Player::gameresult::Blackwin: return L"��ʤ";
        default: return L"-";
        }
    }

    ListViewWithButton listview;
    Button back_btn;
};