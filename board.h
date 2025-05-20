#pragma once

#include "camera.h"
#include <graphics.h>

// ¿É¸ü»»ÎªStaticImage
class Board
{
public:
	Board(Vector2 position);
	Board();
	~Board();

	void on_render(const Camera& camera);

	void on_input(const ExMessage& msg);

	void on_update(int delta);

	void set_pos(int x, int y)
	{
		position.x = x;
		position.y = y;
	}

	Vector2 get_size() const
	{
		return size;
	}

private:
	Vector2 position;
	Vector2 size;

	IMAGE img;
};

