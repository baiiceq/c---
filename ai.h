#pragma once
#include <iostream>
#include "Vector2.h"
#include "chess_piece.h"
//#include "chess_pieces.h"

const int MAX_DEPTH = 6; // ����������

typedef struct _method
{
	Vector2 rsc_pos;
	Vector2 dst_pos;
}Method;

class Ai
{
public:
	Ai() {};
    void update(int map[9][10], ChessPiece::Camp current_turn) {
		this->my_party = current_turn;
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 10; j++)
				this->map[i][j] = map[i][j];
	};
	~Ai() {};
	Method get_method() { return method; };
	void cout_method() {
		DFS(my_party, map, MAX_DEPTH, -1000000000, 1000000000);
		std::cout << "rsc_pos:" << method.rsc_pos.x << "," << method.rsc_pos.y << std::endl;
		std::cout << "dst_pos:" << method.dst_pos.x << "," << method.dst_pos.y << std::endl;
	}
private:
	int map[9][10]{0};
	Method method;
	ChessPiece::Camp my_party = ChessPiece::Camp::Black;
    int Judge(int current_map[9][10]);//������ǰ���Ƶķ���
    int DFS(ChessPiece::Camp current_party, int (& current_map)[9][10], int depth, int a, int b);
	std::vector<SChessPiece*> all_pieces(ChessPiece::Camp current_party, int current_map[9][10]);

    ChessPiece::Camp get_enemy(ChessPiece::Camp current_party) {
        return (current_party == ChessPiece::Camp::Black) ? ChessPiece::Camp::Red : ChessPiece::Camp::Black;
	}

	bool is_game_over(ChessPiece::Camp current_party, int current_map[9][10]);
	SChessPiece* get_piece(int x, int y,int a, ChessPiece::Camp current_party);
private:
// ���ӻ�����ֵ��
const int piece_values[7] = { 10000000,200,200,500,1000,450,100 };
const int piece_turn[7] = { 2,1,4,6,7,5,3};

// ����λ�ü�ֵ��[��][��]
const int soldier_pos_value[9][10] = {
    {1, 18, 15, 13, 8, 3, -1, 0, 0, 0},     // ��0��
    {3, 36, 28, 22, 17, 0, 0, 0, 0, 0},     // ��1��
    {9, 56, 42, 30, 28, 8, -3, 0, 0, 0},    // ��2��
    {10, 95, 73, 42, 21, 0, 0, 0, 0, 0},    // ��3��
    {12, 118, 80, 50, 26, 8, 5, 0, 0, 0},   // ��4��
    {10, 95, 73, 42, 21, 0, 0, 0, 0, 0},    // ��5��
    {9, 56, 42, 30, 28, 8, -3, 0, 0, 0},    // ��6��
    {3, 36, 28, 22, 17, 0, 0, 0, 0, 0},     // ��7��
    {1, 18, 15, 13, 8, 3, -1, 0, 0, 0}      // ��8��
};

// ����λ�ü�ֵ��[��][��]
const int chariot_pos_value[9][10] = {
    {185, 185, 180, 180, 180, 155, 110, 100, 115, 20},    // ��0��
    {195, 203, 198, 200, 190, 185, 148, 115, 95, 120},    // ��1��
    {190, 198, 190, 195, 180, 172, 135, 105, 100, 105},   // ��2��
    {210, 230, 215, 220, 205, 215, 185, 140, 155, 140},   // ��3��
    {220, 245, 225, 230, 225, 215, 190, 135, 155, 115},   // ��4��
    {210, 230, 215, 220, 205, 215, 185, 140, 155, 140},   // ��5��
    {190, 198, 190, 195, 180, 172, 135, 105, 100, 105},   // ��6��
    {195, 203, 198, 200, 190, 185, 148, 115, 95, 120},    // ��7��
    {185, 185, 180, 180, 180, 155, 110, 100, 115, 20}     // ��8��
};

// ���λ�ü�ֵ��[��][��]
const int horse_pos_value[9][10] = {
    {80, 80, 120, 105, 90, 80, 45, 80, 20, 20},     // ��0��
    {105, 115, 125, 175, 135, 120, 90, 45, 45, -20}, // ��1��
    {135, 200, 135, 145, 125, 135, 105, 105, 80, 20}, // ��2��
    {120, 135, 150, 150, 145, 125, 90, 105, 80, 20}, // ��3��
    {80, 105, 145, 175, 135, 120, 110, 80, -10, 20}, // ��4��
    {120, 135, 150, 145, 145, 125, 90, 105, 80, 20}, // ��5��
    {135, 200, 135, 150, 125, 135, 105, 105, 80, 20}, // ��6��
    {105, 115, 125, 175, 135, 120, 90, 45, 45, -20}, // ��7��
    {80, 80, 120, 105, 90, 80, 45, 80, 20, 20}      // ��8��
};

// �ڵ�λ�ü�ֵ��[��][��]
const int cannon_pos_value[9][10] = {
    {50, 0, 0, 0, 0, 0, 0, 0, 0, 0},      // ��0��
    {40, 0, 0, 0, 0, 0, 0, 0, 0, 0},      // ��1��
    {30, 0, 0, 0, 0, 0, 0, 10, 0, 0},     // ��2��
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},       // ��3��
    {0, 0, 40, 40, 50, 40, 50, 40, 0, 0}, // ��4��
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},       // ��5��
    {30, 0, 0, 0, 0, 0, 0, 10, 0, 0},     // ��6��
    {40, 0, 0, 0, 0, 0, 0, 0, 0, 0},      // ��7��
    {50, 0, 0, 0, 0, 0, 0, 0, 0, 0}       // ��8��
};

// �ж�����ֵ��
const int mobility_values[7] = { 0, 7, 13, 1, 1, 7, 2 };
/*int BasicValue[7] {80, 0, 0, 300, 500, 300, 100};
int GeneralPosValue[9][10]{
{ 0 },{0},{0},{1,-8,-9},{5,-8,-9},{1,-8,-9},{0},{0},{0} };
int AdvisorPosValue[9][10]{
    {0 },{0},{0},{0},{0,3},{0},{0},{0},{0}
};
int ElephantPosValue[9][10]{
    {0,0,-2 },{0},{0},{0},{0,0,3},{0},{0},{0},{0,0,-2}
};*/
/*int HorsePosValue[9][10]{
    {0,-3,5,4,2,2,5,4,2,2},{ -3,2,4,6,10,12,20,10,8,2 },{2,4,6,10,13,11,12,11,15,2},{} }
}*/
};
