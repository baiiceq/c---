#include "util.h"
#include "resources_manager.h"
#include <fstream>  
#include <sstream>
#include "account.h"

struct ImageResInfo
{
	std::string id;
	LPCTSTR path;
};

struct AtlasResInfo
{
	std::string id;
	LPCTSTR path;
	int num_frame = 0;
};

static const std::vector<ImageResInfo> image_info_list =
{
	{"button_startgame_1",                _T(R"(resources\ui\button_startgame_1.png)")},
	{"button_startgame_2",                _T(R"(resources\ui\button_startgame_2.png)")},
	{"button_startgame_3",                _T(R"(resources\ui\button_startgame_3.png)")},
	{"button_setting_1",                  _T(R"(resources\ui\button_setting_1.png)")},
	{"button_setting_2",                  _T(R"(resources\ui\button_setting_2.png)")},
	{"button_setting_3",                  _T(R"(resources\ui\button_setting_3.png)")},
	{"button_exit_1",                     _T(R"(resources\ui\button_exit_1.png)")},
	{"button_exit_2",                     _T(R"(resources\ui\button_exit_2.png)")},
	{"button_exit_3",                     _T(R"(resources\ui\button_exit_3.png)")},
	{"button_repentance_1",               _T(R"(resources\ui\button_repentance_1.png)")},
	{"button_repentance_2",               _T(R"(resources\ui\button_repentance_2.png)")},
	{"button_repentance_3",               _T(R"(resources\ui\button_repentance_3.png)")},
	{"button_lianji_1",                   _T(R"(resources\ui\button_lianji_1.png)")},
	{"button_lianji_2",                   _T(R"(resources\ui\button_lianji_2.png)")},
	{"button_lianji_3",                   _T(R"(resources\ui\button_lianji_3.png)")},
	{"button_benji_1",                    _T(R"(resources\ui\button_benji_1.png)")},
	{"button_benji_2",                    _T(R"(resources\ui\button_benji_2.png)")},
	{"button_benji_3",                    _T(R"(resources\ui\button_benji_3.png)")},
	{"button_rightarrow_1",               _T(R"(resources\ui\button_rightarrow_1.png)")},
	{"button_rightarrow_2",               _T(R"(resources\ui\button_rightarrow_2.png)")},
	{"button_rightarrow_3",               _T(R"(resources\ui\button_rightarrow_3.png)")},
	{"button_leftarrow_1",                _T(R"(resources\ui\button_leftarrow_1.png)")},
	{"button_leftarrow_2",                _T(R"(resources\ui\button_leftarrow_2.png)")},
	{"button_leftarrow_3",                _T(R"(resources\ui\button_leftarrow_3.png)")},
	{"button_backmenu_1",                 _T(R"(resources\ui\button_backmenu_1.png)")},
	{"button_backmenu_2",                 _T(R"(resources\ui\button_backmenu_2.png)")},
	{"button_backmenu_3",                 _T(R"(resources\ui\button_backmenu_3.png)")},
	{"button_playback_1",                 _T(R"(resources\ui\button_playback_1.png)")},
	{"button_playback_2",                 _T(R"(resources\ui\button_playback_2.png)")},
	{"button_playback_3",                 _T(R"(resources\ui\button_playback_3.png)")},
	{"button_create_1",                   _T(R"(resources\ui\button_create_1.png)")},
	{"button_create_2",                   _T(R"(resources\ui\button_create_2.png)")},
	{"button_create_3",                   _T(R"(resources\ui\button_create_3.png)")},
	{"button_enter_1",                    _T(R"(resources\ui\button_enter_1.png)")},
	{"button_enter_2",                    _T(R"(resources\ui\button_enter_2.png)")},
	{"button_enter_3",                    _T(R"(resources\ui\button_enter_3.png)")},
	{"button_load_1",                     _T(R"(resources\ui\button_load_1.png)")},
	{"button_load_2",                     _T(R"(resources\ui\button_load_2.png)")},
	{"button_load_3",                     _T(R"(resources\ui\button_load_3.png)")},
	{"button_once_login_1",               _T(R"(resources\ui\button_once_login_1.png)")},
	{"button_once_login_2",               _T(R"(resources\ui\button_once_login_2.png)")},
	{"button_once_login_3",               _T(R"(resources\ui\button_once_login_3.png)")},
	{"button_account_login_1",            _T(R"(resources\ui\button_account_login_1.png)")},
	{"button_account_login_2",            _T(R"(resources\ui\button_account_login_2.png)")},
	{"button_account_login_3",            _T(R"(resources\ui\button_account_login_3.png)")},
	{"button_register_1",                 _T(R"(resources\ui\button_register_1.png)")},
	{"button_register_2",                 _T(R"(resources\ui\button_register_2.png)")},
	{"button_register_3",                 _T(R"(resources\ui\button_register_3.png)")},
	{"button_confirm_1",                  _T(R"(resources\ui\button_confirm_1.png)")},
	{"button_confirm_2",                  _T(R"(resources\ui\button_confirm_2.png)")},
	{"button_confirm_3",                  _T(R"(resources\ui\button_confirm_3.png)")},
	{"button_exitaccount_1",              _T(R"(resources\ui\button_exitaccount_1.png)")},
	{"button_exitaccount_2",              _T(R"(resources\ui\button_exitaccount_2.png)")},
	{"button_exitaccount_3",              _T(R"(resources\ui\button_exitaccount_3.png)")},
	{"button_myinfo_1",                   _T(R"(resources\ui\button_myinfo_1.png)")},
	{"button_myinfo_2",                   _T(R"(resources\ui\button_myinfo_2.png)")},
	{"button_myinfo_3",                   _T(R"(resources\ui\button_myinfo_3.png)")},
	{"button_ranklist_1",               _T(R"(resources\ui\button_ranklist_1.png)")},
	{"button_ranklist_2",                 _T(R"(resources\ui\button_ranklist_2.png)")},
	{"button_ranklist_3",                 _T(R"(resources\ui\button_ranklist_3.png)")},
	{"button_huifang_1",                  _T(R"(resources\ui\button_huifang_1.png)")},
	{"button_huifang_2",                  _T(R"(resources\ui\button_huifang_2.png)")},
	{"button_huifang_3",                  _T(R"(resources\ui\button_huifang_3.png)")},
	{"board",                             _T(R"(resources\board.png)")},
	{"advisor_black",                     _T(R"(resources\advisor_black.png)")},
	{"advisor_red",                       _T(R"(resources\advisor_red.png)")},
	{"general_black",                     _T(R"(resources\general_black.png)")},
	{"general_red",                       _T(R"(resources\general_red.png)")},
	{"soldier_black",                     _T(R"(resources\soldier_black.png)")},
	{"soldier_red",                       _T(R"(resources\soldier_red.png)")},
	{"chariot_black",                     _T(R"(resources\chariot_black.png)")},
	{"chariot_red",                       _T(R"(resources\chariot_red.png)")},
	{"horse_black",                       _T(R"(resources\horse_black.png)")},
	{"horse_red",                         _T(R"(resources\horse_red.png)")},
	{"cannon_black",                      _T(R"(resources\cannon_black.png)")},
	{"cannon_red",                        _T(R"(resources\cannon_red.png)")},
	{"elephant_black",                    _T(R"(resources\elephant_black.png)")},
	{"elephant_red",                      _T(R"(resources\elephant_red.png)")},
	{"select_box_1",                      _T(R"(resources\select_box_1.png)")},
	{"select_box_2",                      _T(R"(resources\select_box_2.png)")},
	{"select_box_3",                      _T(R"(resources\select_box_3.png)")},
	{"select_box_4",                      _T(R"(resources\select_box_4.png)")},
	{"background",                        _T(R"(resources\background.png)")},
	{"title",                             _T(R"(resources\title.png)")},
	{"red_tip",                           _T(R"(resources\red_tip.png)")},
	{"black_tip",                         _T(R"(resources\black_tip.png)")},
	{"red_tip1",                          _T(R"(resources\red_tip(1).png)")},
	{"black_tip1",                        _T(R"(resources\black_tip(1).png)")},
	{"pause_background",                  _T(R"(resources\pause_background.png)")},
	{"pause_mask",                        _T(R"(resources\pause_mask.png)")},
	{"check",                             _T(R"(resources\check.png)")},
	{"cursor",                            _T(R"(resources\cursor.png)")},
	{"account",                           _T(R"(resources\account.png)")},
	{"password",                          _T(R"(resources\password.png)")},
	{ "ai_thinking",                      _T(R"(resources\ai_thinking.png)") },
	{"notright",						  _T(R"(resources\notright.png)")},
	{"loginsuccess",					  _T(R"(resources\loginsuccess.png)")},
	{"registersuccess",				      _T(R"(resources\registersuccess.png)")},
	{"usernameexist",					  _T(R"(resources\usernameexist.png)")},
	{"invalidusername",				      _T(R"(resources\invalidusername.png)")},
	{"invalidpassword",				      _T(R"(resources\invalidpassword.png)")},
	{"newusername",					      _T(R"(resources\newusername.png)")},
	{"newpassword",						  _T(R"(resources\newpassword.png)")},
	{"login",							  _T(R"(resources\login.png)")},
	{"register",						  _T(R"(resources\register.png)")},
	{"waiting_players",                   _T(R"(resources\waiting_player.png)") },
	{"waiting_move",                      _T(R"(resources\waiting_move.png)")},
	{"ranklist_bg",                       _T(R"(resources\ranklist_bg.png)")}
};

