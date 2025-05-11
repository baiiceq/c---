#pragma once
#pragma once
#include "chess_piece.h"

class General : public ChessPiece 
{
public:
    General(const Vector2& p, Camp c);
    void on_render(const Camera& camera) override;
    void on_input(const ExMessage& msg) override;
    void on_update(int delta) override;
    void can_move_to() override;
};

class Advisor : public ChessPiece 
{
public:
    Advisor(const Vector2& p, Camp c);
    void on_render(const Camera& camera) override;
    void on_input(const ExMessage& msg) override;
    void on_update(int delta) override;
    void can_move_to() override;
};

class Elephant : public ChessPiece
{
public:
    Elephant(const Vector2& p, Camp c);
    void on_render(const Camera& camera) override;
    void on_input(const ExMessage& msg) override;
    void on_update(int delta) override;
    void can_move_to() override;
};

class Horse : public ChessPiece
{
public:
    Horse(const Vector2& p, Camp c);
    void on_render(const Camera& camera) override;
    void on_input(const ExMessage& msg) override;
    void on_update(int delta) override;
    void can_move_to() override;
};

class Chariot : public ChessPiece {
public:
    Chariot(const Vector2& p, Camp c);
    void on_render(const Camera& camera) override;
    void on_input(const ExMessage& msg) override;
    void on_update(int delta) override;
    void can_move_to() override;
};

class Cannon : public ChessPiece
{
public:
    Cannon(const Vector2& p, Camp c);
    void on_render(const Camera& camera) override;
    void on_input(const ExMessage& msg) override;
    void on_update(int delta) override;
    void can_move_to() override;
};

class Soldier : public ChessPiece 
{
public:
    Soldier(const Vector2& p, Camp c);
    void on_render(const Camera& camera) override;
    void on_input(const ExMessage& msg) override;
    void on_update(int delta) override;
    void can_move_to() override;
};

