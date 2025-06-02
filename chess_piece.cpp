#include "chess_piece.h"
#include "util.h"

ChessPiece::ChessPiece(const Vector2& pos, Camp c)
{
	size = { 60,60 };
	is_alive = true;
	this->pos = pos;
	camp = c;

	Vector2 board_pos = { 260, 20 };
	image_pos.x = board_pos.x + 30 + pos.x * 60 - size.x / 2;
	image_pos.y = board_pos.y + 30 + pos.y * 60 - size.y / 2;

	timer_move.set_one_shot(true);
	timer_move.set_wait_time(MOVE_TIME);
	timer_move.set_on_timeout([&]()
		{
			is_moving = false;
			image_pos.x = 260 + this->pos.x * 60;
			image_pos.y = 20 + this->pos.y * 60;
			if(callback_operate)
				callback_operate();
		});

}

void ChessPiece::on_render(const Camera& camera)
{
	Rect rect_dst = { (int)image_pos.x, (int)image_pos.y, (int)size.x, (int)size.y };
	putimage_alpha(&camera, &img, &rect_dst);
}

void ChessPiece::on_input(const ExMessage& msg)
{
}

void ChessPiece::on_update(int delta)
{
	if (is_moving)
	{
		timer_move.on_update(delta);

		Vector2 board_pos = { 260, 20 };
		Vector2 target_image_pos;
		target_image_pos.x = board_pos.x + 30 + pos.x * 60 - size.x / 2;
		target_image_pos.y = board_pos.y + 30 + pos.y * 60 - size.y / 2;

		if (!(target_image_pos == image_pos))
		{
			float t = timer_move.get_ratio();
			image_pos = image_pos + (target_image_pos - image_pos) * t;
		}
	}
}
