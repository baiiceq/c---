#pragma once
#pragma once
#include <graphics.h>
#include "scene.h"
#include "camera.h"
#include "button.h"
#include "listview.h"
#include "scene_manager.h"

// 排行榜界面
class RankListScene : public Scene
{
public:
    RankListScene()
    {
		background_image.set_image("ranklist_bg");
        background_image.set_position({ 0,0 });
        background_image.set_size({800,640});

        listview.set_pos(135, 100);
        listview.set_size(530, 400);
        listview.set_column_count(4);
        listview.set_column_widths({ 120,170, 120, 120 });
        listview.set_row_height(80);
        ListView::Item header;
        header.columns = { L"排名",L"用户名", L"分数", L"对局数"};
		listview.set_header(header);

        back_btn.set_pos(280, 520);
        back_btn.set_size(240, 60);
        back_btn.set_image("backmenu");
        back_btn.set_on_click([&]() {
            SceneManager::instance()->switch_to(SceneManager::SceneType::Menu);
            });
    }

    ~RankListScene() = default;

    void on_enter() override
    {
        listview.clear_items();

        auto& pool = ResourcesManager::instance()->get_account_pool();
        std::vector<std::pair<std::wstring, int>> sorted;
        for (const auto& a : pool) {
            sorted.push_back({ a.first, a.second.score });
        }
        // 按分数降序排序
        std::sort(sorted.begin(), sorted.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
            });

        int count = 1;
        for (const auto& a : sorted) {
            const auto& info = pool[a.first];
            ListView::Item item;
            item.columns = {
                std::to_wstring(count++),
                a.first,
                std::to_wstring(info.score),
                std::to_wstring(info.matchCount),
            };
            listview.add_item(item);
        }
    }

    void on_update(int delta) override
    {
        listview.on_update(delta);
        back_btn.on_update(delta);
    }

    void on_render(const Camera& camera) override
    {
		background_image.on_render(camera);
        listview.on_render(camera);
        back_btn.on_render(camera);
    }

    void on_input(const ExMessage& msg) override
    {
        listview.on_input(msg);
        back_btn.on_input(msg);
    }

    void on_exit() override
    {
    }

private:
    StaticImage background_image;
    ListView listview;
    Button back_btn;
};