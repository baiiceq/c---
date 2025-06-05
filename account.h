#pragma once
#include <string>
#include <vector>

#include "util.h"
#include "chess_piece.h"

class Account
{
public:
    enum class AccountError
    {
        Null,
        None,
        InvalidUsername,
        InvalidPassword,
        UsernameAlreadyExists,
        NotRight
    };
    typedef struct AccountInfo_
    {
        std::wstring password;
        int score = 0;
        int matchCount = 0;
        int winCount = 0;
    } AccountInfo;

    Account();
    Account(const std::wstring& username, const std::wstring& password);
    virtual ~Account();
    Account(const Account&);
    Account& operator=(const Account&);
    AccountError ValidateRegister() const;
    AccountError ValidateLogin() const;
    std::wstring& get_username();
    std::wstring& get_password();
    void add_account();
protected:
    std::wstring username;
    AccountInfo accountInfo;
};

class Player : public Account
{
public:
    enum class mode
    {
        localpk,
        Aipk,
        lianjipk
    };
    enum class gameresult
    {
        Win,
        Lose,
        Draw,
        Notend,
        Redwin,
        Blackwin
    };
    struct gamerecord
    {
        mode gameMode;
        std::wstring opponentName;
        gameresult result;
        std::wstring time;
        std::wstring move_history;
    };

    Player();
    Player(const Account& account);
    virtual ~Player();
    Player(const Player&);
    Player& operator=(const Player&);
    void save();
    void add_game_record(const bool& is_red_AI, const bool& is_black_AI, int red, int black);//游戏开始(人机或本地）
	void add_game_record(int); //游戏开始(联网)
	std::string add_game_record(const ChessPiece::Camp& current_turn);//联机
    std::string add_game_record(const ChessPiece::Camp& current_turn,int ai_difficulty);//一方获胜
    std::string add_game_record();//中途退出
    std::vector<gamerecord>& get_gamerecords() { return gamerecords; };
private:
    std::vector<gamerecord> gamerecords;
};