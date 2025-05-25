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
void General::on_update(int delta) { ChessPiece::on_update(delta); }
std::vector<Vector2> General::get_can_move_to(const int(&board)[9][10])
{
    std::vector<Vector2> moves;
    const int dx[4] = {1,0,-1,0};
    const int dy[4] = {0,1,0,-1};
    for (int i = 0; i < 4; i++)
    {
        int x = pos.x, y = pos.y;
        x += dx[i], y += dy[i];
        if (camp == Camp::Red)
        {
            if (x < 3 || x>5 || y > 9 || y < 7)continue;
            if (board[x][y] != 0)continue;
            for (int j = y -1;j >= 0;j--)
            {
                if (board[x][j] == 0)continue;
                if (board[x][j] == 1)break;
				moves.push_back({ (float)x, (float)y });
                break;
            }
        }
        else
        {
            if (x < 3 || x>5 || y > 2 || y < 0)continue;
			if (board[x][y] != 0)continue;
            for (int j = y + 1;j <= 9;j++)
            {
                if (board[x][j] == 0)continue;
                if (board[x][j] == 101)break;
                moves.push_back({ (float)x, (float)y });
                break;
            }
        }
    }
    
    return moves;
}

std::vector<Vector2> General::get_can_eat(const int(&board)[9][10])
{
    std::vector<Vector2> eats;
    const int dx[4] = { 1,0,-1,0 };
    const int dy[4] = { 0,1,0,-1 };
    for (int i = 0; i < 4; i++)
    {
        int x = pos.x, y = pos.y;
        x += dx[i], y += dy[i];
        if (camp == Camp::Red)
        {
            if (x < 3 || x>5 || y > 9 || y < 7)continue;
        }
        else
        {
            if (x < 3 || x>5 || y > 2 || y < 0)continue;
        }
        if (board[x][y] != 0 && abs(board[x][y] - board[(int)pos.x][(int)pos.y]) >= 80)
        {
            eats.push_back({ (float)x, (float)y });
        }
    }
    if (camp == Camp::Red)
    {
        for (int i = pos.y - 1; i >= 0; i--)
        {
            if (board[(int)pos.x][i] != 0)
            {
                if (board[(int)pos.x][i] == 1)
                {
                    eats.push_back({ pos.x, (float)i });
                    break;
                }
                else
                    break;
            }
        }
    }
    else
    {
        for (int i = pos.y + 1; i <=9; i++)
        {
            if (board[(int)pos.x][i] != 0)
            {
                if (board[(int)pos.x][i] == 101)
                {
                    eats.push_back({ pos.x, (float)i });
                    break;
                }
                else
                    break;
            }
        }
    }
    return eats;
}

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
void Advisor::on_update(int delta) { ChessPiece::on_update(delta); }
std::vector<Vector2> Advisor::get_can_move_to(const int(&board)[9][10])
{
    std::vector<Vector2> moves;
    const int dx[4] = { 1,-1,1,-1 };
    const int dy[4] = { 1,1,-1,-1 };
    for (int i = 0; i < 4; i++)
    {
        int x = pos.x, y = pos.y;
        x += dx[i], y += dy[i];
        if (camp == Camp::Red)
        {
            if (x < 3 || x>5 || y > 9 || y < 7)continue;
        }
        else
        {
            if (x < 3 || x>5 || y > 2 || y < 0)continue;
        }
        if (board[x][y] == 0)
        {
            moves.push_back({ (float)x, (float)y });
        }
    }

    return moves;
}

