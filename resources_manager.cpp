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
	{"button_startgame_1",                _T(R"(resources\ui\button_startgame_1.png)")},
	{"button_startgame_2",                _T(R"(resources\ui\button_startgame_2.png)")},
	{"button_startgame_3",                _T(R"(resources\ui\button_startgame_3.png)")},
	{"button_setting_1",                  _T(R"(resources\ui\button_setting_1.png)")},
	{"button_setting_2",                  _T(R"(resources\ui\button_setting_2.png)")},
	{"button_setting_3",                  _T(R"(resources\ui\button_setting_3.png)")},
	{"button_exit_1",                     _T(R"(resources\ui\button_exit_1.png)")},
	{"button_exit_2",                     _T(R"(resources\ui\button_exit_2.png)")},
	{"button_exit_3",                     _T(R"(resources\ui\button_exit_3.png)")},
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
};

static const std::vector<AtlasResInfo> atlas_info_list =
{
	

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