static inline bool check_image_valid(IMAGE* image)
{
	return GetImageBuffer(image);
}

void ResourcesManager::load()
{
	AddFontResourceEx(_T("resources/font.ttf"), FR_PRIVATE, NULL);

	for (const auto& info : image_info_list)
	{
		IMAGE* image = new IMAGE();
		loadimage(image, info.path);
		if (!check_image_valid(image))
			throw info.path;
		image_pool[info.id] = image;
	}


	load_audio(_T(R"(resources\music\ui_confirm.wav)"), _T("ui_confirm"));
	load_audio(_T(R"(resources\music\piece_move.wav)"), _T("move"));
	load_audio(_T(R"(resources\music\piece_eat.wav)"), _T("eat"));

	load_account(_T("data\\account.txt"));
}

ResourcesManager* ResourcesManager::manager = nullptr;

ResourcesManager* ResourcesManager::instance()
{
	if (!manager)
		manager = new ResourcesManager();

	return manager;
}

ResourcesManager::ResourcesManager()
{
	main_camera = new Camera();
}

ResourcesManager::~ResourcesManager()
{
	delete main_camera;
}


Atlas* ResourcesManager::find_atlas(const std::string& id) const
{
	const auto& itor = atlas_pool.find(id);
	if (itor == atlas_pool.end())
		return nullptr;
	
	return itor->second;
}

