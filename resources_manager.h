#pragma once

#include "atlas.h"
#include "camera.h"
#include "account.h"

#include <string>
#include <graphics.h>
#include <unordered_map>

class ResourcesManager
{
public:
	static ResourcesManager* instance();

	void load();

	Atlas* find_atlas(const std::string& id) const;
	IMAGE* find_image(const std::string& id) const;

	Camera* get_camera() const
	{
		return main_camera;
	}
	std::unordered_map<std::wstring, Account::AccountInfo>& get_account_pool()
	{
		return account_pool;
	}
	void load_account(const std::wstring& path);
	void save_account(const std::wstring& path) const;

	int& get_volume()
	{
		return volume;
	}
private:
	static ResourcesManager* manager;

	std::unordered_map<std::string, Atlas*> atlas_pool;
	std::unordered_map<std::string, IMAGE*> image_pool;
	std::unordered_map<std::wstring,Account::AccountInfo> account_pool;
	int volume = 80; 

	Camera* main_camera;

private:
	ResourcesManager();
	~ResourcesManager();

	void flip_image(IMAGE* src_image, IMAGE* dst_image, int num_h = 1);
	void flip_image(const std::string& src_id, const std::string dst_id, int num_h = 1);
	void flip_atlas(const std::string& src_id, const std::string dst_id);

};