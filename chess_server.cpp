#define _WINSOCKAPI_
#define WIN32_LEAN_AND_MEAN

#include "chess_server.h"
#include "httplib.h"
#include <iostream>

ChessServer::ChessServer(const std::string& ip, int port)
    : ip_(ip), port_(port), running_(false) {}

ChessServer::~ChessServer()
{
    stop();
}

void ChessServer::start()
{
    if (running_) return;

    server_ = std::make_unique<httplib::Server>();

    server_->Post("/join", [&](const httplib::Request& req, httplib::Response& res) 
        {
            std::lock_guard<std::mutex> lock(mutex_);

            if (has_another)
            {
                res.set_content("-1", "text/plain");
                return;
            }

            res.set_content("1", "text/plain");
            has_another = true;
        });

    server_->Get("/get_move1", [&](const httplib::Request&, httplib::Response& res)
        {
            std::lock_guard<std::mutex> lock(mutex_);
            res.set_content(std::to_string(last_move_1), "text/plain");
        });

    server_->Post("/post_move1", [&](const httplib::Request& req, httplib::Response& res) 
        {
            last_move_1 = std::stoi(req.body);
        });

    server_->Get("/get_move2", [&](const httplib::Request&, httplib::Response& res)
        {
            std::lock_guard<std::mutex> lock(mutex_);
            res.set_content(std::to_string(last_move_2), "text/plain");
        });

    server_->Post("/post_move2", [&](const httplib::Request& req, httplib::Response& res)
        {
            last_move_2 = std::stoi(req.body);
        });

    running_ = true;
    server_thread_ = std::thread([this]()
        {
            server_->listen(ip_.c_str(), port_);
        });
}

void ChessServer::stop()
{
    if (!running_) return;

    server_->stop();
    if (server_thread_.joinable())
        server_thread_.join();
    server_.reset();
    running_ = false;
}

int ChessServer::get_last_move1() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return last_move_1;
}

void ChessServer::set_last_move1(int move_code)
{
    std::lock_guard<std::mutex> lock(mutex_);
    last_move_1 = move_code;
}

int ChessServer::get_last_move2() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return last_move_2;
}

void ChessServer::set_last_move2(int move_code)
{
    std::lock_guard<std::mutex> lock(mutex_);
    last_move_2 = move_code;
}

bool ChessServer::is_ready() const
{
    return has_another;
}

