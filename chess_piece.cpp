#include "chess_piece.h"
#include "util.h"

ChessPiece::ChessPiece(const Vector2& pos, Camp c)
{
	size = { 60,60 };
	is_alive = true;
	this->pos = pos;
	camp = c;

	Vector2 board_pos = { 130, 20 };
	image_pos.x = board_pos.x + 30 + pos.x * 60 - size.x / 2;
	image_pos.y = board_pos.y + 30 + pos.y * 60 - size.y / 2;
}

void ChessPiece::on_render(const Camera& camera)
{
	Rect rect_dst = { image_pos.x, image_pos.y, size.x, size.y };
	putimage_alpha(&camera, &img, &rect_dst);
}

void ChessPiece::on_input(const ExMessage& msg)
{
}

void ChessPiece::on_update(int delta)
{
	Vector2 board_pos = { 130, 20 };
	Vector2 target_image_pos;
	target_image_pos.x = board_pos.x + 30 + pos.x * 60 - size.x / 2;
	target_image_pos.y = board_pos.y + 30 + pos.y * 60 - size.y / 2;

	if (!(target_image_pos == image_pos))
	{
		Vector2 delta_vec = target_image_pos - image_pos;

		// 计算本帧最大能移动的距离
		float distance = delta * SPEED / 1000.0f;

		// 若距离足够小
		if (delta_vec.length() <= distance)
		{
			image_pos = target_image_pos;
		}
		else
		{
			Vector2 direction = delta_vec.normalize();
			image_pos = image_pos + direction * distance;
		}
	}
}
