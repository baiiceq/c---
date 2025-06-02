#define _WINSOCKAPI_
#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#include "httplib.h"
#include "chess_client.h"

#pragma comment(lib, "ws2_32.lib")

ChessClient::ChessClient(const std::string& ip, int port)
    : ip_(ip), port_(port), player_id_(0) {}

bool ChessClient::join()
{
    httplib::Client cli(ip_, port_);
    auto res = cli.Post("/join");
    if (res && res->status == 200) 
    {
        std::string body = res->body;
        if (body == "1") 
        {
            player_id_ = 1;
            std::cout << "Joined room as player " << player_id_ << std::endl;
            return true;
        }
        else if (body == "-1") 
        {
            std::cout << "Room full, cannot join." << std::endl;
            player_id_ = -1;
            return false;
        }
    }
    std::cout << "Join failed." << std::endl;
    return false;
}

bool ChessClient::send_move(int move_code, int is_host)
{
    httplib::Client cli(ip_, port_);
    auto res = is_host ? cli.Post("/post_move1", std::to_string(move_code), "text/plain") : cli.Post("/post_move2", std::to_string(move_code), "text/plain");
    std::cout << (res && res->status == 200) << std::endl;
    return res && res->status == 200;
}

int ChessClient::get_opponent_move(int is_host) 
{
    httplib::Client cli(ip_, port_);
    auto res = is_host ? cli.Get("/get_move2") : cli.Get("/get_move1");
    if (res && res->status == 200) 
    {
        return std::stoi(res->body);
    }
    return -1;
}