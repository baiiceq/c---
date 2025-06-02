#pragma once

#include "chess_piece.h"
#include "animation.h"
#include "ai.h"
#include <vector>
#include <memory>

// 棋子管理器

class ChessManager
{
public:
    ChessManager();
    ~ChessManager();
    void on_render(const Camera& camera);
    void on_update(int delta, ChessPiece::Camp current_turn);
    void on_input(const ExMessage& msg, ChessPiece::Camp current_turn);

    void reset();

    void undo_move(); // 悔棋


    void set_callback_change(std::function<void(int)> callback)
    {
        callback_change = callback;
    }

    void set_callback_win(std::function<void(int)> callback)
    {
        callback_win = callback;
    }

    void set_player(bool is_red_AI, bool is_black_AI)
    {
        this->is_black_AI = is_black_AI;
        this->is_red_AI = is_red_AI;
    }

    void set_difficulty(int red, int black)
    {
        red_AI_difficulty = red;
        black_AI_difficulty = black;
    }

    void save_game_record(const std::string& filename);

    void load_game_record(const std::string& filename);

    void load();

    void load_one_step();
    
    void ai_start_think(ChessPiece::Camp current_turn);

    int get_ai_difficulty()
    {
        if(is_red_AI)
			return red_AI_difficulty;
		if (is_black_AI)
			return black_AI_difficulty;
        return 0;
	}
    void set_turn_time_limit(int limit)
    {
        turn_time_limit = limit;
	}
    int get_turn_time_limit()
    {
        return turn_time_limit;
    }
private:
    struct MoveRecord
    {
        Vector2 from_pos;                       // 起始位置
        Vector2 to_pos;                         // 目标位置

        ChessPiece::PieceType piece_type;       // 移动的棋子类型
        ChessPiece::Camp camp;                  // 移动的阵营

        ChessPiece* moved_piece = nullptr;      // 移动的棋子
        ChessPiece* captured_piece = nullptr;   // 被吃的棋子

        bool captured_alive_before = false;     // 被吃棋子之前是否是活的
    };


    void handle_click(const Vector2& mousePos, ChessPiece::Camp current_turn);
    void handle_hover(const Vector2& mousePos, ChessPiece::Camp current_turn);
    bool try_move_selected_piece_to(const Vector2& mouse_pos);

    Vector2 find_general(ChessPiece::Camp camp);

    // 判断走完一步后是否将军对方
    bool is_in_check(ChessPiece::Camp current_camp);

    // 判断走完这一步后自己是否会被将军
    bool is_legal_move();

    Vector2 mouse_to_chess_pos(const Vector2& mouse_pos)
    {
        int x = (mouse_pos.x - 260) / 60;
        int y = (mouse_pos.y - 20) / 60;
        return Vector2(x, y);
    }

    ChessPiece* get_piece_at(const Vector2& pos)
    {
        for (auto& piece : pieces) 
        {
            if (piece->get_pos() == pos && piece->get_alive()) 
            {
                return piece;
            }
        }
        return nullptr;
    }

    void waigua(ChessPiece::Camp c);

public:
    bool move_piece(const Vector2& src_pos, const Vector2& dst_pos, bool is_load, MoveRecord* r = nullptr);


private:
    bool can_operate = true;
    std::vector<ChessPiece*> pieces;
    IMAGE hover_box, selected_box, move_box, eat_box;
    ChessPiece* hovered_piece = nullptr;
    ChessPiece* selected_piece = nullptr;

    std::vector<Vector2> can_moves;
    std::vector<Vector2> can_eats;

    int map[9][10] {0};

    std::function<void(int)> callback_change;
    std::function<void(int)> callback_win;

    std::vector<MoveRecord> move_history;

    Animation anim_check;
    bool is_check = false;

    int playback_step = 0;

    bool is_black_AI = false;
    bool is_red_AI = false;
    int black_AI_difficulty = 1;
    int red_AI_difficulty = 1;

    std::atomic<bool> is_AI_thinking = false;

    Animation anim_ai_thinking;

    Timer turn_timer;
	int turn_time_limit = 30000; // 每方的时间限制，单位为毫秒
private:
    Ai ai;
};