std::vector<Vector2> Advisor::get_can_eat(const int(&board)[9][10])
{
    std::vector<Vector2> eats;
    const int dx[4] = { 1,-1,1,-1 };
    const int dy[4] = { 1,1,-1,-1 };
    for (int i = 0; i < 4; i++)
    {
        int x = pos.x, y = pos.y;
        x += dx[i], y += dy[i];
        if (camp == Camp::Red)
        {
            if (x < 3 || x>5 || y > 9 || y < 7)continue;
        }
        else
        {
            if (x < 3 || x>5 || y > 2 || y < 0)continue;
        }
        if (board[x][y] != 0 && abs(board[x][y] - board[(int)pos.x][(int)pos.y]) >= 80)
        {
            eats.push_back({ (float)x, (float)y });
        }
    }

    return eats;
}

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
void Elephant::on_update(int delta) { ChessPiece::on_update(delta); }
std::vector<Vector2> Elephant::get_can_move_to(const int(&board)[9][10])
{
    std::vector<Vector2> moves;
    const int dx[4] = { 2,-2,2,-2 };
    const int dy[4] = { 2,2,-2,-2 };
    for (int i = 0; i < 4; i++)
    {
        int x = pos.x, y = pos.y;
        x += dx[i], y += dy[i];
        if (camp == Camp::Red)
        {
            if (x < 0 || x > 8 || y > 9 || y < 5)continue;
        }
        else
        {
            if (x < 0 || x > 8 || y > 4  || y < 0)continue;
        }
        if (board[x][y] == 0 && board[(int)((x + pos.x) / 2)][(int)((y + pos.y) / 2)] == 0)
        {
            moves.push_back({ (float)x, (float)y });
        }
    }

    return moves;
}

std::vector<Vector2> Elephant::get_can_eat(const int(&board)[9][10])
{
    std::vector<Vector2> eats;
    const int dx[4] = { 2,-2,2,-2 };
    const int dy[4] = { 2,2,-2,-2 };
    for (int i = 0; i < 4; i++)
    {
        int x = pos.x, y = pos.y;
        x += dx[i], y += dy[i];
        if (camp == Camp::Red)
        {
            if (x < 0 || x > 8 || y > 9 || y < 5)continue;
        }
        else
        {
            if (x < 0 || x > 8 || y > 4 || y < 0)continue;
        }
        if (board[x][y] != 0 && board[(int)((x + pos.x) / 2)][(int)((y + pos.y) / 2)] == 0 && abs(board[x][y] - board[(int)pos.x][(int)pos.y]) >= 80)
        {
            eats.push_back({ (float)x, (float)y });
        }
    }

    return eats;
}

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
void Horse::on_update(int delta) { ChessPiece::on_update(delta); }
std::vector<Vector2> Horse::get_can_move_to(const int(&board)[9][10])
{
    std::vector<Vector2> moves;
    const int move_dx[8] = { 1, 2, -1, -2, -2, -1, 2, 1 };
    const int move_dy[8] = { 2, 1, 2, 1, -1, -2, -1, -2 };

    const int leg_dx[8] = { 0, 1, 0, -1, -1, 0, 1, 0 };
    const int leg_dy[8] = { 1, 0, 1, 0, 0, -1, 0, -1 };
    for (int i = 0; i < 8; ++i)
    {
        int leg_x = pos.x + leg_dx[i];
        int leg_y = pos.y + leg_dy[i];
        int dx = pos.x + move_dx[i];
        int dy = pos.y + move_dy[i];

        if (dx < 0 || dx > 8 || dy < 0 || dy > 9)
            continue;

        if (board[leg_x][leg_y] != 0 || board[dx][dy] != 0)
            continue;

        moves.push_back({ (float)dx, (float)dy });
    }

    return moves;
}

std::vector<Vector2> Horse::get_can_eat(const int(&board)[9][10])
{
    std::vector<Vector2> eats;
    const int move_dx[8] = { 1, 2, -1, -2, -2, -1, 2, 1 };
    const int move_dy[8] = { 2, 1, 2, 1, -1, -2, -1, -2 };

    const int leg_dx[8] = { 0, 1, 0, -1, -1, 0, 1, 0 };
    const int leg_dy[8] = { 1, 0, 1, 0, 0, -1, 0, -1 };
    for (int i = 0; i < 8; ++i)
    {
        int leg_x = pos.x + leg_dx[i];
        int leg_y = pos.y + leg_dy[i];
        int dx = pos.x + move_dx[i];
        int dy = pos.y + move_dy[i];

        if (dx < 0 || dx > 8 || dy < 0 || dy > 9)
            continue;

        if (board[leg_x][leg_y] != 0 || board[dx][dy] == 0)
            continue;

        if (abs(board[(int)pos.x][(int)pos.y] - board[dx][dy]) >= 80)
            eats.push_back({ (float)dx, (float)dy });
    }

    return eats;
}

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
void Chariot::on_update(int delta) { ChessPiece::on_update(delta); }
std::vector<Vector2> Chariot::get_can_move_to(const int(&board)[9][10])
{
    std::vector<Vector2> moves;
    int x = pos.x;
    int y = pos.y;

    // 向上
    for (int i = y - 1; i >= 0; --i)
    {
        if (board[x][i] == 0)
        {
            moves.push_back({ (float)x, (float)i });                   
        }   
        else
        {
            break;
        }
    }
    // 向下
    for (int i = y + 1; i <= 9; ++i)
    {
        if (board[x][i] == 0)
        {
            moves.push_back({ (float)x, (float)i });
        }
        else
        {
            break;
        }
    }
    // 向左
    for (int i = x - 1; i >= 0; --i)
    {
        if (board[i][y] == 0)
        {
            moves.push_back({ (float)i, (float)y });
        }
        else
        {
            break;
        }
    }

    // 向右
    for (int i = x + 1; i <= 8; ++i)
    {
        if (board[i][y] == 0)
        {
            moves.push_back({ (float)i, (float)y });
        }
        else
        {
            break;
        }
    }

    return moves;
}

