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
	ai_thread.detach(); // 分离线程，允许其在后台运行
}

//局势评分
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
                    case 4: score += horse_pos_value[si][sj]; break; // 马
                    case 5: score += chariot_pos_value[si][sj]; break; // 车
                    case 6: score += cannon_pos_value[si][sj]; break; // 炮
                    case 7: score += soldier_pos_value[si][sj]; break; // 卒
					default: break; // 将、士、象
				}
            }
            else{
                score -= piece_values[st-1];
                switch (st) {
                case 4: score -= horse_pos_value[si][sj]; break; // 马
                case 5: score -= chariot_pos_value[si][sj]; break; // 车
                case 6: score -= cannon_pos_value[si][sj]; break; // 炮
                case 7: score -= soldier_pos_value[si][sj]; break; // 卒
                default: break; // 将、士、象
                }
			}
		}
	return score;
}
//function alphabeta(node, depth, α, β, Player)
//if  depth = 0 or node is a terminal node
//return the heuristic value of node
//if  Player = MaxPlayer // 极大节点
//for each child of node // 极小节点
//α : = max(α, alphabeta(child, depth - 1, α, β, not(Player)))
//if β ≤ α // 该极大节点的值>=α>=β，该极大节点后面的搜索到的值肯定会大于β，因此不会被其上层的极小节点所选用了。对于根节点，β为正无穷
//break                             (*Beta cut - off*)
//return α
//else // 极小节点
//for each child of node // 极大节点
//β : = min(β, alphabeta(child, depth - 1, α, β, not(Player))) // 极小节点
//if β ≤ α // 该极大节点的值<=β<=α，该极小节点后面的搜索到的值肯定会小于α，因此不会被其上层的极大节点所选用了。对于根节点，α为负无穷
//break                             (*Alpha cut - off*)
//return β
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
                    //复原棋盘
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
                        //复原棋盘
                        current_map[x][y] = current_map[to_x][to_y];
                        current_map[to_x][to_y] = temp;
                    }
                }
            }
			delete it; // 释放棋子对象的内存
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
                    //复原棋盘
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
                        //复原棋盘
                        current_map[x][y] = current_map[to_x][to_y];
                        current_map[to_x][to_y] = temp;
                    }
                }
            }
			free(it); // 释放棋子对象的内存
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

//获得当前棋盘上所有棋子
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
    // 对棋子进行排序
    std::sort(pieces.begin(), pieces.end(), [this](const SChessPiece* a, const SChessPiece* b) {
        int value_a = piece_turn[(int)a->get_type() - 1];
        int value_b = piece_turn[(int)b->get_type() - 1];
        return value_a > value_b;
        });
	return pieces;
}
