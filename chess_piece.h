#pragma once

#include "camera.h"
#include <graphics.h>

class ChessPiece
{
public:
	enum class Camp
	{
		Black,
		Red
	};

	enum class PieceType 
	{
		General,  // 将 / 帅
		Advisor,  // 士
		Elephant, // 象 / 相
		Horse,    // 马
		Chariot,  // 车
		Cannon,   // 炮
		Soldier   // 卒 / 兵
	};

public:
	ChessPiece(const Vector2& pos, Camp c);
	~ChessPiece() = default;

	virtual void on_render(const Camera& camera);

	virtual void on_input(const ExMessage& msg);

	virtual void on_update(int delta);

	virtual void can_move_to() = 0;

	void set_pos(const Vector2& p) { pos = p; }

	Vector2 get_pos() const { return pos; }
	Vector2 get_image_pos() const { return image_pos; }
	Vector2 get_size() const { return size; }

	void set_selected(bool s) { is_selected = s; }
	bool get_selected() const { return is_selected; }

	void set_alive(bool s) { is_alive = s; }
	bool get_alive() const { return is_alive; }

	Camp get_camp() const { return camp; }
	PieceType get_type() const { return type; }


protected:
	Vector2 image_pos;       // 图像在界面的位置
	Vector2 pos;             // 棋子在棋盘的位置

	IMAGE img;
	Vector2 size;

	Camp camp;
	PieceType type;

	bool is_selected = false;
	bool is_alive = false;

};