std::vector<Vector2> Chariot::get_can_eat(const int(&board)[9][10])
{
    std::vector<Vector2> eats;
    int x = pos.x;
    int y = pos.y;

    // 向上
    for (int i = y - 1; i >= 0; --i)
    {
        if (board[x][i] != 0)
        {
            if(abs(board[x][i] - board[x][y]) >= 80)
                eats.push_back({ (float)x, (float)i });
            break;
        }
    }
    // 向下
    for (int i = y + 1; i <= 9; ++i)
    {
        if (board[x][i] != 0)
        {
            if (abs(board[x][i] - board[x][y]) >= 80)
                eats.push_back({ (float)x, (float)i });
            break;
        }
    }
    // 向左
    for (int i = x - 1; i >= 0; --i)
    {
        if (board[i][y] != 0)
        {
            if (abs(board[i][y] - board[x][y]) >= 80)
                eats.push_back({ (float)i, (float)y });
            break;
        }
    }

    // 向右
    for (int i = x + 1; i <= 8; ++i)
    {
        if (board[i][y] != 0)
        {
            if (abs(board[i][y] - board[x][y]) >= 80)
                eats.push_back({ (float)i, (float)y });
            break;
        }
    }

    return eats;
}


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
void Cannon::on_update(int delta) { ChessPiece::on_update(delta); }
std::vector<Vector2> Cannon::get_can_move_to(const int(&board)[9][10])
{
    std::vector<Vector2> moves;
    int x = pos.x;
    int y = pos.y;

    // 向上
    for (int i = y - 1; i >= 0; --i)
    {
        if (board[x][i] == 0)
        {
            moves.push_back({ (float)x, (float)i });
        }
        else
        {
            break;
        }
    }
    // 向下
    for (int i = y + 1; i <= 9; ++i)
    {
        if (board[x][i] == 0)
        {
            moves.push_back({ (float)x, (float)i });
        }
        else
        {
            break;
        }
    }
    // 向左
    for (int i = x - 1; i >= 0; --i)
    {
        if (board[i][y] == 0)
        {
            moves.push_back({ (float)i, (float)y });
        }
        else
        {
            break;
        }
    }

    // 向右
    for (int i = x + 1; i <= 8; ++i)
    {
        if (board[i][y] == 0)
        {
            moves.push_back({ (float)i, (float)y });
        }
        else
        {
            break;
        }
    }

    return moves;
}

