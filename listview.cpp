#include "ListView.h"
#include <algorithm>

void ListView::on_render(const Camera& camera)
{
    setfillcolor(RGB(255, 200, 120));
    solidrectangle(x, y, x + w, y + h);

    int col_x = x;
    setfillcolor(RGB(255, 140, 0));
    solidrectangle(x, y, x + w, y + row_height);
    settextcolor(WHITE);
    settextstyle(42, 0, _T("Î¢ÈíÑÅºÚ"));
    for (int c = 0; c < column_count; ++c) {
        int col_w = (column_widths.size() > c) ? column_widths[c] : w / column_count;
        roundrect(col_x, y, col_x + col_w, y + row_height, 12, 12);
        if (c < (int)header.columns.size())
            outtextxy(col_x + 5, y + 5, header.columns[c].c_str());
        col_x += col_w;
    }

    visible_row_count = (h - row_height) / row_height;
    int start = scroll_offset;
    int end = std::min(start + visible_row_count, (int)items.size());
    for (int i = start; i < end; ++i) {
        int row_y = y + row_height * (i - start + 1);
        on_render_row(camera, i, row_y, items[i]);
    }
}

void ListView::on_render_row(const Camera&, int row, int row_y, const Item& item)
{
    if ((row - scroll_offset) % 2 == 0)
        setfillcolor(RGB(255, 230, 180));
    else
        setfillcolor(RGB(255, 245, 210));
    solidrectangle(x, row_y, x + w, row_y + row_height);

    if (row == selected_index) {
        setfillcolor(RGB(255, 180, 60));
        solidrectangle(x, row_y, x + w, row_y + row_height);
        setlinecolor(RGB(255, 120, 0));
        roundrect(x, row_y, x + w, row_y + row_height, 8, 8);
    }

    int col_x = x;
    settextcolor(BLACK);
    for (int c = 0; c < column_count; ++c) {
        int col_w = (column_widths.size() > c) ? column_widths[c] : w / column_count;
        roundrect(col_x, row_y, col_x + col_w, row_y + row_height, 8, 8);
        if (c < (int)item.columns.size()) {
            outtextxy(col_x + 5, row_y + 5, item.columns[c].c_str());
        }
        col_x += col_w;
    }
}

void ListView::on_input(const ExMessage& msg)
{
    if (msg.message == WM_LBUTTONDOWN) {
        if (is_inside(msg.x, msg.y)) {
            int row = (msg.y - y - row_height) / row_height + scroll_offset;
            if (row >= 0 && row < (int)items.size()) {
                selected_index = row;
                if (on_select) on_select(selected_index);
            }
        }
    }
    if (msg.message == WM_MOUSEWHEEL) {
        if (is_inside(msg.x, msg.y)) {
            int total_rows = (int)items.size();
            if (msg.wheel > 0 && scroll_offset > 0) {
                scroll_offset--;
            }
            if (msg.wheel < 0 && scroll_offset + visible_row_count < total_rows) {
                scroll_offset++;
            }
        }
    }
    int start = scroll_offset;
    int end = std::min(start + visible_row_count, (int)items.size());
    for (int i = start; i < end; ++i) {
        int row_y = y + row_height * (i - start + 1);
        on_input_row(msg, i, row_y);
    }
}




void ListViewWithButton::on_render_row(const Camera& camera, int row, int row_y, const Item& item)
{
    ListView::on_render_row(camera, row, row_y, item);
    Button& btn = detail_buttons[row];
    btn.on_render(camera);
}

void ListViewWithButton::on_input_row(const ExMessage& msg, int row, int row_y)
{
	detail_buttons[row].set_pos(x + w - column_widths.back() + 8, row_y + 4);
	detail_buttons[row].set_size(column_widths.back(), row_height);
    detail_buttons[row].on_input(msg);
}

void ListViewWithButton::on_update(int delta)
{
    for (auto& btn : detail_buttons) {
        btn.on_update(delta);
	}
}