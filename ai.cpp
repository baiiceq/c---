#include "ai.h"
#include<thread>
#include "vector2.h"
#include "chess_pieces.h"
#include "chess_piece.h"

void Ai::ai_think()
{
	DFS(my_party, map, MAX_DEPTH, -1000000000, 1000000000);
    if (think_finished)
        think_finished();
    std::cout << "rsc_pos:" << method.rsc_pos.x << "," << method.rsc_pos.y << std::endl;
    std::cout << "dst_pos:" << method.dst_pos.x << "," << method.dst_pos.y << std::endl;
}

Method Ai::get_method()
{
    return method;
};

void Ai::cout_method(int depth)
{
	set_depth(depth);
    std::thread ai_thread(&Ai::ai_think, this);
	ai_thread.detach(); // �����̣߳��������ں�̨����
}

//��������
int Ai::Judge(int current_map[9][10])
{
    int score = 0, m = 0;
    for(int i= 0; i < 9; ++i)
        for (int j = 0; j < 10; ++j)
        {
            if (current_map[i][j] == 0)
                continue;
			ChessPiece::Camp piece_party = (current_map[i][j] > 100) ? ChessPiece::Camp::Red : ChessPiece::Camp::Black;
            int st = (current_map[i][j] > 100) ? (current_map[i][j] - 100) : (current_map[i][j]);
            int si = i;
            int sj = (piece_party == ChessPiece::Camp::Black) ? 9 - j : j;
            if (piece_party == my_party) {
                score += piece_values[st-1];
                switch(st) {
                    case 4: score += horse_pos_value[si][sj]; break; // ��
                    case 5: score += chariot_pos_value[si][sj]; break; // ��
                    case 6: score += cannon_pos_value[si][sj]; break; // ��
                    case 7: score += soldier_pos_value[si][sj]; break; // ��
					default: break; // ����ʿ����
				}
            }
            else{
                score -= piece_values[st-1];
                switch (st) {
                case 4: score -= horse_pos_value[si][sj]; break; // ��
                case 5: score -= chariot_pos_value[si][sj]; break; // ��
                case 6: score -= cannon_pos_value[si][sj]; break; // ��
                case 7: score -= soldier_pos_value[si][sj]; break; // ��
                default: break; // ����ʿ����
                }
			}
		}
	return score;
}
//function alphabeta(node, depth, ��, ��, Player)
//if  depth = 0 or node is a terminal node
//return the heuristic value of node
//if  Player = MaxPlayer // ����ڵ�
//for each child of node // ��С�ڵ�
//�� : = max(��, alphabeta(child, depth - 1, ��, ��, not(Player)))
//if �� �� �� // �ü���ڵ��ֵ>=��>=�£��ü���ڵ�������������ֵ�϶�����ڦ£���˲��ᱻ���ϲ�ļ�С�ڵ���ѡ���ˡ����ڸ��ڵ㣬��Ϊ������
//break                             (*Beta cut - off*)
//return ��
//else // ��С�ڵ�
//for each child of node // ����ڵ�
//�� : = min(��, alphabeta(child, depth - 1, ��, ��, not(Player))) // ��С�ڵ�
//if �� �� �� // �ü���ڵ��ֵ<=��<=�����ü�С�ڵ�������������ֵ�϶���С�ڦ�����˲��ᱻ���ϲ�ļ���ڵ���ѡ���ˡ����ڸ��ڵ㣬��Ϊ������
//break                             (*Alpha cut - off*)
//return ��
//(*Initial call*)
//alphabeta(origin, depth, -infinity, +infinity, MaxPlayer)

