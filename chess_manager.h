#pragma once

#include "chess_piece.h"
#include <vector>
#include <memory>

class ChessManager
{
public:
    ChessManager();
    ~ChessManager();
    void on_render(const Camera& camera);
    void on_update(int delta);
    void on_input(const ExMessage& msg, ChessPiece::Camp current_turn);

    void reset();

    void set_callback(std::function<void()> callback)
    {
        callback_change = callback;
    }

private:
    void handle_click(const Vector2& mousePos, ChessPiece::Camp current_turn);
    void handle_hover(const Vector2& mousePos, ChessPiece::Camp current_turn);

    bool try_move_selected_piece_to(const Vector2& mouse_pos);

    Vector2 mouse_to_chess_pos(const Vector2& mouse_pos)
    {
        int x = (mouse_pos.x - 130) / 60;
        int y = (mouse_pos.y - 20) / 60;
        return Vector2(x, y);
    }

private:
    std::vector<ChessPiece*> pieces;
    IMAGE hover_box, selected_box, move_box, eat_box;
    ChessPiece* hovered_piece = nullptr;
    ChessPiece* selected_piece = nullptr;

    std::vector<Vector2> can_moves;
    std::vector<Vector2> can_eats;

    int map[9][10] {0};

    std::function<void()> callback_change;
};

