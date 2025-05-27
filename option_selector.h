#pragma once
#include <graphics.h>
#include <string>
#include <vector>
#include <functional>

#include "Button.h"

class OptionSelector 
{

public:
    OptionSelector();
    ~OptionSelector();

    void on_render(const Camera& camera);

    void on_input(const ExMessage& msg);

    void set_position(Vector2 pos)
    {
        position = pos;

        update_button_layout();
    }

    void set_size(Vector2 s)
    {
        size = s;

        update_button_layout();
    }


    // ���ûص�����
    void setCallback(std::function<void(int)> callback)
    {
        on_select_callback = callback;
    }

    // ���õ�ǰѡ����
    void SetSelected(int index)
    {
        if (index >= 0 && index < options.size()) {
            selected = index;
        }
    }

    // ��ȡ��ǰѡ��������
    int GetSelected() const
    {
        return selected;
    }

    // ��ȡ��ǰѡ���ı�
    std::wstring GetSelectedText() const
    {
        return options[selected];
    }

    void set_options(const std::vector<std::wstring>& opts)
    {
        options = opts;
    }

private:
    // ���°�ť��С��λ��
    void update_button_layout();

private:
    Vector2 position;
    Vector2 size;
    std::vector<std::wstring> options;
    int selected = 0;

    std::function<void(int)> on_select_callback = nullptr;

    Button left;
    Button right;
};