std::vector<Vector2> Cannon::get_can_eat(const int(&board)[9][10])
{
    std::vector<Vector2> eats;
    int x = pos.x;
    int y = pos.y;
    int flag = 0;

    // 向上
    for (int i = y - 1; i >= 0; --i)
    {
        if (board[x][i] != 0)
        {
            if (flag == 0)
            {
                // 第一次遇到棋子
                flag = 1;
            }
            else
            {
                if (abs(board[x][y] - board[x][i]) >= 80)
                {
                    eats.push_back({ (float)x, (float)i });
                }
                break;
            }
        }
    }
    // 向下
    for (int i = y + 1, flag = 0; i <= 9; ++i)
    {
        if (board[x][i] != 0)
        {
            if (flag == 0)
            {
                // 第一次遇到棋子
                flag = 1;
            }
            else
            {
                if (abs(board[x][y] - board[x][i]) >= 80)
                {
                    eats.push_back({ (float)x, (float)i });
                }
                break;
            }
        }
    }
    // 向左
    for (int i = x - 1, flag = 0; i >= 0; --i)
    {
        if (board[i][y] != 0)
        {
            if (flag == 0)
            {
                // 第一次遇到棋子
                flag = 1;
            }
            else
            {
                if (abs(board[x][y] - board[i][y]) >= 80)
                {
                    eats.push_back({ (float)i, (float)y });
                }
                break;
            }
        }
    }

    // 向右
    for (int i = x + 1, flag = 0; i <= 8; ++i)
    {
        if (board[i][y] != 0)
        {
            if (flag == 0)
            {
                // 第一次遇到棋子
                flag = 1;
            }
            else
            {
                if (abs(board[x][y] - board[i][y]) >= 80)
                {
                    eats.push_back({ (float)i, (float)y });
                }
                break;
            }
        }
    }

    return eats;
}


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
void Soldier::on_update(int delta) { ChessPiece::on_update(delta); }
std::vector<Vector2> Soldier::get_can_move_to(const int(&board)[9][10])
{
    std::vector<Vector2> moves;
    int x = pos.x;
    int y = pos.y;

    if (camp == Camp::Red)
    {
        // 向上
        if (y - 1 >= 0 && board[x][y - 1] == 0)
        {
            moves.push_back({ (float)x, (float)(y - 1) });
        }

        // 过河后可以左右走
        if (y <= 4) 
        {
            if (x - 1 >= 0 && board[x - 1][y] == 0)
                moves.push_back({ (float)(x - 1), (float)y });
            if (x + 1 <= 8 && board[x + 1][y] == 0)
                moves.push_back({ (float)(x + 1), (float)y });
        }
    }
    else
    {
        // 向下
        if (y + 1 <= 9 && board[x][y + 1] == 0)
        {
            moves.push_back({ (float)x, (float)(y + 1) });
        }

        // 过河后可以左右走
        if (y >= 5)
        {
            if (x - 1 >= 0 && board[x - 1][y] == 0)
                moves.push_back({ (float)(x - 1), (float)y });
            if (x + 1 <= 8 && board[x + 1][y] == 0)
                moves.push_back({ (float)(x + 1), (float)y });
        }
    }

    return moves;
}

std::vector<Vector2> Soldier::get_can_eat(const int(&board)[9][10])
{
    std::vector<Vector2> eats;
    int x = pos.x;
    int y = pos.y;

    if (camp == Camp::Red)
    {
        // 向上
        if (y - 1 >= 0 && board[x][y - 1] != 0 && abs(board[x][y - 1] - board[x][y]) >= 80)
        {
           eats.push_back({ (float)x, (float)(y - 1) });
        }

        // 过河后可以左右走
        if (y <= 4)
        {
            if (x - 1 >= 0 && board[x - 1][y] != 0 && abs(board[x - 1][y] - board[x][y]) >= 80)
                eats.push_back({ (float)(x - 1), (float)y });
            if (x + 1 <= 8 && board[x + 1][y] != 0 && abs(board[x + 1][y] - board[x][y]) >= 80)
                eats.push_back({ (float)(x + 1), (float)y });
        }
    }
    else
    {
        // 向下
        if (y + 1 <= 9 && board[x][y + 1] != 0 && abs(board[x][y + 1] - board[x][y]) >= 80)
        {
            eats.push_back({ (float)x, (float)(y + 1) });
        }

        // 过河后可以左右走
        if (y >= 5)
        {
            if (x - 1 >= 0 && board[x - 1][y] != 0 && abs(board[x - 1][y] - board[x][y]) >= 80)
                eats.push_back({ (float)(x - 1), (float)y });
            if (x + 1 <= 8 && board[x + 1][y] == 0 && abs(board[x + 1][y] - board[x][y]) >= 80)
                eats.push_back({ (float)(x + 1), (float)y });
        }
    }

    return eats;
}






