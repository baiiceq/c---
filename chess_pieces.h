#pragma once
#pragma once
#include "chess_piece.h"

// 实现了不同棋子，主要实现了移动方式

class General : public ChessPiece 
{
public:
    General(const Vector2& p, Camp c);
    void on_render(const Camera& camera) override;
    void on_input(const ExMessage& msg) override;
    void on_update(int delta) override;
    std::vector<Vector2> get_can_move_to(const int(&board)[9][10]) override;
    std::vector<Vector2> get_can_eat(const int(&board)[9][10]) override;
};

class Advisor : public ChessPiece 
{
public:
    Advisor(const Vector2& p, Camp c);
    void on_render(const Camera& camera) override;
    void on_input(const ExMessage& msg) override;
    void on_update(int delta) override;
    std::vector<Vector2> get_can_move_to(const int(&board)[9][10]) override;
    std::vector<Vector2> get_can_eat(const int(&board)[9][10]) override;
};

class Elephant : public ChessPiece
{
public:
    Elephant(const Vector2& p, Camp c);
    void on_render(const Camera& camera) override;
    void on_input(const ExMessage& msg) override;
    void on_update(int delta) override;
    std::vector<Vector2> get_can_move_to(const int(&board)[9][10])override;
    std::vector<Vector2> get_can_eat(const int(&board)[9][10]) override;
};

class Horse : public ChessPiece
{
public:
    Horse(const Vector2& p, Camp c);
    void on_render(const Camera& camera) override;
    void on_input(const ExMessage& msg) override;
    void on_update(int delta) override;
    std::vector<Vector2> get_can_move_to(const int(&board)[9][10]) override;
    std::vector<Vector2> get_can_eat(const int(&board)[9][10]) override;
};

class Chariot : public ChessPiece {
public:
    Chariot(const Vector2& p, Camp c);
    void on_render(const Camera& camera) override;
    void on_input(const ExMessage& msg) override;
    void on_update(int delta) override;
    std::vector<Vector2> get_can_move_to(const int(&board)[9][10]) override;
    std::vector<Vector2> get_can_eat(const int(&board)[9][10]) override;
};

class Cannon : public ChessPiece
{
public:
    Cannon(const Vector2& p, Camp c);
    void on_render(const Camera& camera) override;
    void on_input(const ExMessage& msg) override;
    void on_update(int delta) override;
    std::vector<Vector2> get_can_move_to(const int(&board)[9][10]) override;
    std::vector<Vector2> get_can_eat(const int(&board)[9][10]) override;
};

class Soldier : public ChessPiece 
{
public:
    Soldier(const Vector2& p, Camp c);
    void on_render(const Camera& camera) override;
    void on_input(const ExMessage& msg) override;
    void on_update(int delta) override;
    std::vector<Vector2> get_can_move_to(const int(&board)[9][10]) override;
    std::vector<Vector2> get_can_eat(const int(&board)[9][10]) override;
};




class SChariot : public SChessPiece
{
public:
    SChariot(const Vector2& p, ChessPiece::Camp c) :SChessPiece(p,c){type = ChessPiece::PieceType::Chariot;}
	std::vector<Vector2> get_can_move_to(const int(&board)[9][10]) override;
    std::vector<Vector2> get_can_eat(const int(&board)[9][10]) override;
};
class SCannon : public SChessPiece
{
    public:
    SCannon(const Vector2& p, ChessPiece::Camp c) :SChessPiece(p,c){type = ChessPiece::PieceType::Cannon;}
    std::vector<Vector2> get_can_move_to(const int(&board)[9][10]) override;
    std::vector<Vector2> get_can_eat(const int(&board)[9][10]) override;
};
class SHorse : public SChessPiece
{
    public:
    SHorse(const Vector2& p, ChessPiece::Camp c) :SChessPiece(p,c){type = ChessPiece::PieceType::Horse;}
    std::vector<Vector2> get_can_move_to(const int(&board)[9][10]) override;
    std::vector<Vector2> get_can_eat(const int(&board)[9][10]) override;
};
class SGeneral : public SChessPiece
{
    public:
    SGeneral(const Vector2& p, ChessPiece::Camp c) :SChessPiece(p,c){type = ChessPiece::PieceType::General;}
    std::vector<Vector2> get_can_move_to(const int(&board)[9][10]) override;
    std::vector<Vector2> get_can_eat(const int(&board)[9][10]) override;
};
class SAdvisor : public SChessPiece
{
    public:
    SAdvisor(const Vector2& p, ChessPiece::Camp c) :SChessPiece(p,c){type = ChessPiece::PieceType::Advisor;}
    std::vector<Vector2> get_can_move_to(const int(&board)[9][10]) override;
    std::vector<Vector2> get_can_eat(const int(&board)[9][10]) override;
};
class SElephant : public SChessPiece
{
    public:
    SElephant(const Vector2& p, ChessPiece::Camp c) :SChessPiece(p,c){type = ChessPiece::PieceType::Elephant;}
    std::vector<Vector2> get_can_move_to(const int(&board)[9][10]) override;
    std::vector<Vector2> get_can_eat(const int(&board)[9][10]) override;
};
class SSoldier : public SChessPiece
{
    public:
    SSoldier(const Vector2& p, ChessPiece::Camp c) :SChessPiece(p,c){type = ChessPiece::PieceType::Soldier;}
    std::vector<Vector2> get_can_move_to(const int(&board)[9][10]) override;
    std::vector<Vector2> get_can_eat(const int(&board)[9][10]) override;
};
