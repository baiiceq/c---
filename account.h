#pragma once
#include <string>

class Account
{
public:
	enum class AccountError
	{
		None,
		InvalidUsername,
		InvalidPassword,
		UsernameAlreadyExists,
		NotRight                  //�û��������벻��ȷ
	};
	Account() = default;
	Account(const std::wstring& username, const std::wstring& password)
		: username(username), password(password), score(0) {
	}
	~Account() = default;
	Account(const Account&) = default;
	Account& operator=(const Account&) = default;
	AccountError Validate() const {
		if (username.empty()) return AccountError::InvalidUsername;
		if (password.empty()) return AccountError::InvalidPassword;
		return AccountError::None;
	}
private:
	std::wstring username;
	std::wstring password;
	int score;
};