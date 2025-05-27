#pragma once

#include "chess_piece.h"
#include "animation.h"
#include "ai.h"
#include <vector>
#include <memory>

// 棋子管理器

class ChessManager
{
public:
    ChessManager();
    ~ChessManager();
    void on_render(const Camera& camera);
    void on_update(int delta);
    void on_input(const ExMessage& msg, ChessPiece::Camp current_turn);

    void reset();

    void undo_move(); // 悔棋


    void set_callback_change(std::function<void()> callback)
    {
        callback_change = callback;
    }

    void set_callback_win(std::function<void()> callback)
    {
        callback_win = callback;
    }

    void save_game_record(const std::string& filename);

private:
    struct MoveRecord
    {
        Vector2 from_pos;                       // 起始位置
        Vector2 to_pos;                         // 目标位置

        ChessPiece::PieceType piece_type;       // 移动的棋子类型
        ChessPiece::Camp camp;                  // 移动的阵营

        ChessPiece* moved_piece = nullptr;      // 移动的棋子
        ChessPiece* captured_piece = nullptr;   // 被吃的棋子

        bool captured_alive_before = false;     // 被吃棋子之前是否是活的
    };


    void handle_click(const Vector2& mousePos, ChessPiece::Camp current_turn);
    void handle_hover(const Vector2& mousePos, ChessPiece::Camp current_turn);
    bool try_move_selected_piece_to(const Vector2& mouse_pos);

    bool move_piece(const Vector2& src_pos, const Vector2& dst_pos);

    Vector2 find_general(ChessPiece::Camp camp);

    // 判断走完一步后是否将军对方
    bool is_in_check(ChessPiece::Camp current_camp);

    // 判断走完这一步后自己是否会被将军
    bool is_legal_move();

    Vector2 mouse_to_chess_pos(const Vector2& mouse_pos)
    {
        int x = (mouse_pos.x - 260) / 60;
        int y = (mouse_pos.y - 20) / 60;
        return Vector2(x, y);
    }

    ChessPiece* get_piece_at(const Vector2& pos)
    {
        for (auto& piece : pieces) 
        {
            if (piece->get_pos() == pos && piece->get_alive()) 
            {
                return piece;
            }
        }
        return nullptr;
    }

    void waigua(ChessPiece::Camp c);

private:
    bool can_operate = true;
    std::vector<ChessPiece*> pieces;
    IMAGE hover_box, selected_box, move_box, eat_box;
    ChessPiece* hovered_piece = nullptr;
    ChessPiece* selected_piece = nullptr;

    std::vector<Vector2> can_moves;
    std::vector<Vector2> can_eats;

    int map[9][10] {0};

    std::function<void()> callback_change;
    std::function<void()> callback_win;

    std::vector<MoveRecord> move_history;

    Animation anim_check;
    bool is_check = false;
private:
    Ai ai;
};

