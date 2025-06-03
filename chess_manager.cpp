#include "chess_manager.h"
#include "chess_pieces.h"
#include "resources_manager.h"
#include "scene_manager.h"
#include "util.h"
#include <fstream>
#include <algorithm>
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

    anim_check.add_frame(ResourcesManager::instance()->find_image("check"), 11);
    anim_check.set_position({ 200,300 });
    anim_check.set_anchor_mode(Animation::AnchorMode::BottomCentered);
    anim_check.set_loop(false);
    anim_check.set_interval(80);
    anim_check.set_on_finished([&]()
        {
            is_check = false;
        });

    anim_ai_thinking.add_frame(ResourcesManager::instance()->find_image("ai_thinking"), 6);
    anim_ai_thinking.set_position({ 100,400 });
    anim_ai_thinking.set_anchor_mode(Animation::AnchorMode::BottomCentered);
    anim_ai_thinking.set_loop(true);
    anim_ai_thinking.set_interval(300);
    anim_ai_thinking.set_on_finished([&]()
        {
            is_AI_thinking = false;
        });

    ai.set_think_finished([&]()
        {
            Method result = ai.get_method();
            move_piece(result.rsc_pos, result.dst_pos, false);
            is_AI_thinking = false;
        });

    turn_timer.set_wait_time(turn_time_limit);
    turn_timer.set_one_shot(true);
    turn_timer.set_on_timeout([&]() {
        if (callback_win)
            callback_win(1);
        });
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
        Rect rect_dst = { (int)pos.x,(int)pos.y, (int)size.x, (int)size.y };
        putimage_alpha(&camera, &hover_box, &rect_dst);
    }

    if (selected_piece) 
    {
        Vector2 pos = selected_piece->get_image_pos();
        Vector2 size = selected_piece->get_size();
        Rect rect_dst = { (int)pos.x,(int)pos.y,(int)size.x,(int)size.y };
        putimage_alpha(&camera, &selected_box, &rect_dst);
    }

    for (auto move_pos : can_moves)
    {
        Rect rect_dst = { 260 + (int)move_pos.x * 60, 20 + (int)move_pos.y * 60, 60, 60 };
        putimage_alpha(&camera, &move_box, &rect_dst);
    }

    for (auto move_pos : can_eats)
    {
        Rect rect_dst = { 260 + (int)move_pos.x * 60, 20 + (int)move_pos.y * 60, 60, 60 };
        putimage_alpha(&camera, &eat_box, &rect_dst);
    }

    if (is_check)
        anim_check.on_render(camera, 3);

    if (is_AI_thinking)
        anim_ai_thinking.on_render(camera);

    // 显示剩余时间
    int remain_ms = turn_time_limit - turn_timer.get_pass_time();
    int remain_sec = (0> remain_ms / 1000)?0:remain_ms / 1000;
    settextstyle(32, 0, _T("微软雅黑"));
    settextcolor(RED);
    wchar_t buf[32];
    swprintf(buf, 32, L"倒计时: %d", remain_sec);
    outtextxy(50, 600, buf);
}

void ChessManager::on_update(int delta, ChessPiece::Camp current_turn)
{
    turn_timer.on_update(delta);

    if ((is_black_AI && current_turn == ChessPiece::Camp::Black) || (is_red_AI && current_turn == ChessPiece::Camp::Red))
    {
        if (!is_AI_thinking && can_operate)
        {
            ai_start_think(current_turn);
        }
    }

    for (auto piece : pieces)
    {
        if(piece->get_alive())
            piece->on_update(delta);
    }

    if (is_check)
        anim_check.on_update((float)delta);

    if (is_AI_thinking)
        anim_ai_thinking.on_update((float)delta);
}

void ChessManager::on_input(const ExMessage& msg, ChessPiece::Camp current_turn)
{
    if (!can_operate) return;
    if (is_AI_thinking)return;

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

    can_moves.clear();
    can_eats.clear();
    move_history.clear();
    turn_timer.restart();
    playback_step = 0;
    memset(map, 0, sizeof map);

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

    can_operate = true;
}

void ChessManager::undo_move()
{
    if (is_AI_thinking)
        return;

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
    last.moved_piece->set_moving(1);
    
    if (last.captured_piece && last.captured_alive_before)
    {
        last.captured_piece->set_alive(true);
        last.captured_piece->set_pos(last.to_pos);
        last.captured_piece->set_moving(1);

        map[(int)now_pos.x][(int)now_pos.y] = (int)last.captured_piece->get_type() +
            (last.captured_piece->get_camp() == ChessPiece::Camp::Red ? 100 : 0);
    }

    if (callback_change)
        callback_change(1);
    turn_timer.restart();
}

void ChessManager::save_game_record(const std::string& filename)
{
    std::ofstream file(filename);
    if (!file.is_open()) 
    {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return;
    }

    for (const auto& record : move_history) {
        file << record.from_pos.x << " " << record.from_pos.y << " "
            << record.to_pos.x << " " << record.to_pos.y << " "
            << (int)record.piece_type << " "
            << (int)record.camp << " "
            << record.captured_alive_before << "\n";
    }

    file.close();
}