// 轻量级车的可移动位置
std::vector<Vector2> SChariot::get_can_move_to(const int(&board)[9][10]) {
    std::vector<Vector2> moves;
    int x = pos.x;
    int y = pos.y;

    // 向上
    for (int i = y - 1; i >= 0; --i) {
        if (board[x][i] == 0) {
            moves.push_back({ (float)x, (float)i });
        }
        else {
            break;
        }
    }
    // 向下
    for (int i = y + 1; i <= 9; ++i) {
        if (board[x][i] == 0) {
            moves.push_back({ (float)x, (float)i });
        }
        else {
            break;
        }
    }
    // 向左
    for (int i = x - 1; i >= 0; --i) {
        if (board[i][y] == 0) {
            moves.push_back({ (float)i, (float)y });
        }
        else {
            break;
        }
    }
    // 向右
    for (int i = x + 1; i <= 8; ++i) {
        if (board[i][y] == 0) {
            moves.push_back({ (float)i, (float)y });
        }
        else {
            break;
        }
    }
    return moves;
}

// 轻量级车的可吃子位置
std::vector<Vector2> SChariot::get_can_eat(const int(&board)[9][10]) {
    std::vector<Vector2> eats;
    int x = pos.x;
    int y = pos.y;

    // 向上
    for (int i = y - 1; i >= 0; --i) {
        if (board[x][i] != 0) {
            if (abs(board[x][i] - board[x][y]) >= 80)
                eats.push_back({ (float)x, (float)i });
            break;
        }
    }
    // 向下
    for (int i = y + 1; i <= 9; ++i) {
        if (board[x][i] != 0) {
            if (abs(board[x][i] - board[x][y]) >= 80)
                eats.push_back({ (float)x, (float)i });
            break;
        }
    }
    // 向左
    for (int i = x - 1; i >= 0; --i) {
        if (board[i][y] != 0) {
            if (abs(board[i][y] - board[x][y]) >= 80)
                eats.push_back({ (float)i, (float)y });
            break;
        }
    }
    // 向右
    for (int i = x + 1; i <= 8; ++i) {
        if (board[i][y] != 0) {
            if (abs(board[i][y] - board[x][y]) >= 80)
                eats.push_back({ (float)i, (float)y });
            break;
        }
    }
    return eats;
}
//轻量级士的可移动位置
std::vector<Vector2> SAdvisor::get_can_move_to(const int(&board)[9][10]) {
    std::vector<Vector2> moves;
    const int dx[4] = { 1,-1,1,-1 };
    const int dy[4] = { 1,1,-1,-1 };
    for (int i = 0; i < 4; i++)
    {
        int x = pos.x, y = pos.y;
        x += dx[i], y += dy[i];
        if (camp == ChessPiece::Camp::Red)
        {
            if (x < 3 || x>5 || y > 9 || y < 7)continue;
        }
        else
        {
            if (x < 3 || x>5 || y > 2 || y < 0)continue;
        }
        if (board[x][y] == 0)
        {
            moves.push_back({ (float)x, (float)y });
        }
    }

    return moves;
}
//轻量级士的可吃子位置
std::vector<Vector2> SAdvisor::get_can_eat(const int(&board)[9][10]) {
    std::vector<Vector2> eats;
    const int dx[4] = { 1,-1,1,-1 };
    const int dy[4] = { 1,1,-1,-1 };
    for (int i = 0; i < 4; i++)
    {
        int x = pos.x, y = pos.y;
        x += dx[i], y += dy[i];
        if (camp == ChessPiece::Camp::Red)
        {
            if (x < 3 || x>5 || y > 9 || y < 7)continue;
        }
        else
        {
            if (x < 3 || x>5 || y > 2 || y < 0)continue;
        }
        if (board[x][y] != 0 && abs(board[x][y] - board[(int)pos.x][(int)pos.y]) >= 80)
        {
            eats.push_back({ (float)x, (float)y });
        }
    }
    return eats;
}
//轻量级象的可移动位置
std::vector<Vector2> SElephant::get_can_move_to(const int(&board)[9][10]) {
    std::vector<Vector2> moves;
    const int dx[4] = { 2,-2,2,-2 };
    const int dy[4] = { 2,2,-2,-2 };
    for (int i = 0; i < 4; i++)
    {
        int x = pos.x, y = pos.y;
        x += dx[i], y += dy[i];
        if (camp == ChessPiece::Camp::Red)
        {
            if (x < 0 || x > 8 || y > 9 || y < 5)continue;
        }
        else
        {
            if (x < 0 || x > 8 || y > 4 || y < 0)continue;
        }
        if (board[x][y] == 0 && board[(int)((x + pos.x) / 2)][(int)((y + pos.y) / 2)] == 0)
        {
            moves.push_back({ (float)x, (float)y });
        }
    }
    return moves;
}
//轻量级象的可吃子位置
std::vector<Vector2> SElephant::get_can_eat(const int(&board)[9][10]) {
    std::vector<Vector2> eats;
    const int dx[4] = { 2,-2,2,-2 };
    const int dy[4] = { 2,2,-2,-2 };
    for (int i = 0; i < 4; i++)
    {
        int x = pos.x, y = pos.y;
        x += dx[i], y += dy[i];
        if (camp == ChessPiece::Camp::Red)
        {
            if (x < 0 || x > 8 || y > 9 || y < 5)continue;
        }
        else
        {
            if (x < 0 || x > 8 || y > 4 || y < 0)continue;
        }
        if (board[x][y] != 0 && board[(int)((x + pos.x) / 2)][(int)((y + pos.y) / 2)] == 0 && abs(board[x][y] - board[(int)pos.x][(int)pos.y]) >= 80)
        {
            eats.push_back({ (float)x, (float)y });
        }
    }
    return eats;
}
//轻量级马的可移动位置
std::vector<Vector2> SHorse::get_can_move_to(const int(&board)[9][10]) {
    std::vector<Vector2> moves;
    const int move_dx[8] = { 1, 2, -1, -2, -2, -1, 2, 1 };
    const int move_dy[8] = { 2, 1, 2, 1, -1, -2, -1, -2 };
    const int leg_dx[8] = { 0, 1, 0, -1, -1, 0, 1, 0 };
    const int leg_dy[8] = { 1, 0, 1, 0, 0, -1, 0, -1 };
    for (int i = 0; i < 8; ++i)
    {
        int leg_x = pos.x + leg_dx[i];
        int leg_y = pos.y + leg_dy[i];
        int dx = pos.x + move_dx[i];
        int dy = pos.y + move_dy[i];
        if (dx < 0 || dx > 8 || dy < 0 || dy > 9)
            continue;
        if (board[leg_x][leg_y] != 0 || board[dx][dy] != 0)
            continue;
        moves.push_back({ (float)dx, (float)dy });
    }
    return moves;
}
//轻量级马的可吃子位置
std::vector<Vector2> SHorse::get_can_eat(const int(&board)[9][10]) {
    std::vector<Vector2> eats;
    const int move_dx[8] = { 1, 2, -1, -2, -2, -1, 2, 1 };
    const int move_dy[8] = { 2, 1, 2, 1, -1, -2, -1, -2 };
    const int leg_dx[8] = { 0, 1, 0, -1, -1, 0, 1, 0 };
    const int leg_dy[8] = { 1, 0, 1, 0, 0, -1, 0, -1 };
    for (int i = 0; i < 8; ++i)
    {
        int leg_x = pos.x + leg_dx[i];
        int leg_y = pos.y + leg_dy[i];
        int dx = pos.x + move_dx[i];
        int dy = pos.y + move_dy[i];
        if (dx < 0 || dx > 8 || dy < 0 || dy > 9)
            continue;
        if (board[leg_x][leg_y] != 0 || board[dx][dy] == 0)
            continue;
        if (abs(board[(int)pos.x][(int)pos.y] - board[dx][dy]) >= 80)
            eats.push_back({ (float)dx, (float)dy });
    }
    return eats;
}
//轻量级将的可移动位置
std::vector<Vector2> SGeneral::get_can_move_to(const int(&board)[9][10])
{
    std::vector<Vector2> moves;
    const int dx[4] = { 1,0,-1,0 };
    const int dy[4] = { 0,1,0,-1 };
    for (int i = 0; i < 4; i++)
    {
        int x = pos.x, y = pos.y;
        x += dx[i], y += dy[i];
        if (camp == ChessPiece::Camp::Red)
        {
            if (x < 3 || x>5 || y > 9 || y < 7)continue;
            if (board[x][y] != 0)continue;
            for (int j = y - 1;j >= 0;j--)
            {
                if (board[x][j] == 0)continue;
                if (board[x][j] == 1)break;
                moves.push_back({ (float)x, (float)y });
                break;
            }
        }
        else
        {
            if (x < 3 || x>5 || y > 2 || y < 0)continue;
            if (board[x][y] != 0)continue;
            for (int j = y + 1;j <= 9;j++)
            {
                if (board[x][j] == 0)continue;
                if (board[x][j] == 101)break;
                moves.push_back({ (float)x, (float)y });
                break;
            }
        }
	}
	return moves;
}
//轻量级将的可吃子位置
std::vector<Vector2> SGeneral::get_can_eat(const int(&board)[9][10])
{
    std::vector<Vector2> eats;
    const int dx[4] = { 1,0,-1,0 };
    const int dy[4] = { 0,1,0,-1 };
    for (int i = 0; i < 4; i++)
    {
        int x = pos.x, y = pos.y;
		x += dx[i], y += dy[i];
        if (camp == ChessPiece::Camp::Red)
        {
            if (x < 3 || x>5 || y > 9 || y < 7)continue;
        }
        else
        {
            if (x < 3 || x>5 || y > 2 || y < 0)continue;
        }
        if (board[x][y] != 0 && abs(board[x][y] - board[(int)pos.x][(int)pos.y]) >= 80)
        {
			// 吃对面的将(以后写)
            if (board[x][y] == 100 || board[x][y] == 200)
            {
                eats.push_back({ (float)x, (float)y });
            }
            else
            {
                eats.push_back({ (float)x, (float)y });
            }
        }
    }
    if (camp == ChessPiece::Camp::Red)
    {
        for (int i = pos.y - 1; i >= 0; i--)
        {
            if (board[(int)pos.x][i] != 0)
            {
                if (board[(int)pos.x][i] == 1)
                {
                    eats.push_back({ pos.x, (float)i });
                    break;
                }
                else
                    break;
            }
        }
    }
    else
    {
        for (int i = pos.y + 1; i <= 9; i++)
        {
            if (board[(int)pos.x][i] != 0)
            {
                if (board[(int)pos.x][i] == 101)
                {
                    eats.push_back({ pos.x, (float)i });
                    break;
                }
                else
                    break;
            }
        }
    }
	return eats;
}
std::vector<Vector2> SCannon::get_can_move_to(const int(&board)[9][10])
{
    std::vector<Vector2> moves;
    int x = pos.x;
    int y = pos.y;
    // 向上
    for (int i = y - 1; i >= 0; --i)
    {
        if (board[x][i] == 0)
        {
            moves.push_back({ (float)x, (float)i });
        }
        else
        {
            break;
        }
    }
    // 向下
    for (int i = y + 1; i <= 9; ++i)
    {
        if (board[x][i] == 0)
        {
            moves.push_back({ (float)x, (float)i });
        }
        else
        {
            break;
        }
    }
    // 向左
    for (int i = x - 1; i >= 0; --i)
    {
        if (board[i][y] == 0)
        {
            moves.push_back({ (float)i, (float)y });
        }
        else
        {
            break;
        }
    }
    // 向右
    for (int i = x + 1; i <= 8; ++i)
    {
        if (board[i][y] == 0)
        {
            moves.push_back({ (float)i, (float)y });
        }
        else
        {
            break;
        }
    }
    return moves;
}

