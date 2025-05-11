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
    void on_input(const ExMessage& msg);

    void reset();

private:
    void handle_click(const Vector2& mousePos);
    void handle_hover(const Vector2& mousePos);

private:
    std::vector<ChessPiece*> pieces;
    IMAGE hover_box, selected_box, move_box, eat_box;
    ChessPiece* hovered_piece = nullptr;
    ChessPiece* selected_piece = nullptr;
};

