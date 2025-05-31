#pragma once

#include <string>
#include <iostream>

class ChessClient
{
public:
    ChessClient(const std::string& ip, int port);

    bool join();
    bool send_move(int move_code, int is_host);
    int get_opponent_move(int is_host);
    int get_player_id() const
    {
        return player_id_;
    }

private:
    std::string ip_;
    int port_;
    int player_id_;
};
