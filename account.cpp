#include "account.h"
#include "resources_manager.h"
#include <sstream>
#include <fstream>
#include <locale>
#include <codecvt>

Account::Account() = default;

Account::Account(const std::wstring& username, const std::wstring& password)
    : username(username)
{
    accountInfo.password = password;
    accountInfo.matchCount = 0;
    accountInfo.winCount = 0;
    accountInfo.score = 0;
}

Account::~Account() = default;
Account::Account(const Account&) = default;
Account& Account::operator=(const Account&) = default;

Account::AccountError Account::ValidateRegister() const
{
    if (username.empty()) return AccountError::InvalidUsername;
    if (accountInfo.password.empty()) return AccountError::InvalidPassword;
    if (ResourcesManager::instance()->get_account_pool().find(username) !=
        ResourcesManager::instance()->get_account_pool().end())
        return AccountError::UsernameAlreadyExists;
    return AccountError::None;
}

Account::AccountError Account::ValidateLogin() const
{
    auto it = ResourcesManager::instance()->get_account_pool().find(username);
    if (it == ResourcesManager::instance()->get_account_pool().end())
        return AccountError::NotRight;
    if (it->second.password != accountInfo.password)
        return AccountError::NotRight;
    return AccountError::None;
}

std::wstring& Account::get_username() { return username; }
std::wstring& Account::get_password() { return accountInfo.password; }

void Account::add_account()
{
    ResourcesManager::instance()->get_account_pool()[username] = accountInfo;
}

Player::Player() = default;

Player::Player(const Account& account) : Account(account)
{
    std::wstring path = L"data\\game_records\\" + this->get_username() + L".txt";
    std::wifstream file(path, std::ios::binary);
    if (!file.is_open())
        return;

    file.imbue(std::locale(file.getloc(),
        new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>));

    wchar_t bom = 0;
    file.read(&bom, 1);

    std::wstring line;
    while (std::getline(file, line))
    {
        if (line.empty()) continue;
        std::wistringstream iss(line);
        int modeInt, resultInt;
        gamerecord record;
        iss >> modeInt >> record.opponentName >> resultInt >> record.time >> record.move_history;
        record.gameMode = static_cast<mode>(modeInt);
        record.result = static_cast<gameresult>(resultInt);
        gamerecords.push_back(record);
    }
    file.close();
}

Player::~Player() = default;
Player::Player(const Player&) = default;
Player& Player::operator=(const Player&) = default;

void Player::save()
{
    std::wstring path = L"data\\game_records\\" + this->get_username() + L".txt";
    std::wofstream file(path, std::ios::binary);
    if (!file.is_open())
        return;

    file.imbue(std::locale(file.getloc(),
        new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>));

    wchar_t bom = 0xFEFF;
    file.write(&bom, 1);

    for (const auto& record : gamerecords)
    {
        file << static_cast<int>(record.gameMode) << L" "
            << record.opponentName << L" "
            << static_cast<int>(record.result) << L" "
            << record.time << L" "
            << record.move_history << L"\n";
    }
    file.close();
}

void Player::add_game_record(const bool& is_red_AI, const bool& is_black_AI, int red, int black)
{
    gamerecord record;
    if (is_red_AI) {
        record.gameMode = mode::Aipk;
        record.opponentName = L"(ºì)AI";
        switch (red)
        {
        case 1:record.opponentName += L"¼òµ¥"; break;
        case 2:record.opponentName += L"ÆÕÍ¨"; break;
        case 3:record.opponentName += L"À§ÄÑ"; break;
        }
        ResourcesManager::instance()->get_account_pool()[username].matchCount++;
    }
    else if (is_black_AI) {
        record.gameMode = mode::Aipk;
        record.opponentName = L"(ºÚ)AI";
        switch (black)
        {
        case 2:record.opponentName += L"¼òµ¥"; break;
        case 4:record.opponentName += L"ÆÕÍ¨"; break;
        case 6:record.opponentName += L"À§ÄÑ"; break;
        }
		ResourcesManager::instance()->get_account_pool()[username].matchCount++;
    }
    else {
        record.gameMode = mode::localpk;
        record.opponentName = L"-";
		ResourcesManager::instance()->get_account_pool()[username].matchCount++;
        ResourcesManager::instance()->get_account_pool()[username].score += 3;
    }
    record.time = get_current_time();
    record.result = gameresult::Notend;
    record.move_history = L"-";
    gamerecords.push_back(record);
}

std::string Player::add_game_record(const ChessPiece::Camp& current_turn,int ai_difficulty)
{
    gamerecord& record = gamerecords.back();
    ChessPiece::Camp opponent_turn;
    if (record.opponentName[1] == L'ºì')
        opponent_turn = ChessPiece::Camp::Red;
	else if (record.opponentName[1] == L'ºÚ')
        opponent_turn = ChessPiece::Camp::Black;
    if (record.gameMode == mode::Aipk)
    {
        if (current_turn == opponent_turn) {
            record.result = gameresult::Lose;
            ResourcesManager::instance()->get_account_pool()[username].score++;
        }
        else {
            record.result = gameresult::Win;
			ResourcesManager::instance()->get_account_pool()[username].score += ai_difficulty * 2;
			ResourcesManager::instance()->get_account_pool()[username].winCount++;
        }
    }
    else if (record.gameMode == mode::localpk)
    {
        if (current_turn == ChessPiece::Camp::Red)
            record.result = gameresult::Redwin;
        else if (current_turn == ChessPiece::Camp::Black)
            record.result = gameresult::Blackwin;
        else
            record.result = gameresult::Draw;
    }
    record.move_history = get_current_time();
    std::string a = std::string(record.move_history.begin(), record.move_history.end());
    a = "data\\move_history\\" + a + ".txt";
    return a;
}

std::string Player::add_game_record()
{
    gamerecord& record = gamerecords.back();
    record.move_history = get_current_time();
    std::string a = std::string(record.move_history.begin(), record.move_history.end());
    a = "data\\move_history\\" + a + ".txt";
    return a;
}