std::vector<Vector2> SCannon::get_can_eat(const int(&board)[9][10])
{
    std::vector<Vector2> eats;
    int x = pos.x;
    int y = pos.y;
    int flag = 0;
    // 向上
    for (int i = y - 1; i >= 0; --i)
    {
        if (board[x][i] != 0)
        {
            if (flag == 0)
            {
                // 第一次遇到棋子
                flag = 1;
            }
            else
            {
                if (abs(board[x][y] - board[x][i]) >= 80)
                {
                    eats.push_back({ (float)x, (float)i });
                }
                break;
            }
        }
    }
    // 向下
    for (int i = y + 1, flag = 0; i <= 9; ++i)
    {
        if (board[x][i] != 0)
        {
            if (flag == 0)
            {
                // 第一次遇到棋子
                flag = 1;
            }
            else
            {
                if (abs(board[x][y] - board[x][i]) >= 80)
                {
                    eats.push_back({ (float)x, (float)i });
                }
                break;
            }
        }
    }
    // 向左
    for (int i = x - 1, flag = 0; i >= 0; --i)
    {
        if (board[i][y] != 0)
        {
            if (flag == 0)
            {
                // 第一次遇到棋子
                flag = 1;
            }
            else
            {
                if (abs(board[x][y] - board[i][y]) >= 80)
                {
                    eats.push_back({ (float)i, (float)y });
                }
                break;
            }
        }
    }
    // 向右
    for (int i = x + 1, flag = 0; i <= 8; ++i)
    {
        if (board[i][y] != 0)
        {
            if (flag == 0)
            {
                // 第一次遇到棋子
                flag = 1;
            }
            else
            {
				if (abs(board[x][y] - board[i][y]) >= 80)
                {
                    eats.push_back({ (float)i, (float)y });
                }
                break;
            }
        }
	}
	return eats;
}

