#include "chess_manager.h"
#include "chess_pieces.h"
#include "resources_manager.h"
#include "util.h"

#include <iostream>
ChessManager::ChessManager()
{

    hover_box = *ResourcesManager::instance()->find_image("select_box_1");
    selected_box = *ResourcesManager::instance()->find_image("select_box_2");
    move_box = *ResourcesManager::instance()->find_image("select_box_3");
    eat_box = *ResourcesManager::instance()->find_image("select_box_4");
    // 红方
    {
        pieces.push_back(new Chariot({ 0, 0 }, ChessPiece::Camp::Red));
        pieces.push_back(new Horse({ 1, 0 }, ChessPiece::Camp::Red));
        pieces.push_back(new Elephant({ 2, 0 }, ChessPiece::Camp::Red));
        pieces.push_back(new Advisor({ 3, 0 }, ChessPiece::Camp::Red));
        pieces.push_back(new General({ 4, 0 }, ChessPiece::Camp::Red));
        pieces.push_back(new Advisor({ 5, 0 }, ChessPiece::Camp::Red));
        pieces.push_back(new Elephant({ 6, 0 }, ChessPiece::Camp::Red));
        pieces.push_back(new Horse({ 7, 0 }, ChessPiece::Camp::Red));
        pieces.push_back(new Chariot({ 8, 0 }, ChessPiece::Camp::Red));

        pieces.push_back(new Cannon({ 1, 2 }, ChessPiece::Camp::Red));
        pieces.push_back(new Cannon({ 7, 2 }, ChessPiece::Camp::Red));
        for (int i = 0; i < 5; ++i)
        {
            pieces.push_back(new Soldier({ (float)i * 2, 3 }, ChessPiece::Camp::Red));
        }
    }

    // 黑方
    {
        pieces.push_back(new Chariot({ 0, 9 }, ChessPiece::Camp::Black));
        pieces.push_back(new Horse({ 1, 9 }, ChessPiece::Camp::Black));
        pieces.push_back(new Elephant({ 2, 9 }, ChessPiece::Camp::Black));
        pieces.push_back(new Advisor({ 3, 9 }, ChessPiece::Camp::Black));
        pieces.push_back(new General({ 4, 9 }, ChessPiece::Camp::Black));
        pieces.push_back(new Advisor({ 5, 9 }, ChessPiece::Camp::Black));
        pieces.push_back(new Elephant({ 6, 9 }, ChessPiece::Camp::Black));
        pieces.push_back(new Horse({ 7, 9 }, ChessPiece::Camp::Black));
        pieces.push_back(new Chariot({ 8, 9 }, ChessPiece::Camp::Black));

        pieces.push_back(new Cannon({ 1, 7 }, ChessPiece::Camp::Black));
        pieces.push_back(new Cannon({ 7, 7 }, ChessPiece::Camp::Black));
        for (int i = 0; i < 5; ++i)
        {
            pieces.push_back(new Soldier({ (float)i * 2, 6 }, ChessPiece::Camp::Black));
        }
    }

}

ChessManager::~ChessManager()
{
    for (auto piece : pieces) 
    {
        delete piece;
    }
    pieces.clear();
}

void ChessManager::on_render(const Camera& camera)
{
    for (auto piece : pieces)
    {
        piece->on_render(camera);
    }

    if (hovered_piece)
    {
        Vector2 pos = hovered_piece->get_image_pos();
        Vector2 size = hovered_piece->get_size();
        Rect rect_dst = { pos.x, pos.y, size.x, size.y };
        putimage_alpha(&camera, &hover_box, &rect_dst);
    }

    if (selected_piece) 
    {
        Vector2 pos = selected_piece->get_image_pos();
        Vector2 size = selected_piece->get_size();
        Rect rect_dst = { pos.x,pos.y,size.x,size.y };
        putimage_alpha(&camera, &selected_box, &rect_dst);
    }
}

void ChessManager::on_update(int delta)
{
}

void ChessManager::on_input(const ExMessage& msg)
{
    Vector2 mousePos(msg.x, msg.y);
    switch (msg.message)
    {
    case WM_MOUSEMOVE:
        handle_hover(mousePos);
        break;
    case WM_LBUTTONDOWN:
        handle_click(mousePos);
        break;

    case WM_LBUTTONUP:
        break;

    }
}

