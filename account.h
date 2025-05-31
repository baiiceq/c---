#pragma once
#include <string>
#include <sstream> 
#include <fstream>
#include "resources_manager.h"

class Account
{
public:
	enum class AccountError
	{
		Null,                     //��״̬
		None,
		InvalidUsername,
		InvalidPassword,
		UsernameAlreadyExists,
		NotRight                  //�û��������벻��ȷ
	};
	Account() = default;
	Account(const std::wstring& username, const std::wstring& password)
		: username(username), password(password) {
	}
	~Account() = default;
	Account(const Account&) = default;
	Account& operator=(const Account&) = default;
	AccountError ValidateRegister() const {
		if (username.empty()) return AccountError::InvalidUsername;
		if (password.empty()) return AccountError::InvalidPassword;
		if (ResourcesManager::instance()->get_account_pool().find(username) !=
			ResourcesManager::instance()->get_account_pool().end())
			return AccountError::UsernameAlreadyExists;
		return AccountError::None;
	}
	AccountError ValidateLogin() const
	{
		auto it = ResourcesManager::instance()->get_account_pool().find(username);
		if (it == ResourcesManager::instance()->get_account_pool().end())
			return AccountError::NotRight;
		if (it->second != password)
			return AccountError::NotRight;
		return AccountError::None;
	}
	std::wstring& get_username() { return username; }
	std::wstring& get_password() { return password; }
	void add_account()
	{
		ResourcesManager::instance()->get_account_pool()[username] = password;
	}
private:
	std::wstring username;
	std::wstring password;
	int score;
	int matchCount;
	int winCount;
};

class Player :public Account
{
public:
	enum class mode
	{
		Realbattle,
		Aipk
	};
	enum class gameresult
	{
		Win,//ʤ��
		Lose,//ʧ��
		Draw,//ƽ��
		Notend//�ж�
	};
	struct gamerecord
	{
		mode gameMode; //��Ϸģʽ
		std::wstring opponentName; //��������
		gameresult result; //��Ϸ���
		std::wstring time; //��Ϸʱ��
	};
public:
	Player() = default;
	Player(const Account& account) : Account(account)
	{
		//��ȡ���û�����Ϸ��¼
		std::wstring path = L"data\\game_records\\"+this->get_username() + L".txt";
		std::wifstream file(path);
		if (!file.is_open())
			return;//�ļ�������˵��û��Ϸ��¼
		std::wstring line;
		while (std::getline(file, line))
		{
			gamerecord record;
			std::wistringstream iss(line);
			int modeInt, resultInt;
			iss >> modeInt >> record.opponentName >> resultInt >> record.time;
			record.gameMode = static_cast<mode>(modeInt);
			record.result = static_cast<gameresult>(resultInt);
			gamerecords.push_back(record);
		}
	}
	~Player() = default;
	Player(const Player&) = default;
	Player& operator=(const Player&) = default;
	void save()
	{
		std::wstring path = L"data\\game_records\\"+this->get_username() + L".txt";
		std::wofstream file(path);
		if (!file.is_open())
			return; //�ļ���ʧ��
		for (const auto& record : gamerecords)
		{
			file << static_cast<int>(record.gameMode) << L" "
				<< record.opponentName << L" "
				<< static_cast<int>(record.result) << L" "
				<< record.time << L"\n";
		}
		file.close();
	}
private:
	std::vector<gamerecord> gamerecords; //��Ϸ��¼
};