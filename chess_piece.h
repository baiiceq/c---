#pragma once

#include "camera.h"

#include <vector>
#include <graphics.h>

class ChessPiece
{
public:
	// ���ӵ���Ӫ������\��\��
	enum class Camp 
	{
		Black,
		Red,
		None = -1
	};

	// ���ӵ�����
	enum class PieceType 
	{
		General = 1,  // �� / ˧
		Advisor,      // ʿ
		Elephant,     // �� / ��
		Horse,        // ��
		Chariot,      // ��
		Cannon,       // ��
		Soldier       // �� / ��
	};

public:
	ChessPiece(const Vector2& pos, Camp c);
	~ChessPiece() = default;

	virtual void on_render(const Camera& camera);

	virtual void on_input(const ExMessage& msg);

	virtual void on_update(int delta);

	// ��ȡ�����ӿ��Ե����λ��
	virtual std::vector<Vector2> get_can_move_to(const int(&board)[9][10]) = 0;
	// ��ȡ�����ӿ��ԳԵ������ӵ�λ��
	virtual std::vector<Vector2> get_can_eat(const int(&board)[9][10]) = 0;

 	// ����λ��
	void set_pos(const Vector2& p) { pos = p; }
	void set_image_pos(const Vector2& p) { image_pos = p; }

	// ��ȡλ�úʹ�С
	Vector2 get_pos() const { return pos; }
	Vector2 get_image_pos() const { return image_pos; }
	Vector2 get_size() const { return size; }

	// ���úͻ�ȡ�Ƿ�ѡ��ûʲô�ã�
	void set_selected(bool s) { is_selected = s; }
	bool get_selected() const { return is_selected; }

	// ���úͻ�ȡ�������Ƿ񱻳Ե�
	void set_alive(bool s) { is_alive = s; }
	bool get_alive() const { return is_alive; }

	// ��ȡ���ӵ���Ӫ������
	Camp get_camp() const { return camp; }
	PieceType get_type() const { return type; }

	// ����������Ϊ�˶�״̬
	// 0 - false 1 - true 2 - ֱ���ƶ���ָ��λ�� 
	void set_moving(int mode)
	{
		switch (mode)
		{
		case 0:
			is_moving = false;
			break;
		case 1:
			is_moving = true;
			timer_move.restart();
			break;
		case 2:
		{
			is_moving = false;
			Vector2 board_pos = { 260, 20 };
			image_pos.x = board_pos.x + 30 + pos.x * 60 - size.x / 2;
			image_pos.y = board_pos.y + 30 + pos.y * 60 - size.y / 2;
		}
			break;
		}
	}

	// ���������˶���ɺ�Ļص�����
	void set_callback_operate(std::function<void()> callback)
	{
		callback_operate = callback;
	}


protected:
	Vector2 image_pos;       // ͼ���ڽ����λ��
	Vector2 pos;             // ���������̵�λ��

	IMAGE img;               // ���ӵ�ͼ��
	Vector2 size;            // ͼ��Ĵ�С

	Camp camp;               // ������Ӫ
	PieceType type;          // ���ӵ�����

	bool is_selected = false;  // �Ƿ�ѡ��Ŀǰ���ã�
	bool is_alive = false;     // �Ƿ����

	const int MOVE_TIME = 500; // ÿ���˶���ʱ��

	bool is_moving = false;    // �Ƿ����˶�
	Timer timer_move;          // �˶��ļ�ʱ��

	std::function<void()> callback_operate;    // ����������ƶ�ʱ��֪ͨ�ϲ����ӹ�����
};

class SChessPiece
{
protected:
	ChessPiece::Camp camp;// ���ӵ���Ӫ
	Vector2 pos; // �����������ϵ�λ��
	ChessPiece::PieceType type; // ���ӵ�����
public:
	SChessPiece(const Vector2& p,ChessPiece::Camp c) : camp(c), pos(p) {}
	~SChessPiece() = default;
	virtual std::vector<Vector2> get_can_move_to(const int(&board)[9][10]) = 0;
	virtual std::vector<Vector2> get_can_eat(const int(&board)[9][10]) = 0;
	ChessPiece::PieceType get_type() const { return type; }
	Vector2 get_pos() const { return pos; }
};