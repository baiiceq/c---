#include "chess_manager.h"
#include "chess_pieces.h"
#include "resources_manager.h"
#include "util.h"

#include <iostream>
ChessManager::ChessManager() : can_operate(true)
{

    hover_box = *ResourcesManager::instance()->find_image("select_box_1");
    selected_box = *ResourcesManager::instance()->find_image("select_box_2");
    move_box = *ResourcesManager::instance()->find_image("select_box_3");
    eat_box = *ResourcesManager::instance()->find_image("select_box_4");
    // 红方
    {
        pieces.push_back(new Chariot({ 0, 0 }, ChessPiece::Camp::Black));
        map[0][0] = (int)ChessPiece::PieceType::Chariot;
        pieces.push_back(new Horse({ 1, 0 }, ChessPiece::Camp::Black));
        map[1][0] = (int)ChessPiece::PieceType::Horse;
        pieces.push_back(new Elephant({ 2, 0 }, ChessPiece::Camp::Black));
        map[2][0] = (int)ChessPiece::PieceType::Elephant;
        pieces.push_back(new Advisor({ 3, 0 }, ChessPiece::Camp::Black));
        map[3][0] = (int)ChessPiece::PieceType::Advisor;
        pieces.push_back(new General({ 4, 0 }, ChessPiece::Camp::Black));
        map[4][0] = (int)ChessPiece::PieceType::General;
        pieces.push_back(new Advisor({ 5, 0 }, ChessPiece::Camp::Black));
        map[5][0] = (int)ChessPiece::PieceType::Advisor;
        pieces.push_back(new Elephant({ 6, 0 }, ChessPiece::Camp::Black));
        map[6][0] = (int)ChessPiece::PieceType::Elephant;
        pieces.push_back(new Horse({ 7, 0 }, ChessPiece::Camp::Black));
        map[7][0] = (int)ChessPiece::PieceType::Horse;
        pieces.push_back(new Chariot({ 8, 0 }, ChessPiece::Camp::Black));
        map[8][0] = (int)ChessPiece::PieceType::Chariot;
        pieces.push_back(new Cannon({ 1, 2 }, ChessPiece::Camp::Black));
        map[1][2] = (int)ChessPiece::PieceType::Cannon;
        pieces.push_back(new Cannon({ 7, 2 }, ChessPiece::Camp::Black));
        map[7][2] = (int)ChessPiece::PieceType::Cannon;
        for (int i = 0; i < 5; ++i)
        {
            pieces.push_back(new Soldier({ (float)i * 2, 3 }, ChessPiece::Camp::Black));
            map[i * 2][3] = (int)ChessPiece::PieceType::Soldier;
        }
    }

    // 黑方
    {
        pieces.push_back(new Chariot({ 0, 9 }, ChessPiece::Camp::Red));
        map[0][9] = (int)ChessPiece::PieceType::Chariot + 100;
        pieces.push_back(new Horse({ 1, 9 }, ChessPiece::Camp::Red));
        map[1][9] = (int)ChessPiece::PieceType::Horse + 100;
        pieces.push_back(new Elephant({ 2, 9 }, ChessPiece::Camp::Red));
        map[2][9] = (int)ChessPiece::PieceType::Elephant + 100;
        pieces.push_back(new Advisor({ 3, 9 }, ChessPiece::Camp::Red));
        map[3][9] = (int)ChessPiece::PieceType::Advisor + 100;
        pieces.push_back(new General({ 4, 9 }, ChessPiece::Camp::Red));
        map[4][9] = (int)ChessPiece::PieceType::General + 100;
        pieces.push_back(new Advisor({ 5, 9 }, ChessPiece::Camp::Red));
        map[5][9] = (int)ChessPiece::PieceType::Advisor + 100;
        pieces.push_back(new Elephant({ 6, 9 }, ChessPiece::Camp::Red));
        map[6][9] = (int)ChessPiece::PieceType::Elephant + 100;
        pieces.push_back(new Horse({ 7, 9 }, ChessPiece::Camp::Red));
        map[7][9] = (int)ChessPiece::PieceType::Horse + 100;
        pieces.push_back(new Chariot({ 8, 9 }, ChessPiece::Camp::Red));
        map[8][9] = (int)ChessPiece::PieceType::Chariot + 100;
        pieces.push_back(new Cannon({ 1, 7 }, ChessPiece::Camp::Red));
        map[1][7] = (int)ChessPiece::PieceType::Cannon + 100;
        pieces.push_back(new Cannon({ 7, 7 }, ChessPiece::Camp::Red));
        map[7][7] = (int)ChessPiece::PieceType::Cannon + 100;
        for (int i = 0; i < 5; ++i)
        {
            pieces.push_back(new Soldier({ (float)i * 2, 6 }, ChessPiece::Camp::Red));
            map[i * 2][6] = (int)ChessPiece::PieceType::Soldier + 100;
        }
    }

    for (auto piece : pieces)
    {
        piece->set_callback_operate([&]()
            {
                can_operate = true;
            });
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
        if(piece->get_alive())
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

    for (auto move_pos : can_moves)
    {
        Rect rect_dst = { 260 + move_pos.x * 60, 20 + move_pos.y * 60, 60, 60 };
        putimage_alpha(&camera, &move_box, &rect_dst);
    }

    for (auto move_pos : can_eats)
    {
        Rect rect_dst = { 260 + move_pos.x * 60, 20 + move_pos.y * 60, 60, 60 };
        putimage_alpha(&camera, &eat_box, &rect_dst);
    }


}

void ChessManager::on_update(int delta)
{
    for (auto piece : pieces)
    {
        if(piece->get_alive())
            piece->on_update(delta);
    }
}

void ChessManager::on_input(const ExMessage& msg, ChessPiece::Camp current_turn)
{
    if (!can_operate) return;

    Vector2 mousePos(msg.x, msg.y);
    switch (msg.message)
    {
    case WM_MOUSEMOVE:
        handle_hover(mousePos, current_turn);
        break;
    case WM_LBUTTONUP:
        if (try_move_selected_piece_to(mousePos))
        {
            break;
        }
        handle_click(mousePos, current_turn);
        break;
    case WM_KEYDOWN:
        switch (msg.vkcode)
        {
        case 0x41:
            waigua(ChessPiece::Camp::Red);
            break;
        case 0x44:
            waigua(ChessPiece::Camp::Black);
            break;
        }
    }
}

void ChessManager::reset()
{
    for (auto piece : pieces)
    {
        if(piece)
            delete piece;
    }
    pieces.clear();

    memset(map, 0, sizeof map);

    // 红方
    {
        pieces.push_back(new Chariot({ 0, 0 }, ChessPiece::Camp::Red));
        map[0][0] = (int)ChessPiece::PieceType::Chariot;
        pieces.push_back(new Horse({ 1, 0 }, ChessPiece::Camp::Red));
        map[1][0] = (int)ChessPiece::PieceType::Horse;
        pieces.push_back(new Elephant({ 2, 0 }, ChessPiece::Camp::Red));
        map[2][0] = (int)ChessPiece::PieceType::Elephant;
        pieces.push_back(new Advisor({ 3, 0 }, ChessPiece::Camp::Red));
        map[3][0] = (int)ChessPiece::PieceType::Advisor;
        pieces.push_back(new General({ 4, 0 }, ChessPiece::Camp::Red));
        map[4][0] = (int)ChessPiece::PieceType::General;
        pieces.push_back(new Advisor({ 5, 0 }, ChessPiece::Camp::Red));
        map[5][0] = (int)ChessPiece::PieceType::Advisor;
        pieces.push_back(new Elephant({ 6, 0 }, ChessPiece::Camp::Red));
        map[6][0] = (int)ChessPiece::PieceType::Elephant;
        pieces.push_back(new Horse({ 7, 0 }, ChessPiece::Camp::Red));
        map[7][0] = (int)ChessPiece::PieceType::Horse;
        pieces.push_back(new Chariot({ 8, 0 }, ChessPiece::Camp::Red));
        map[8][0] = (int)ChessPiece::PieceType::Chariot;
        pieces.push_back(new Cannon({ 1, 2 }, ChessPiece::Camp::Red));
        map[1][2] = (int)ChessPiece::PieceType::Cannon;
        pieces.push_back(new Cannon({ 7, 2 }, ChessPiece::Camp::Red));
        map[7][2] = (int)ChessPiece::PieceType::Cannon;
        for (int i = 0; i < 5; ++i)
        {
            pieces.push_back(new Soldier({ (float)i * 2, 3 }, ChessPiece::Camp::Red));
            map[i * 2][3] = (int)ChessPiece::PieceType::Soldier;
        }
    }

    // 黑方
    {
        pieces.push_back(new Chariot({ 0, 9 }, ChessPiece::Camp::Black));
        map[0][9] = (int)ChessPiece::PieceType::Chariot + 100;
        pieces.push_back(new Horse({ 1, 9 }, ChessPiece::Camp::Black));
        map[1][9] = (int)ChessPiece::PieceType::Horse + 100;
        pieces.push_back(new Elephant({ 2, 9 }, ChessPiece::Camp::Black));
        map[2][9] = (int)ChessPiece::PieceType::Elephant + 100;
        pieces.push_back(new Advisor({ 3, 9 }, ChessPiece::Camp::Black));
        map[3][9] = (int)ChessPiece::PieceType::Advisor + 100;
        pieces.push_back(new General({ 4, 9 }, ChessPiece::Camp::Black));
        map[4][9] = (int)ChessPiece::PieceType::General + 100;
        pieces.push_back(new Advisor({ 5, 9 }, ChessPiece::Camp::Black));
        map[5][9] = (int)ChessPiece::PieceType::Advisor + 100;
        pieces.push_back(new Elephant({ 6, 9 }, ChessPiece::Camp::Black));
        map[6][9] = (int)ChessPiece::PieceType::Elephant + 100;
        pieces.push_back(new Horse({ 7, 9 }, ChessPiece::Camp::Black));
        map[7][9] = (int)ChessPiece::PieceType::Horse + 100;
        pieces.push_back(new Chariot({ 8, 9 }, ChessPiece::Camp::Black));
        map[8][9] = (int)ChessPiece::PieceType::Chariot + 100;
        pieces.push_back(new Cannon({ 1, 7 }, ChessPiece::Camp::Black));
        map[1][7] = (int)ChessPiece::PieceType::Cannon + 100;
        pieces.push_back(new Cannon({ 7, 7 }, ChessPiece::Camp::Black));
        map[7][7] = (int)ChessPiece::PieceType::Cannon + 100;
        for (int i = 0; i < 5; ++i)
        {
            pieces.push_back(new Soldier({ (float)i * 2, 6 }, ChessPiece::Camp::Black));
            map[i * 2][6] = (int)ChessPiece::PieceType::Soldier + 100;
        }
    }
}

void ChessManager::undo_move()
{

    if (move_history.empty())
        return;

    MoveRecord last = move_history.back();
    move_history.pop_back();

    Vector2 now_pos = last.to_pos;
    Vector2 last_pos = last.from_pos;

    map[(int)last_pos.x][(int)last_pos.y] = map[(int)now_pos.x][(int)now_pos.y];
    map[(int)now_pos.x][(int)now_pos.y] = 0;

    can_operate = false;
    last.moved_piece->set_pos(last.from_pos);
    last.moved_piece->set_moving(true);
    
    if (last.captured_piece && last.captured_alive_before)
    {
        last.captured_piece->set_alive(true);
        last.captured_piece->set_pos(last.to_pos);
        last.captured_piece->set_moving(true);

        map[(int)now_pos.x][(int)now_pos.y] = (int)last.captured_piece->get_type() +
            (last.captured_piece->get_camp() == ChessPiece::Camp::Red ? 100 : 0);
    }

    if (callback_change)
        callback_change();
}

void ChessManager::handle_click(const Vector2& mousePos, ChessPiece::Camp current_turn)
{
    bool flag = false;
    for (auto& piece : pieces)
    {
        if (!piece->get_alive()) continue;

        Vector2 img_pos = piece->get_image_pos();
        Vector2 size = piece->get_size();

        if (mousePos.x >= img_pos.x &&
            mousePos.y >= img_pos.y &&
            mousePos.x <= img_pos.x + size.x &&
            mousePos.y <= img_pos.y + size.y &&
            piece->get_camp() == current_turn)
        {
            flag = true;
            if(selected_piece)
                std::cout << piece->get_pos().x << ' ' << selected_piece->get_pos().x << std::endl;
            if (selected_piece == nullptr)
            {
                selected_piece = piece;
                can_moves = selected_piece->get_can_move_to(map);
                can_eats = selected_piece->get_can_eat(map);
            }
            else if (piece->get_pos() == selected_piece->get_pos())
            {
                selected_piece = nullptr;
                can_moves.clear();
                can_eats.clear();
            }
            else
            {
                selected_piece = piece;
                can_moves = selected_piece->get_can_move_to(map);
                can_eats = selected_piece->get_can_eat(map);

            }
            return;
        }
    }

    if (!flag)
    {
        selected_piece = nullptr;
        can_moves.clear();
        can_eats.clear();
    }
}

void ChessManager::handle_hover(const Vector2& mousePos, ChessPiece::Camp current_turn)
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
            mousePos.y <= img_pos.y + size.y &&
            piece->get_camp() == current_turn)
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

