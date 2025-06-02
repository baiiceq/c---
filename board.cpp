#include "board.h"
#include "resources_manager.h"
#include "util.h"

#include <iostream>

Board::Board()
{
	img = *ResourcesManager::instance()->find_image("board");

	this->position = { 0,0 };
	size = { (float)img.getwidth(), (float)img.getheight() };
}

Board::Board(Vector2 position)
{
	img = *ResourcesManager::instance()->find_image("board");
	
	this->position = position;
	size = { (float)img.getwidth(), (float)img.getheight() };
}

Board::~Board()
{
}

void Board::on_render(const Camera& camera)
{
	Rect rect_dst = { (int)position.x, (int)position.y, (int)size.x, (int)size.y};
	
	putimage_alpha(&camera, &img, &rect_dst);
}

void Board::on_input(const ExMessage& msg)
{
}

void Board::on_update(int delta)
{
}