int Ai::DFS(ChessPiece::Camp current_party,int (& current_map_)[9][10], int depth, int a, int b)
{
	int current_map[9][10]; 
    for(int i = 0; i < 9; ++i)
        for (int j = 0; j < 10; ++j)
			current_map[i][j] = current_map_[i][j];
	bool flag = true;
	if (depth == 0 || is_game_over(current_party,current_map))
		return Judge(current_map);
	if (current_party == my_party) {
		for (auto& it : all_pieces(current_party,current_map))
		{  
            if (flag) {
                for (const auto& move : it->get_can_eat(current_map))
                {
                    int x = it->get_pos().x, y = it->get_pos().y;
                    int to_x = move.x, to_y = move.y;
                    int temp = current_map[to_x][to_y];
                    current_map[to_x][to_y] = current_map[x][y];
                    current_map[x][y] = 0;
                    int t = DFS(get_enemy(current_party), current_map, depth - 1, a, b);
                    if (a < t) {
                        a = t;
                        if (depth == MAX_DEPTH) {
                            method.rsc_pos = Vector2(x, y);
                            method.dst_pos = Vector2(to_x, to_y);
                        }
                    }
                    if (b <= a)
                    {
                        flag = false;
                        break;
                    }
                    //��ԭ����
                    current_map[x][y] = current_map[to_x][to_y];
                    current_map[to_x][to_y] = temp;
                }
                if (flag) {
                    for (const auto& move : it->get_can_move_to(current_map))
                    {
                        int x = it->get_pos().x, y = it->get_pos().y;
                        int to_x = move.x, to_y = move.y;
                        int temp = current_map[to_x][to_y];
                        current_map[to_x][to_y] = current_map[x][y];
                        current_map[x][y] = 0;
                        int t = DFS(get_enemy(current_party), current_map, depth - 1, a, b);
                        if(a < t){
                            a = t;
                            if (depth == MAX_DEPTH) {
                                method.rsc_pos = Vector2(x, y);
                                method.dst_pos = Vector2(to_x, to_y);
                            }
                        }
                        if (b <= a)
                        {
                            flag = false;
                            break;
                        }
                        //��ԭ����
                        current_map[x][y] = current_map[to_x][to_y];
                        current_map[to_x][to_y] = temp;
                    }
                }
            }
			delete it; // �ͷ����Ӷ�����ڴ�
		}
		return a;
	}
    else
    {
        for (auto& it : all_pieces(current_party, current_map))
        {
            if (flag) {
                for (const auto& move : it->get_can_eat(current_map))
                {
                    int x = it->get_pos().x, y = it->get_pos().y;
                    int to_x = move.x, to_y = move.y;
                    int temp = current_map[to_x][to_y];
                    current_map[to_x][to_y] = current_map[x][y];
                    current_map[x][y] = 0;
                    int t = DFS(get_enemy(current_party), current_map, depth - 1, a, b);
                    if( b > t) {
                        b = t;
					}
                    if (b <= a)
                    {
                        flag = false;
                        break; // Beta cut-off
                    }
                    //��ԭ����
                    current_map[x][y] = current_map[to_x][to_y];
                    current_map[to_x][to_y] = temp;
                }
                if (flag) {
                    for (const auto& move : it->get_can_move_to(current_map))
                    {
                        int x = it->get_pos().x, y = it->get_pos().y;
                        int to_x = move.x, to_y = move.y;
                        int temp = current_map[to_x][to_y];
                        current_map[to_x][to_y] = current_map[x][y];
                        current_map[x][y] = 0;
                        int t = DFS(get_enemy(current_party), current_map, depth - 1, a, b);
                        if (b > t) {
                            b = t;
                        }
                        if (b <= a)
                        {
                            flag = false;
                            break; 
                        }
                        //��ԭ����
                        current_map[x][y] = current_map[to_x][to_y];
                        current_map[to_x][to_y] = temp;
                    }
                }
            }
			free(it); // �ͷ����Ӷ�����ڴ�
        }
		return b;
    }

}
bool Ai::is_game_over(ChessPiece::Camp current_party, int current_map[9][10])
{
	int flag = 0;
    for (int i = 3; i < 6; ++i)
        for (int j = 0; j < 3; ++j) {
            if (current_map[i][j] == 1)
                flag++;
            if (current_map[i][j+7] == 101) 
                flag++;
        }
    if(flag==2)
		return false; 
	return true;
}

SChessPiece* Ai::get_piece(int x,int y, int a,ChessPiece::Camp current_party)
{
    if(a>100)
		a -= 100;
    switch(a)
    {
	case 1: return new SGeneral(Vector2(x, y), current_party);
	case 2:return new SAdvisor(Vector2(x, y), current_party);
	case 3:return new SElephant(Vector2(x, y), current_party);
	case 4:return new SHorse(Vector2(x, y), current_party);
	case 5:return new SChariot(Vector2(x, y), current_party);
	case 6:return new SCannon(Vector2(x, y), current_party);
	case 7:return new SSoldier(Vector2(x, y), current_party);
	}
}

//��õ�ǰ��������������
std::vector<SChessPiece*> Ai::all_pieces(ChessPiece::Camp current_party, int current_map[9][10])
{
    std::vector<SChessPiece*> pieces;
	for(int i = 0; i < 9; ++i)
        for (int j = 0; j < 10; ++j)
        {
            if (current_map[i][j] != 0)
                if (((current_party == ChessPiece::Camp::Red) && current_map[i][j] > 100) ||
                    (current_party == ChessPiece::Camp::Black && current_map[i][j] < 100)) {
                    SChessPiece* piece = get_piece(i, j, current_map[i][j], current_party);
                    pieces.push_back(piece);
                }
        }
    // �����ӽ�������
    std::sort(pieces.begin(), pieces.end(), [this](const SChessPiece* a, const SChessPiece* b) {
        int value_a = piece_turn[(int)a->get_type() - 1];
        int value_b = piece_turn[(int)b->get_type() - 1];
        return value_a > value_b;
        });
	return pieces;
}
