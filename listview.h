#pragma once
#define NOMINMAX
#include <graphics.h>
#include <vector>
#include <string>
#include <functional>
#include "camera.h"
#include "static_image.h"
#include "button.h"

class ListView
{
public:
    struct Item {
        std::vector<std::wstring> columns;
    };

    ListView() = default;
    virtual ~ListView() = default;

    void set_pos(int x, int y) { this->x = x; this->y = y; }
    void set_size(int w, int h) { this->w = w; this->h = h; }
    void set_column_count(int count) { column_count = count; }
    void set_column_widths(const std::vector<int>& widths) { column_widths = widths; }
    void set_row_height(int height) { row_height = height; }
    void set_items(const std::vector<Item>& items) { this->items = items; }
    void set_header(const Item& header) { this->header = header; }

    void add_item(const Item& item) { items.push_back(item); }
    void clear_items() { items.clear(); scroll_offset = 0; selected_index = -1; }

    void on_render(const Camera& camera);
    void on_input(const ExMessage& msg);
    virtual void on_update(int delta) {}

    void set_on_select(std::function<void(int)> callback) { on_select = callback; }
    int get_selected_index() const { return selected_index; }
    const Item* get_selected_item() const {
        if (selected_index >= 0 && selected_index < (int)items.size())
            return &items[selected_index];
        return nullptr;
    }

protected:
    virtual void on_render_row(const Camera& camera, int row, int row_y, const Item& item);
    virtual void on_input_row(const ExMessage& msg, int row, int row_y) {}

    int x = 0, y = 0, w = 200, h = 200;
    int column_count = 1;
    std::vector<int> column_widths;
    int row_height = 30;
    std::vector<Item> items;
    Item header;
    int scroll_offset = 0; // 滚动的起始行
    int selected_index = -1;
    int visible_row_count = 0;

    std::function<void(int)> on_select;

    bool is_inside(int px, int py) const {
        return (px >= x && px <= x + w && py >= y && py <= y + h);
    }
};

class ListViewWithButton : public ListView
{
public:
    ListViewWithButton() = default;
    ~ListViewWithButton() = default;

    void set_button_image(const std::string& button_name) {
        for (auto& button : detail_buttons) {
            button.set_image(button_name);
            button.set_size(row_height - 8, row_height - 8);
        }
    }
    void on_render_row(const Camera& camera, int row, int row_y, const Item& item) override;
    void on_input_row(const ExMessage& msg, int row, int row_y) override;
	void on_update(int delta) override;
    void set_button_callback(int index, std::function<void()> callback) {
        if (index >= 0 && index < (int)detail_buttons.size()) {
            detail_buttons[index].set_on_click(callback);
        }
	}
    void set_button_count(int count) {
        detail_buttons.resize(count);
	}
private:
    std::vector<Button> detail_buttons;
};