void ChessManager::load_game_record(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return;
    }

    move_history.clear(); 

    int from_x, from_y, to_x, to_y;
    int piece_type_int, camp_int;
    int captured_int;

    while (file >> from_x >> from_y >> to_x >> to_y >> piece_type_int >> camp_int >> captured_int)
    {
        MoveRecord record;
        record.from_pos.x = (float)from_x;
        record.from_pos.y = (float)from_y;
        record.to_pos.x = (float)to_x;
        record.to_pos.y = (float)to_y;
        record.piece_type = (ChessPiece::PieceType)piece_type_int;
        record.camp = (ChessPiece::Camp)camp_int;
        record.captured_alive_before = (captured_int != 0);

        move_history.push_back(record);
    }

    file.close();
}

void ChessManager::load()
{
    for (auto& record : move_history)
    {
        move_piece(record.from_pos, record.to_pos, false, &record);
    }

    can_operate = true;
}

void ChessManager::load_one_step()
{
    if (playback_step >= move_history.size())
    {
        SceneManager::instance()->set_gamescene_state_to_running();
    }
    else
    {
        auto record = move_history[playback_step++];
        move_piece(record.from_pos, record.to_pos, false, &record);
    }
}

void ChessManager::ai_start_think(ChessPiece::Camp current_turn)
{
    is_AI_thinking = true;
    ai.update(map, current_turn);
    ai.cout_method(current_turn == ChessPiece::Camp::Black ? black_AI_difficulty : red_AI_difficulty);
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

    Vector2 board_pos = mouse_to_chess_pos(mouse_pos);

    for (auto& pos : can_moves)
    {
        if (pos == board_pos) 
        {
            return move_piece(selected_piece->get_pos(), board_pos, false);
        }
    }

    for (auto& pos : can_eats) 
    {
        if (pos == board_pos) 
        {
            return move_piece(selected_piece->get_pos(), board_pos, false);
        }
    }

    return false;
}

bool ChessManager::move_piece(const Vector2& src_pos, const Vector2& dst_pos, bool is_load, MoveRecord* r)
{
    ChessPiece* piece = get_piece_at(src_pos);
    if (!piece || !piece->get_alive())
        return false;

    MoveRecord record;
    if (!is_load)
    {
        record.moved_piece = piece;
        record.from_pos = src_pos;
        record.to_pos = dst_pos;
        record.piece_type = piece->get_type();
        record.camp = piece->get_camp();
        record.captured_piece = get_piece_at(dst_pos);
        record.captured_alive_before = record.captured_piece ? record.captured_piece->get_alive() : false;
    }
    
    if (r)
    {
        r->captured_piece = get_piece_at(dst_pos);
        r->moved_piece = piece;
    }

    // 吃子
    if (record.captured_piece || (r && r->captured_piece))
    {
        if (r)
        {
            r->captured_piece->set_alive(false);
        }
        else
        {
            record.captured_piece->set_alive(false);
        }
        
        if (!is_load)
        {
            ResourcesManager::instance()->get_camera()->shake(5, 100);
            play_audio(_T("eat"), ResourcesManager::instance()->get_volume());
        }
        
        if (record.captured_piece && record.captured_piece->get_type() == ChessPiece::PieceType::General)
        {
            
            can_operate = true;
            if (callback_win)
                callback_win((int)src_pos.x * 1000 + (int)src_pos.y * 100 + (int)dst_pos.x * 10 + (int)dst_pos.y);
        }
    }
    else
    {
        if(!is_load)
            play_audio(_T("move"), ResourcesManager::instance()->get_volume());
    }

    // 修改棋盘地图
    map[(int)dst_pos.x][(int)dst_pos.y] = map[(int)src_pos.x][(int)src_pos.y];
    map[(int)src_pos.x][(int)src_pos.y] = 0;

    // 移动棋子
    piece->set_pos(dst_pos);
    piece->set_selected(false);
    piece->set_moving(is_load ? 2 : 1);
    selected_piece = nullptr;
    can_operate = false;

    can_moves.clear();
    can_eats.clear();

    if(r == nullptr)
        move_history.push_back(record);

    std::cout << "从(" << src_pos.x << ',' << src_pos.y << "到(" << dst_pos.x << '/' << dst_pos.y << std::endl;

    if (!is_load)
    {
        ChessPiece::Camp current_turn = piece->get_camp();
        if (is_in_check(current_turn))
        {
            anim_check.reset();
            is_check = true;
        }
    }

    if (callback_change)
        callback_change((int)src_pos.x * 1000 + (int)src_pos.y * 100 + (int)dst_pos.x * 10 + (int)dst_pos.y);

    turn_timer.restart();
    return true;
}

Vector2 ChessManager::find_general(ChessPiece::Camp camp)
{
    for (const auto& piece : pieces) 
    {
        if (piece->get_camp() == camp && piece->get_type() == ChessPiece::PieceType::General)
        {
            return piece->get_pos();
        }
    }
    return { -1, -1 }; // 未找到
}

bool ChessManager::is_in_check(ChessPiece::Camp current_camp)
{
    Vector2 general_pos = find_general((ChessPiece::Camp)(1 - (int)current_camp));
    for (const auto& piece : pieces)
    {
        if (piece->get_camp() == current_camp && piece->get_alive()) 
        {
            auto eats = piece->get_can_eat(map);
            for (auto& pos : eats)
            {
                if (pos == general_pos) 
                {
                    return true; 
                }
            }
        }
    }
    return false;
}

bool ChessManager::is_legal_move()
{

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
                pieces.back()->set_moving(1);
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
                pieces.back()->set_moving(1);
            }
        }
    }
}