// 轻量级卒的可移动位置
std::vector<Vector2> SSoldier::get_can_move_to(const int(&board)[9][10])
{
    std::vector<Vector2> moves;
    int x = pos.x;
    int y = pos.y;
    if (camp == ChessPiece::Camp::Red)
    {
        // 向上
        if (y - 1 >= 0 && board[x][y - 1] == 0)
        {
            moves.push_back({ (float)x, (float)(y - 1) });
        }
        // 过河后可以左右走
        if (y <= 4)
        {
            if (x - 1 >= 0 && board[x - 1][y] == 0)
                moves.push_back({ (float)(x - 1), (float)y });
            if (x + 1 <= 8 && board[x + 1][y] == 0)
                moves.push_back({ (float)(x + 1), (float)y });
        }
    }
    else
    {
        // 向下
        if (y + 1 <= 9 && board[x][y + 1] == 0)
        {
            moves.push_back({ (float)x, (float)(y + 1) });
        }
        // 过河后可以左右走
        if (y >= 5)
        {
            if (x - 1 >= 0 && board[x - 1][y] == 0)
                moves.push_back({ (float)(x - 1), (float)y });
            if (x + 1 <= 8 && board[x + 1][y] == 0)
                moves.push_back({ (float)(x + 1), (float)y });
        }
    }
    return moves;
}

