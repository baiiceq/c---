#pragma once

#include "camera.h"

#include <vector>
#include <graphics.h>

class ChessPiece
{
public:
	// 棋子的阵营——红\黑\无
	enum class Camp 
	{
		Black,
		Red,
		None = -1
	};

	// 棋子的种类
	enum class PieceType 
	{
		General = 1,  // 将 / 帅
		Advisor,      // 士
		Elephant,     // 象 / 相
		Horse,        // 马
		Chariot,      // 车
		Cannon,       // 炮
		Soldier       // 卒 / 兵
	};

public:
	ChessPiece(const Vector2& pos, Camp c);
	~ChessPiece() = default;

	virtual void on_render(const Camera& camera);

	virtual void on_input(const ExMessage& msg);

	virtual void on_update(int delta);

	// 获取该棋子可以到达的位置
	virtual std::vector<Vector2> get_can_move_to(const int(&board)[9][10]) = 0;
	// 获取该棋子可以吃掉的棋子的位置
	virtual std::vector<Vector2> get_can_eat(const int(&board)[9][10]) = 0;

 	// 设置位置
	void set_pos(const Vector2& p) { pos = p; }
	void set_image_pos(const Vector2& p) { image_pos = p; }

	// 获取位置和大小
	Vector2 get_pos() const { return pos; }
	Vector2 get_image_pos() const { return image_pos; }
	Vector2 get_size() const { return size; }

	// 设置和获取是否被选择（没什么用）
	void set_selected(bool s) { is_selected = s; }
	bool get_selected() const { return is_selected; }

	// 设置和获取该棋子是否被吃掉
	void set_alive(bool s) { is_alive = s; }
	bool get_alive() const { return is_alive; }

	// 获取棋子的阵营和种类
	Camp get_camp() const { return camp; }
	PieceType get_type() const { return type; }

	// 将棋子设置为运动状态
	void set_moving(bool s)
	{
		is_moving = s;
		if (s == true)
		{
			timer_move.restart();
		}
	}

	// 设置棋子运动完成后的回调函数
	void set_callback_operate(std::function<void()> callback)
	{
		callback_operate = callback;
	}


protected:
	Vector2 image_pos;       // 图像在界面的位置
	Vector2 pos;             // 棋子在棋盘的位置

	IMAGE img;               // 棋子的图像
	Vector2 size;            // 图像的大小

	Camp camp;               // 棋子阵营
	PieceType type;          // 棋子的种类

	bool is_selected = false;  // 是否被选择（目前无用）
	bool is_alive = false;     // 是否活着

	const int MOVE_TIME = 500; // 每次运动的时间

	bool is_moving = false;    // 是否在运动
	Timer timer_move;          // 运动的计时器

	std::function<void()> callback_operate;    // 当棋子完成移动时，通知上层棋子管理器
};

class SChessPiece
{
protected:
	ChessPiece::Camp camp;// 棋子的阵营
	Vector2 pos; // 棋子在棋盘上的位置
	ChessPiece::PieceType type; // 棋子的种类
public:
	SChessPiece(const Vector2& p,ChessPiece::Camp c) : camp(c), pos(p) {}
	~SChessPiece() = default;
	virtual std::vector<Vector2> get_can_move_to(const int(&board)[9][10]) = 0;
	virtual std::vector<Vector2> get_can_eat(const int(&board)[9][10]) = 0;
	ChessPiece::PieceType get_type() const { return type; }
	Vector2 get_pos() const { return pos; }
};