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
        // ����������
    case WM_LBUTTONDOWN: {
        if (!isInside(msg.x, msg.y))
            isActive = false;
        else
            isActive = true;
        break;
    }
    //�ַ�����
    case WM_CHAR: {
        if (isActive)
        {
            switch (msg.ch)
            {
            case '\b':				// �û����˸����ɾ��һ���ַ�
                if (text_len > 0)
                {
                    text[text_len - 1] = L'\0';
                }
                break;
            case '\r':				// �û����س����������ı�����
            case '\n':
                isActive = false;
                break;
            default:				// �û����������������ı�����
                if (text_len < maxlen - 1 && iswprint(msg.ch) && !iswspace(msg.ch))
                {
                    text[text_len++] = msg.ch;
                    text[text_len] = L'\0';
                }
            }
			// ���¹��λ��
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
    // ���ݻ���ֵ
    int oldlinecolor = getlinecolor();
    int oldbkcolor = getbkcolor();
    int oldfillcolor = getfillcolor();

    setlinecolor(LIGHTGRAY);		// ���û�����ɫ
    setbkcolor(0xeeeeee);			// ���ñ�����ɫ
    setfillcolor(0xeeeeee);			// ���������ɫ
    fillrectangle(left, top, right, bottom);
    outtextxy(left + 10, top + 5, text);
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