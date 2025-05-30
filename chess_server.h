#pragma once

#include <mutex>
#include <thread>

namespace httplib {
    class Server;
}

class ChessServer
{
public:
    ChessServer(const std::string& ip = "127.0.0.1", int port = 8080);
    ~ChessServer();

    void start();  // 启动服务器
    void stop();   // 停止服务器

    // 获取最后一次接收到的走法编码（线程安全）
    int get_last_move1() const;

    // 设置最新的走法编码（线程安全）;
    void set_last_move1(int move_code);

    int get_last_move2() const;

    void set_last_move2(int move_code);
    bool is_ready() const;

private:
    std::string ip_;
    int port_;
    std::unique_ptr<httplib::Server> server_;
    std::thread server_thread_;
    std::atomic<bool> running_;
    mutable std::mutex mutex_;
    int last_move_1 = -1;
    int last_move_2 = -1;
    bool has_another = false;
};