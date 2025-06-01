#include <cwchar>
#include "Textbox.h"
#include "resources_manager.h"

Textbox::Textbox() :left(0), top(0), right(0), bottom(0) {
	cursor_pos = { float(left + 10),float( top + 5 )};
    cursor.add_frame(ResourcesManager::instance()->find_image("cursor"), 2);
    cursor.set_position(cursor_pos);
    cursor.set_anchor_mode(Animation::AnchorMode::BottomCentered);
    cursor.set_loop(true);
    cursor.set_interval(100);
}

Textbox::~Textbox() {
}

void Textbox::cursor_index_to_pos()
{
    cursor_pos.x = 0;
    for(int i=0;i<cursor_index;++i)
    {
        cursor_pos.x += textwidth(text[i]);
	}
	cursor_pos.x = left + cursor_pos.x+7;
}

void Textbox::change_cursor_index(int msgx)
{
    for (int i = text.size();i >= 0;i--)
    {
        int len = 0;
        for (int j = 0;j < i;j++)
        {
			len += textwidth(text[j]);
        }
        if(msgx >= left + 10 + len)
        {
            cursor_index = i-1;
            cursor_index_to_pos();
            return;
		}
    }
}


void Textbox::on_input(const ExMessage& msg)
{
    switch (msg.message)
    {
        // 鼠标左键按下
    case WM_LBUTTONDOWN: {
        if (!isInside(msg.x, msg.y))
        {
            isActive = false;
            if(on_change)
				on_change();
        }
        else {
            isActive = true;
			change_cursor_index(msg.x);
			cursor.set_position(cursor_pos);
        }
        break;
    }
    //字符输入
    case WM_CHAR: {
        if (isActive)
        {
            switch (msg.ch)
            {
            case '\b':				// 用户按退格键，删掉一个字符
                if (cursor_index > -1)
                {
					text.erase(text.begin()+cursor_index);
                    cursor_index--;
                    cursor_index_to_pos();
					cursor.set_position(cursor_pos);
                }
                break;
            case '\r':				// 用户按回车键，结束文本输入
            case '\n':
                isActive = false;
                break;
            default:				// 用户按其它键，接受文本输入
                if (text.size() < maxlen - 1 && iswprint(msg.ch) && !iswspace(msg.ch))
                {
                    text.insert(text.begin() + (++cursor_index), msg.ch);
                    cursor_index_to_pos();
					cursor.set_position(cursor_pos);
                }
            }
        }
        break;
    }
    default:
		break;
    }
}

void Textbox::on_update(int delta)
{
    if (!isActive)
		return;
    cursor.on_update(delta);
}

void Textbox::on_render(const Camera& camera)
{
    // 备份环境值
    int oldlinecolor = getlinecolor();
    int oldbkcolor = getbkcolor();
    int oldfillcolor = getfillcolor();

    setlinecolor(LIGHTGRAY);		// 设置画线颜色
    setbkcolor(0xeeeeee);			// 设置背景颜色
    setfillcolor(0xeeeeee);			// 设置填充颜色
    fillrectangle(left, top, right, bottom);
    settextstyle(35, 0, _T("微软雅黑"));
    settextcolor(BLACK); // 设置字体颜色为黑色
    std::wstring wide_text(text.begin(), text.end());
    outtextxy(left + 10, top + 5, wide_text.c_str());

	// 绘制光标
    if (isActive)
    {
		cursor.on_render(camera);
    }

    // 恢复环境值
    setlinecolor(oldlinecolor);
    setbkcolor(oldbkcolor);
    setfillcolor(oldfillcolor);
}

void TextboxSecurity::on_render(const Camera& camera)
{
    // 备份环境值
    int oldlinecolor = getlinecolor();
    int oldbkcolor = getbkcolor();
    int oldfillcolor = getfillcolor();
    setlinecolor(LIGHTGRAY);		// 设置画线颜色
    setbkcolor(0xeeeeee);			// 设置背景颜色
    setfillcolor(0xeeeeee);			// 设置填充颜色
    fillrectangle(left, top, right, bottom);
    settextstyle(35, 0, _T("微软雅黑"));
    settextcolor(BLACK); // 设置字体颜色为黑色
    std::wstring wide_text(text.size(), '*');
    outtextxy(left + 10, top + 5, wide_text.c_str());
    // 绘制光标
    if (isActive)
    {
        cursor.on_render(camera);
    }
    // 恢复环境值
    setlinecolor(oldlinecolor);
    setbkcolor(oldbkcolor);
    setfillcolor(oldfillcolor);
}