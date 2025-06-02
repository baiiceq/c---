#include <cwchar>
#include "Textbox.h"
#include "resources_manager.h"

Textbox::Textbox() :left(0), top(0), right(0), bottom(0), cursor_index(0) {
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
    for (int i = (int)text.size();i >= 0;i--)
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
        // ����������
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
    //�ַ�����
    case WM_CHAR: {
        if (isActive)
        {
            switch (msg.ch)
            {
            case '\b':				// �û����˸����ɾ��һ���ַ�
                if (cursor_index > -1)
                {
					text.erase(text.begin()+cursor_index);
                    cursor_index--;
                    cursor_index_to_pos();
					cursor.set_position(cursor_pos);
                }
                break;
            case '\r':				// �û����س����������ı�����
            case '\n':
                isActive = false;
                break;
            default:				// �û����������������ı�����
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
    cursor.on_update((float)delta);
}

void Textbox::on_render(const Camera& camera)
{
    // ���ݻ���ֵ
    int oldlinecolor = getlinecolor();
    int oldbkcolor = getbkcolor();
    int oldfillcolor = getfillcolor();

    setlinecolor(LIGHTGRAY);		// ���û�����ɫ
    setbkcolor(0xeeeeee);			// ���ñ�����ɫ
    setfillcolor(0xeeeeee);			// ���������ɫ
    fillrectangle(left, top, right, bottom);
    settextstyle(35, 0, _T("΢���ź�"));
    settextcolor(BLACK); // ����������ɫΪ��ɫ
    std::wstring wide_text(text.begin(), text.end());
    outtextxy(left + 10, top + 5, wide_text.c_str());

	// ���ƹ��
    if (isActive)
    {
		cursor.on_render(camera);
    }

    // �ָ�����ֵ
    setlinecolor(oldlinecolor);
    setbkcolor(oldbkcolor);
    setfillcolor(oldfillcolor);
}

void TextboxSecurity::on_render(const Camera& camera)
{
    // ���ݻ���ֵ
    int oldlinecolor = getlinecolor();
    int oldbkcolor = getbkcolor();
    int oldfillcolor = getfillcolor();
    setlinecolor(LIGHTGRAY);		// ���û�����ɫ
    setbkcolor(0xeeeeee);			// ���ñ�����ɫ
    setfillcolor(0xeeeeee);			// ���������ɫ
    fillrectangle(left, top, right, bottom);
    settextstyle(35, 0, _T("΢���ź�"));
    settextcolor(BLACK); // ����������ɫΪ��ɫ
    std::wstring wide_text(text.size(), '*');
    outtextxy(left + 10, top + 5, wide_text.c_str());
    // ���ƹ��
    if (isActive)
    {
        cursor.on_render(camera);
    }
    // �ָ�����ֵ
    setlinecolor(oldlinecolor);
    setbkcolor(oldbkcolor);
    setfillcolor(oldfillcolor);
}

void TextboxSwitch::on_render(const Camera& camera)
{
    // ���ݻ���ֵ
    int oldlinecolor = getlinecolor();
    int oldbkcolor = getbkcolor();
    int oldfillcolor = getfillcolor();
    if (isActive) 
    {
        setlinecolor(LIGHTGRAY);		// ���û�����ɫ
        setbkcolor(0xeeeeee);			// ���ñ�����ɫ
        setfillcolor(0xeeeeee);			// ���������ɫ
        fillrectangle(left, top, right, bottom);
    }
    else
		setbkcolor(TRANSPARENT); // ���ñ�����ɫΪ͸��
    settextstyle(35, 0, _T("΢���ź�"));
    settextcolor(BLACK); // ����������ɫΪ��ɫ
    std::wstring wide_text(text.begin(), text.end());
    outtextxy(left + 10, top + 5, wide_text.c_str());
    // ���ƹ��
    if (isActive)
    {
        cursor.on_render(camera);
    }
    // �ָ�����ֵ
    setlinecolor(oldlinecolor);
    setbkcolor(oldbkcolor);
    setfillcolor(oldfillcolor);
}

TextboxButton::TextboxButton() :TextboxSwitch()
{
    left.set_image("leftarrow");
    left.set_on_click([&]()
        {
            int val = 0;
            try {
                val = std::stoi(text);
            }
            catch (...) {
                val = 0;
            }
            if (val > 0) val--;
            text = std::to_wstring(val);
            cursor_index = (int)text.size() - 1;
        });

    right.set_image("rightarrow");
    right.set_on_click([&]()
        {
            int val = 0;
            try {
                val = std::stoi(text);
            }
            catch (...) {
                val = 0;
            }
            if (val < 100) val++;
            text = std::to_wstring(val);
            cursor_index = (int)text.size() - 1;
        });
}

void TextboxButton::on_input(const ExMessage& msg)
{
    switch (msg.message)
    {
        // ����������
    case WM_LBUTTONDOWN: {
        if (!isInside(msg.x, msg.y))
        {
            isActive = false;
            if (on_change)
                on_change();
        }
        else {
            isActive = true;
            change_cursor_index(msg.x);
            cursor.set_position(cursor_pos);
        }
        break;
    }
                       //�ַ�����
    case WM_CHAR: {
        if (isActive)
        {
            switch (msg.ch)
            {
            case '\b':				// �û����˸����ɾ��һ���ַ�
                if (cursor_index > -1)
                {
                    text.erase(text.begin() + cursor_index);
                    cursor_index--;
                    cursor_index_to_pos();
                    cursor.set_position(cursor_pos);
                }
                break;
            case '\r':				// �û����س����������ı�����
            case '\n':
                isActive = false;
                break;
            default:				// �û����������������ı�����
                if (text.size() < maxlen - 1 && iswdigit(msg.ch))
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
	left.on_input(msg);
	right.on_input(msg);
}
void TextboxButton::on_update(int delta)
{
    Textbox::on_update(delta);
    left.on_update(delta);
    right.on_update(delta);
}

void TextboxButton::on_render(const Camera& camera)
{
    TextboxSwitch::on_render(camera);
    left.on_render(camera);
    right.on_render(camera);
}

void TextboxButton::Set_Textbox(int x1, int y1, int x2, int y2, int max)
{
	Textbox::Set_Textbox(x1, y1, x2, y2, max);
    left.set_pos(x1 - 40, y1);
	left.set_size(35, y2 - y1);
	right.set_pos(x2 + 5, y1);
    right.set_size(35, y2 - y1);
}