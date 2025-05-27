#include "option_selector.h"

OptionSelector::OptionSelector()
{
    selected = 0;

    left.set_image("leftarrow");
    left.set_on_click([&]() 
        {
        if (selected > 0) 
        {
            selected--;
            if (on_select_callback) on_select_callback(selected);
        }
        });

    right.set_image("rightarrow");
    right.set_on_click([&]() 
        {
        if (selected < options.size() - 1) 
        {
            selected++;
            if (on_select_callback) on_select_callback(selected);
        }
        });
}

OptionSelector::~OptionSelector()
{
}

void OptionSelector::on_render(const Camera& camera)
{
    left.on_render(camera);
    right.on_render(camera);

    std::wstring text = GetSelectedText();

    int font_height = (int)(size.y * 0.5f);
    settextstyle(font_height, 0, _T("Î¢ÈíÑÅºÚ"));
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);

    int btn_size = (int)(size.y * 0.8f);

    float frame_x = position.x;
    float frame_y = position.y;
    float frame_w = size.x;
    float frame_h = size.y;

    setfillcolor(RGB(230, 230, 230)); 
    solidrectangle((int)frame_x, (int)frame_y, (int)(frame_x + frame_w), (int)(frame_y + frame_h));

    setlinecolor(BLACK);
    setlinestyle(PS_SOLID, 2); 
    rectangle((int)frame_x, (int)frame_y, (int)(frame_x + frame_w), (int)(frame_y + frame_h));

    int tw = textwidth(text.c_str());
    int th = textheight(text.c_str());
    float draw_x = frame_x + (frame_w - tw) / 2;
    float draw_y = frame_y + (frame_h - th) / 2;

    outtextxy((int)draw_x, (int)draw_y, text.c_str());
}

void OptionSelector::on_input(const ExMessage& msg)
{
    left.on_input(msg);
    right.on_input(msg);
}


void OptionSelector::update_button_layout()
{
    float btn_size = size.y * 0.3; 
    float btn_y = position.y + (size.y - btn_size) / 2;

    int spacing = size.x * 0.4;
    left.set_size( btn_size, btn_size );
    right.set_size( btn_size,btn_size );

    left.set_pos(position.x - spacing, btn_y);
    right.set_pos(position.x + size.x - btn_size + spacing, btn_y);
}