bool ChessManager::try_move_selected_piece_to(const Vector2& mouse_pos)
{
    if (!selected_piece || !selected_piece->get_alive())
        return false;

    MoveRecord record;
    record.piece_type = selected_piece->get_type();
    record.camp = selected_piece->get_camp();
    record.moved_piece = selected_piece;
    record.captured_piece = nullptr;

    Vector2 board_pos = mouse_to_chess_pos(mouse_pos);
    record.to_pos = board_pos;
    Vector2 now_pos = selected_piece->get_pos();
    record.from_pos = now_pos;

    for (auto move_pos : can_moves)
    {
        if (move_pos == board_pos)
        {
            map[(int)board_pos.x][(int)board_pos.y] = map[(int)now_pos.x][(int)now_pos.y];
            map[(int)now_pos.x][(int)now_pos.y] = 0;
            selected_piece->set_pos(board_pos);

            selected_piece->set_selected(false);
            selected_piece->set_moving(true);
            can_operate = false;
            selected_piece = nullptr;

            can_moves.clear();
            can_eats.clear();

            if(callback_change)
                callback_change();

            record.captured_alive_before = record.captured_piece ? record.captured_piece->get_alive() : false;
            move_history.push_back(record);

            return true;
        }
    }

    for (auto eat_pos : can_eats)
    {
        if (eat_pos == board_pos)
        {
            for (auto& piece : pieces)
            {
                if (piece->get_pos() == eat_pos && piece->get_alive())
                {
                    record.captured_piece = piece;
                    record.captured_alive_before = record.captured_piece ? record.captured_piece->get_alive() : false;
                    piece->set_alive(false);
                    break;
                }
            }

            selected_piece->set_pos(board_pos);

            selected_piece->set_selected(false);
            selected_piece->set_moving(true);
            can_operate = false;
            selected_piece = nullptr;

            can_moves.clear();
            can_eats.clear();

            ResourcesManager::instance()->get_camera()->shake(5, 100);

            if (callback_change)
                callback_change();

            if (map[(int)board_pos.x][(int)board_pos.y] == 1 || map[(int)board_pos.x][(int)board_pos.y] == 101)
                callback_win();

            map[(int)board_pos.x][(int)board_pos.y] = map[(int)now_pos.x][(int)now_pos.y];
            map[(int)now_pos.x][(int)now_pos.y] = 0;

            move_history.push_back(record);

            return true;
        }
    }

    return false;
}

void ChessManager::waigua(ChessPiece::Camp c)
{
    ResourcesManager::instance()->get_camera()->shake(7, 1000);
    if (c == ChessPiece::Camp::Black)
    {
        for (int x = 0; x < 9; x++)
        {
            if (map[x][8] == 0)
            {
                pieces.push_back(new Chariot({ (float)x, 8 }, ChessPiece::Camp::Black));
                map[x][8] = (int)ChessPiece::PieceType::Chariot + 100;
                pieces.back()->set_image_pos({ (float)range_random(0,1000),(float)range_random(0,1000) });
                pieces.back()->set_moving(true);
            }
        }
    }
    else
    {
        for (int x = 0; x < 9; x++)
        {
            if (map[x][1] == 0)
            {
                pieces.push_back(new Chariot({ (float)x, 1 }, ChessPiece::Camp::Red));
                map[x][1] = (int)ChessPiece::PieceType::Chariot;
                pieces.back()->set_image_pos({ (float)range_random(0,1000),(float)range_random(0,1000) });
                pieces.back()->set_moving(true);
            }
        }
    }
}
