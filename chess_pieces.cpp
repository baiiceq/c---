#include "chess_pieces.h"
#include "resources_manager.h"

General::General(const Vector2& p, Camp c) : ChessPiece(p, c)
{
    type = PieceType::General; 

    if (c == Camp::Black)
        img = *ResourcesManager::instance()->find_image("general_black");
    else
        img = *ResourcesManager::instance()->find_image("general_red");
}
void General::on_render(const Camera& camera) { ChessPiece::on_render(camera); }
void General::on_input(const ExMessage& msg) { }
void General::on_update(int delta) { }
void General::can_move_to() { }

Advisor::Advisor(const Vector2& p, Camp c) : ChessPiece(p, c)
{
    type = PieceType::Advisor;
    is_alive = true;

    if (c == Camp::Black)
        img = *ResourcesManager::instance()->find_image("advisor_black");
    else
        img = *ResourcesManager::instance()->find_image("advisor_red");
}
void Advisor::on_render(const Camera& camera) { ChessPiece::on_render(camera); }
void Advisor::on_input(const ExMessage& msg) { }
void Advisor::on_update(int delta) { }
void Advisor::can_move_to() { }

Elephant::Elephant(const Vector2& p, Camp c) : ChessPiece(p, c)
{
    type = PieceType::Elephant;
    is_alive = true;

    if (c == Camp::Black)
        img = *ResourcesManager::instance()->find_image("elephant_black");
    else
        img = *ResourcesManager::instance()->find_image("elephant_red");
}
void Elephant::on_render(const Camera& camera) { ChessPiece::on_render(camera); }
void Elephant::on_input(const ExMessage& msg) { }
void Elephant::on_update(int delta) { }
void Elephant::can_move_to() { }

Horse::Horse(const Vector2& p, Camp c) : ChessPiece(p, c)
{
    type = PieceType::Horse;
    is_alive = true;

    if (c == Camp::Black)
        img = *ResourcesManager::instance()->find_image("horse_black");
    else
        img = *ResourcesManager::instance()->find_image("horse_red");
}
void Horse::on_render(const Camera& camera) { ChessPiece::on_render(camera); }
void Horse::on_input(const ExMessage& msg) { }
void Horse::on_update(int delta) { }
void Horse::can_move_to() { }

Chariot::Chariot(const Vector2& p, Camp c) : ChessPiece(p, c)
{
    type = PieceType::Chariot;
    is_alive = true;

    if (c == Camp::Black)
        img = *ResourcesManager::instance()->find_image("chariot_black");
    else
        img = *ResourcesManager::instance()->find_image("chariot_red");
}
void Chariot::on_render(const Camera& camera) { ChessPiece::on_render(camera); }
void Chariot::on_input(const ExMessage& msg) { }
void Chariot::on_update(int delta) { }
void Chariot::can_move_to() { }

Cannon::Cannon(const Vector2& p, Camp c) : ChessPiece(p, c)
{
    type = PieceType::Cannon;
    is_alive = true;

    if (c == Camp::Black)
        img = *ResourcesManager::instance()->find_image("cannon_black");
    else
        img = *ResourcesManager::instance()->find_image("cannon_red");
}
void Cannon::on_render(const Camera& camera) { ChessPiece::on_render(camera); }
void Cannon::on_input(const ExMessage& msg) { }
void Cannon::on_update(int delta) { }
void Cannon::can_move_to() { }

Soldier::Soldier(const Vector2& p, Camp c) : ChessPiece(p, c)
{
    type = PieceType::Soldier;
    is_alive = true;

    if (c == Camp::Black)
        img = *ResourcesManager::instance()->find_image("soldier_black");
    else
        img = *ResourcesManager::instance()->find_image("soldier_red");
}
void Soldier::on_render(const Camera& camera) { ChessPiece::on_render(camera); }
void Soldier::on_input(const ExMessage& msg) { }
void Soldier::on_update(int delta) { }
void Soldier::can_move_to() { }