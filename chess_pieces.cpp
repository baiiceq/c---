#include "chess_pieces.h"

General::General(const Vector2& p, Camp c)
{
    pos = p;
    camp = c;
    type = PieceType::General;
    is_alive = true;
}
void General::on_render(const Camera& camera) { }
void General::on_input(const ExMessage& msg) { }
void General::on_update(int delta) { }
void General::can_move_to() { }

Advisor::Advisor(const Vector2& p, Camp c) 
{
    pos = p;
    camp = c;
    type = PieceType::Advisor;
    is_alive = true;
}
void Advisor::on_render(const Camera& camera) { }
void Advisor::on_input(const ExMessage& msg) { }
void Advisor::on_update(int delta) { }
void Advisor::can_move_to() { }

// Elephant
Elephant::Elephant(const Vector2& p, Camp c) 
{
    pos = p;
    camp = c;
    type = PieceType::Elephant;
    is_alive = true;
}
void Elephant::on_render(const Camera& camera) { }
void Elephant::on_input(const ExMessage& msg) { }
void Elephant::on_update(int delta) { }
void Elephant::can_move_to() { }

Horse::Horse(const Vector2& p, Camp c)
{
    pos = p;
    camp = c;
    type = PieceType::Horse;
    is_alive = true;
}
void Horse::on_render(const Camera& camera) { }
void Horse::on_input(const ExMessage& msg) { }
void Horse::on_update(int delta) { }
void Horse::can_move_to() { }

Chariot::Chariot(const Vector2& p, Camp c) 
{
    pos = p;
    camp = c;
    type = PieceType::Chariot;
    is_alive = true;
}
void Chariot::on_render(const Camera& camera) { }
void Chariot::on_input(const ExMessage& msg) { }
void Chariot::on_update(int delta) { }
void Chariot::can_move_to() { }

Cannon::Cannon(const Vector2& p, Camp c) 
{
    pos = p;
    camp = c;
    type = PieceType::Cannon;
    is_alive = true;
}
void Cannon::on_render(const Camera& camera) { }
void Cannon::on_input(const ExMessage& msg) { }
void Cannon::on_update(int delta) { }
void Cannon::can_move_to() { }

Soldier::Soldier(const Vector2& p, Camp c)
{
    pos = p;
    camp = c;
    type = PieceType::Soldier;
    is_alive = true;
}
void Soldier::on_render(const Camera& camera) { }
void Soldier::on_input(const ExMessage& msg) { }
void Soldier::on_update(int delta) { }
void Soldier::can_move_to() { }