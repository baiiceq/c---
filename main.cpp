#include <graphics.h>

#include "util.h"
#include "atlas.h"
#include "wsd.h"
#include "collision_manager.h"
#include "resources_manager.h"
#include "character_manager.h"

#pragma comment(lib, "Winmm.lib")

bool is_debug = false;

IMAGE img_background;

Atlas atlas_wsd_left;
Atlas atlas_wsd_right;

IMAGE img_platform_large;

Camera main_camera;

static void draw_background()
{
	static IMAGE* img_background = ResourcesManager::instance()->find_image("background");
	static Rect rect_dst =
	{
		(getwidth() - img_background->getwidth()) / 2,
		(getheight() - img_background->getheight()) / 2,
		img_background->getwidth(),
		img_background->getheight()
	};
	putimage_alpha(ResourcesManager::instance()->get_camera(), img_background, &rect_dst);
}


void flip_atlas(Atlas& src, Atlas& dst)
{
	dst.clear();
	for (int i = 0; i < src.get_size(); i++)
	{
		IMAGE img_flppied;
		flip_image(src.get_image(i), &img_flppied);
		dst.add_image(img_flppied);
	}
}

int main()
{
	HWND hwnd = initgraph(1280, 720, EW_SHOWCONSOLE);
	SetWindowText(hwnd, _T("小日本为是对"));

	try
	{
		ResourcesManager::instance()->load();
	}
	catch (const LPCTSTR id)
	{
		TCHAR err_msg[512];
		_stprintf_s(err_msg, _T("无法加载：%s"), id);
		MessageBox(hwnd, err_msg, _T("资源加载失败"), MB_OK | MB_ICONERROR);
		return -1;
	}

	ExMessage msg;
	const int FPS = 60;


	bool running = true;

	initgraph(1280, 720);

	settextstyle(28, 0, _T("IPix"));
	setbkmode(TRANSPARENT);

	BeginBatchDraw();

	while (running)
	{
		DWORD frame_start_time = GetTickCount();

		while (peekmessage(&msg))
		{
			CharacterManager::instance()->on_input(msg);
		}

		static DWORD last_tick_time = GetTickCount();
		DWORD current_tick_time = GetTickCount();
		DWORD delta_tick = current_tick_time - last_tick_time;
		last_tick_time = current_tick_time;
		
		CharacterManager::instance()->on_update(delta_tick);
		CollisionManager::instance()->process_collide();

		setbkcolor(RGB(0, 0, 0));
		cleardevice();

		draw_background();
		CharacterManager::instance()->on_render(ResourcesManager::instance()->get_camera());

		FlushBatchDraw();

		DWORD frame_end_time = GetTickCount();
		DWORD frame_delta_time = frame_end_time - frame_start_time;
		if (frame_delta_time < 1000 / FPS)
			Sleep(1000 / FPS - frame_delta_time);
	}
	EndBatchDraw();

	return 0;
}