// 轻量级卒的可吃子位置
std::vector<Vector2> SSoldier::get_can_eat(const int(&board)[9][10])
{
    std::vector<Vector2> eats;
    int x = pos.x;
    int y = pos.y;
    if (camp == ChessPiece::Camp::Red)
    {
        // 向上
        if (y - 1 >= 0 && board[x][y - 1] != 0 && abs(board[x][y - 1] - board[x][y]) >= 80)
        {
            eats.push_back({ (float)x, (float)(y - 1) });
        }
        // 过河后可以左右走
        if (y <= 4)
        {
            if (x - 1 >= 0 && board[x - 1][y] != 0 && abs(board[x - 1][y] - board[x][y]) >= 80)
                eats.push_back({ (float)(x - 1), (float)y });
            if (x + 1 <= 8 && board[x + 1][y] != 0 && abs(board[x + 1][y] - board[x][y]) >= 80)
                eats.push_back({ (float)(x + 1), (float)y });
        }
    }
    else
    {
        // 向下
        if (y + 1 <= 9 && board[x][y + 1] != 0 && abs(board[x][y + 1] - board[x][y]) >= 80)
        {
            eats.push_back({ (float)x, (float)(y + 1) });
        }
        // 过河后可以左右走
        if (y >= 5)
        {
            if (x - 1 >= 0 && board[x - 1][y] != 0 && abs(board[x - 1][y] - board[x][y]) >= 80)
                eats.push_back({ (float)(x - 1), (float)y });
            if (x + 1 <= 8 && board[x + 1][y] == 0 && abs(board[x + 1][y] - board[x][y]) >= 80)
                eats.push_back({ (float)(x + 1), (float)y });
        }
    }
    return eats;
}
