#pragma once

#include "chess_piece.h"
#include <vector>
#include <memory>

class ChessManager
{
    ChessManager();
    ~ChessManager();
    void on_render(const Camera& camera);
    void on_update(int delta);
    void on_input(const ExMessage& msg);

private:
    std::vector<ChessPiece*> pieces;
};

