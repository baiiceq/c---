#include "util.h"
#include "resources_manager.h"

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
	{"background",               _T(R"(resource\background.png)")},
};

static const std::vector<AtlasResInfo> atlas_info_list =
{


	{"wsd_idle_right",            _T(R"(resource\wsd\idle\%d.png)"),              3},
	{"wsd_run_right",             _T(R"(resource\wsd\run\%d.png)"),               6},
	{"wsd_jump_right",            _T(R"(resource\wsd\jump\%d.png)"),              3},
	{"wsd_fall_right",            _T(R"(resource\wsd\fall\%d.png)"),              4}
	

};

static inline bool check_image_valid(IMAGE* image)
{
	return GetImageBuffer(image);
}

void ResourcesManager::load()
{
	for (const auto& info : image_info_list)
	{
		IMAGE* image = new IMAGE();
		loadimage(image, info.path);
		if (!check_image_valid(image))
			throw info.path;
		image_pool[info.id] = image;
	}

	for (const auto& info : atlas_info_list)
	{
		Atlas* atlas = new Atlas();
		atlas->load_from_file(info.path, info.num_frame);
		for (int i = 0; i < atlas->get_size(); i++)
		{
			IMAGE* image = atlas->get_image(i);
			if (!check_image_valid(image))
				throw info.path;
		}
		atlas_pool[info.id] = atlas;
	}
	flip_atlas("wsd_idle_right", "wsd_idle_left");
	flip_atlas("wsd_run_right", "wsd_run_left");
	flip_atlas("wsd_jump_right", "wsd_jump_left");
	flip_atlas("wsd_fall_right", "wsd_fall_left");


	load_audio(_T(R"(resources\audio\bgm.mp3)"), _T("bgm"));
	load_audio(_T(R"(resources\audio\barb_break.mp3)"), _T("barb_break"));
	load_audio(_T(R"(resources\audio\bullet_time.mp3)"), _T("bullet_time"));

	load_audio(_T(R"(resources\audio\enemy_dash.mp3)"), _T("enemy_dash"));
	load_audio(_T(R"(resources\audio\enemy_run.mp3)"), _T("enemy_run"));
	load_audio(_T(R"(resources\audio\enemy_hurt_1.mp3)"), _T("enemy_hurt_1"));
	load_audio(_T(R"(resources\audio\enemy_hurt_2.mp3)"), _T("enemy_hurt_2"));
	load_audio(_T(R"(resources\audio\enemy_hurt_3.mp3)"), _T("enemy_hurt_3"));
	load_audio(_T(R"(resources\audio\enemy_throw_barbs.mp3)"), _T("enemy_throw_barbs"));
	load_audio(_T(R"(resources\audio\enemy_throw_silk.mp3)"), _T("enemy_throw_silk"));
	load_audio(_T(R"(resources\audio\enemy_throw_sword.mp3)"), _T("enemy_throw_sword"));

	load_audio(_T(R"(resources\audio\player_attack_1.mp3)"), _T("player_attack_1"));
	load_audio(_T(R"(resources\audio\player_attack_2.mp3)"), _T("player_attack_2"));
	load_audio(_T(R"(resources\audio\player_attack_3.mp3)"), _T("player_attack_3"));
	load_audio(_T(R"(resources\audio\player_dead.mp3)"), _T("player_dead"));
	load_audio(_T(R"(resources\audio\player_hurt.mp3)"), _T("player_hurt"));
	load_audio(_T(R"(resources\audio\player_jump.mp3)"), _T("player_jump"));
	load_audio(_T(R"(resources\audio\player_jump.mp3)"), _T("player_jump"));
	load_audio(_T(R"(resources\audio\player_roll.mp3)"), _T("player_roll"));
	load_audio(_T(R"(resources\audio\player_run.mp3)"), _T("player_run"));
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
