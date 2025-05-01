#include <graphics.h>

#include "util.h"
#include "atlas.h"
#include "scene.h"
#include "menu_scene.h"
#include "game_scene.h"
#include "scene_manager.h"

#pragma comment(lib, "Winmm.lib")

int main()
{
	HWND hwnd = initgraph(800, 640, EW_SHOWCONSOLE);
	SetWindowText(hwnd, _T("Hollow Katana"));

	try
	{
		ResourcesManager::instance()->load();
	}
	catch (const LPCTSTR id)
	{
		TCHAR err_msg[512];
		_stprintf_s(err_msg, _T("�޷����أ�%s"), id);
		MessageBox(hwnd, err_msg, _T("��Դ����ʧ��"), MB_OK | MB_ICONERROR);
		return -1;
	}

	ExMessage msg;
	const int FPS = 60;

	bool running = true;

	initgraph(800, 640);

	BeginBatchDraw();
	
	SceneManager* scene_manager = SceneManager::instance();

	while (running)
	{
		DWORD frame_start_time = GetTickCount();

		while (peekmessage(&msg))
		{
			scene_manager->on_input(msg);
		}

		static DWORD last_tick_time = GetTickCount();
		DWORD current_tick_time = GetTickCount();
		DWORD delta_tick = current_tick_time - last_tick_time;
		scene_manager->on_update(delta_tick);
		last_tick_time = current_tick_time;

		cleardevice();
		scene_manager->on_render(*ResourcesManager::instance()->get_camera());

		FlushBatchDraw();

		DWORD frame_end_time = GetTickCount();
		DWORD frame_delta_time = frame_end_time - frame_start_time;
		if (frame_delta_time < 1000 / FPS)
			Sleep(1000 / FPS - frame_delta_time);
	}
	EndBatchDraw();

	return 0;
}