void ChessManager::reset()
{
    for (auto piece : pieces)
    {
        delete piece;
    }
    pieces.clear();

    // 红方
    {
        pieces.push_back(new Chariot({ 0, 0 }, ChessPiece::Camp::Red));
        pieces.push_back(new Horse({ 1, 0 }, ChessPiece::Camp::Red));
        pieces.push_back(new Elephant({ 2, 0 }, ChessPiece::Camp::Red));
        pieces.push_back(new Advisor({ 3, 0 }, ChessPiece::Camp::Red));
        pieces.push_back(new General({ 4, 0 }, ChessPiece::Camp::Red));
        pieces.push_back(new Advisor({ 5, 0 }, ChessPiece::Camp::Red));
        pieces.push_back(new Elephant({ 6, 0 }, ChessPiece::Camp::Red));
        pieces.push_back(new Horse({ 7, 0 }, ChessPiece::Camp::Red));
        pieces.push_back(new Chariot({ 8, 0 }, ChessPiece::Camp::Red));

        pieces.push_back(new Cannon({ 1, 2 }, ChessPiece::Camp::Red));
        pieces.push_back(new Cannon({ 7, 2 }, ChessPiece::Camp::Red));
        for (int i = 0; i < 5; ++i)
        {
            pieces.push_back(new Soldier({ (float)i * 2, 3 }, ChessPiece::Camp::Red));
        }
    }

    // 黑方
    {
        pieces.push_back(new Chariot({ 0, 9 }, ChessPiece::Camp::Black));
        pieces.push_back(new Horse({ 1, 9 }, ChessPiece::Camp::Black));
        pieces.push_back(new Elephant({ 2, 9 }, ChessPiece::Camp::Black));
        pieces.push_back(new Advisor({ 3, 9 }, ChessPiece::Camp::Black));
        pieces.push_back(new General({ 4, 9 }, ChessPiece::Camp::Black));
        pieces.push_back(new Advisor({ 5, 9 }, ChessPiece::Camp::Black));
        pieces.push_back(new Elephant({ 6, 9 }, ChessPiece::Camp::Black));
        pieces.push_back(new Horse({ 7, 9 }, ChessPiece::Camp::Black));
        pieces.push_back(new Chariot({ 8, 9 }, ChessPiece::Camp::Black));

        pieces.push_back(new Cannon({ 1, 7 }, ChessPiece::Camp::Black));
        pieces.push_back(new Cannon({ 7, 7 }, ChessPiece::Camp::Black));
        for (int i = 0; i < 5; ++i)
        {
            pieces.push_back(new Soldier({ (float)i * 2, 6 }, ChessPiece::Camp::Black));
        }
    }
}

void ChessManager::handle_click(const Vector2& mousePos)
{
    for (auto& piece : pieces)
    {
        if (!piece->get_alive()) continue;

        Vector2 img_pos = piece->get_image_pos();
        Vector2 size = piece->get_size();

        if (mousePos.x >= img_pos.x &&
            mousePos.y >= img_pos.y &&
            mousePos.x <= img_pos.x + size.x &&
            mousePos.y <= img_pos.y + size.y)
        {
            if (selected_piece == nullptr)
            {
                selected_piece = piece;
            }
            else if (piece == selected_piece)
            {
                selected_piece = nullptr;
            }
            else
            {
                selected_piece = piece;
            }

            return;
        }
        else
        {
            selected_piece = nullptr;
        }
    }
    
}

void ChessManager::handle_hover(const Vector2& mousePos)
{
    int has_hovered = false;
    for (auto& piece : pieces)
    {
        if (!piece->get_alive()) continue;

        Vector2 img_pos = piece->get_image_pos();
        Vector2 size = piece->get_size();

        if (mousePos.x >= img_pos.x &&
            mousePos.y >= img_pos.y &&
            mousePos.x <= img_pos.x + size.x &&
            mousePos.y <= img_pos.y + size.y)
        {
            hovered_piece = piece;
            has_hovered = true;
        }
    }

    if (!has_hovered)
    {
        hovered_piece = nullptr;
    }
}
