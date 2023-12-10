#pragma once

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <cassert>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "tetrino.h"

#define WIDTH 10
#define HEIGHT 22
#define VISIBLE_HEIGHT 20
#define GRID_SIZE 30

#define ARRAY_COUNT(x) (sizeof(x) / sizeof((x)[0]))

const f32 TARGET_SECONDS_PER_FRAME = 1.f / 60.f;

enum Game_Phase
{
    GAME_PHASE_START,
    GAME_PHASE_PLAY,
    GAME_PHASE_LINE,
    GAME_PHASE_GAMEOVER
};
enum Text_Align
{
    TEXT_ALIGN_LEFT,
    TEXT_ALIGN_CENTER,
    TEXT_ALIGN_RIGHT
};

struct Piece_State
{
    u8 tetrino_index;
    s32 offset_row;
    s32 offset_col;
    s32 rotation;
};

struct Game_State
{
    u8 board[WIDTH * HEIGHT];
    u8 lines[HEIGHT];
    s32 pending_line_count;

    Piece_State piece;

    Game_Phase phase;

    s32 start_level;
    s32 level;
    s32 line_count;
    s32 points;

    f32 next_drop_time;
    f32 highlight_end_time;
    f32 time;
};

struct Input_State
{
    u8 left;
    u8 right;
    u8 up;
    u8 down;

    u8 a;

    s8 dleft;
    s8 dright;
    s8 dup;
    s8 ddown;
    s8 da;
};


void clear_lines(u8 *values, s32 width, s32 height, const u8 *lines);
void merge_piece(Game_State *game);
void spawn_piece(Game_State *game);
void update_game_start(Game_State *game, const Input_State *input);

void update_game_gameover(Game_State *game, const Input_State *input);

void update_game_line(Game_State *game);

void update_game_play(Game_State *game,
                      const Input_State *input);

void update_game(Game_State *game,
                 const Input_State *input);

void fill_rect(SDL_Renderer *renderer,
               s32 x, s32 y, s32 width, s32 height, Color color);

void draw_rect(SDL_Renderer *renderer,
               s32 x, s32 y, s32 width, s32 height, Color color);

void draw_string(SDL_Renderer *renderer,
                 TTF_Font *font,
                 const char *text,
                 s32 x, s32 y,
                 Text_Align alignment,
                 Color color);

void draw_cell(SDL_Renderer *renderer,
               s32 row, s32 col, u8 value,
               s32 offset_x, s32 offset_y,
               bool outline = false);
void draw_piece(SDL_Renderer *renderer, const Piece_State *piece, s32 offset_x, s32 offset_y, bool outline = false);
void draw_board(SDL_Renderer *renderer, const u8 *board, s32 width, s32 height, s32 offset_x, s32 offset_y);
void render_game(const Game_State *game, SDL_Renderer *renderer, TTF_Font *font);