IMAGE* ResourcesManager::find_image(const std::string& id) const
{
	const auto& itor = image_pool.find(id);
	if (itor == image_pool.end())
		return nullptr;

	return itor->second;
}

void ResourcesManager::flip_image(IMAGE* src_image, IMAGE* dst_image, int num_h)
{
	int w = src_image->getwidth();
	int h = src_image->getheight();
	int w_frame = w / num_h;
	Resize(dst_image, w, h);
	DWORD* src_buffer = GetImageBuffer(src_image);
	DWORD* dst_buffer = GetImageBuffer(dst_image);
	for (int i = 0; i < num_h; i++)
	{
		int x_left = i * w_frame;
		int x_right = (i + 1) * w_frame;
		for (int y = 0; y < h; y++)
		{
			for (int x = x_left; x < x_right; x++)
			{
				int idx_src = y * w + x;
				int idx_dst = y * w + x_right - (x - x_left);
				dst_buffer[idx_dst] = src_buffer[idx_src];
			}
		}
	}
	
}

void ResourcesManager::flip_image(const std::string& src_id, const std::string dst_id, int num_h)
{
	IMAGE* src_image = image_pool[src_id];
	IMAGE* dst_image = new IMAGE();

	flip_image(src_image, dst_image, num_h);

	image_pool[dst_id] = dst_image;
}

void ResourcesManager::flip_atlas(const std::string& src_id, const std::string dst_id)
{
	Atlas* src_atlas = atlas_pool[src_id];
	Atlas* dst_atlas = new Atlas();

	for (int i = 0; i < src_atlas->get_size(); i++)
	{
		IMAGE img_flipped;
		flip_image(src_atlas->get_image(i), &img_flipped);
		dst_atlas->add_image(img_flipped);
	}

	atlas_pool[dst_id] = dst_atlas;
}

 

void ResourcesManager::load_account(const std::wstring& path)  
{  
	std::wifstream file(path);
	if (!file.is_open()) return;
	std::wstring line;
	while (std::getline(file, line)) {
		std::wistringstream iss(line);
		std::wstring username, password;
		int score = 0, matchCount = 0, winCount = 0;
		if (iss >> username >> password >> score >> matchCount >> winCount) {
			Account::AccountInfo info;
			info.password = password;
			info.score = score;
			info.matchCount = matchCount;
			info.winCount = winCount;
			account_pool[username] = info;
		}
	}
	file.close();
}
void ResourcesManager::save_account(const std::wstring& path)const
{
	std::wofstream file(path);
	if (!file.is_open()) return;
	for (const auto& account : account_pool) {
		file << account.first << L" "
			<< account.second.password << L" "
			<< account.second.score << L" "
			<< account.second.matchCount << L" "
			<< account.second.winCount << std::endl;
	}
	file.close();
}
