#include <cwchar>
#include "Textbox.h"
#include "resources_manager.h"

Textbox::Textbox() :left(0), top(0), right(0), bottom(0) {
    cursor.add_frame(ResourcesManager::instance()->find_image("cursor"), 2);
    cursor.set_position({ float(left + 10), float(top + 5 )});
    cursor.set_anchor_mode(Animation::AnchorMode::BottomCentered);
    cursor.set_loop(true);
    cursor.set_interval(100);
}

Textbox::~Textbox() {
    if (text != NULL)
    {
        delete[] text;
        text = NULL;
    }
}

void Textbox::on_input(const ExMessage& msg)
{
    switch (msg.message)
    {
        // 鼠标左键按下
    case WM_LBUTTONDOWN: {
        if (!isInside(msg.x, msg.y))
            isActive = false;
        else
            isActive = true;
        break;
    }
    //字符输入
    case WM_CHAR: {
        if (isActive)
        {
            switch (msg.ch)
            {
            case '\b':				// 用户按退格键，删掉一个字符
                if (text_len > 0)
                {
                    text[text_len - 1] = L'\0';
                }
                break;
            case '\r':				// 用户按回车键，结束文本输入
            case '\n':
                isActive = false;
                break;
            default:				// 用户按其它键，接受文本输入
                if (text_len < maxlen - 1 && iswprint(msg.ch) && !iswspace(msg.ch))
                {
                    text[text_len++] = msg.ch;
                    text[text_len] = L'\0';
                }
            }
			// 更新光标位置
            cursor.set_position({ float(left + 10 +textwidth(text)+1),float( top + 5)});
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
    outtextxy(left + 10, top + 5, text);
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