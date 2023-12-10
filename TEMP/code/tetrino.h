#pragma once
#include "tetris.h"

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef float f32;
typedef double f64;

struct Color
{
    u8 r;
    u8 g;
    u8 b;
    u8 a;
};

inline Color
color(u8 r, u8 g, u8 b, u8 a)
{
    Color result;
    result.r = r;
    result.g = g;
    result.b = b;
    result.a = a;
    return result;
}

const Color BASE_COLORS[] = {
    color(0x28, 0x28, 0x28, 0xFF),
    color(0x2D, 0x99, 0x99, 0xFF),
    color(0x99, 0x99, 0x2D, 0xFF),
    color(0x99, 0x2D, 0x99, 0xFF),
    color(0x2D, 0x99, 0x51, 0xFF),
    color(0x99, 0x2D, 0x2D, 0xFF),
    color(0x2D, 0x63, 0x99, 0xFF),
    color(0x99, 0x63, 0x2D, 0xFF)
};

const Color LIGHT_COLORS[] = {
    color(0x28, 0x28, 0x28, 0xFF),
    color(0x44, 0xE5, 0xE5, 0xFF),
    color(0xE5, 0xE5, 0x44, 0xFF),
    color(0xE5, 0x44, 0xE5, 0xFF),
    color(0x44, 0xE5, 0x7A, 0xFF),
    color(0xE5, 0x44, 0x44, 0xFF),
    color(0x44, 0x95, 0xE5, 0xFF),
    color(0xE5, 0x95, 0x44, 0xFF)
};

const Color DARK_COLORS[] = {
    color(0x28, 0x28, 0x28, 0xFF),
    color(0x1E, 0x66, 0x66, 0xFF),
    color(0x66, 0x66, 0x1E, 0xFF),
    color(0x66, 0x1E, 0x66, 0xFF),
    color(0x1E, 0x66, 0x36, 0xFF),
    color(0x66, 0x1E, 0x1E, 0xFF),
    color(0x1E, 0x42, 0x66, 0xFF),
    color(0x66, 0x42, 0x1E, 0xFF)
};

const u8 FRAMES_PER_DROP[] = {
    48,
    43,
    38,
    33,
    28,
    23,
    18,
    13,
    8,
    6,
    5,
    5,
    5,
    4,
    4,
    4,
    3,
    3,
    3,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    1};

struct Tetrino
{
    const u8 *data;
    const s32 side;
};

inline Tetrino
tetrino(const u8 *data, s32 side)
{
    return {data, side};
}

const u8 TETRINO_1[] = {
    0, 0, 0, 0,
    1, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0};

const u8 TETRINO_2[] = {
    2, 2,
    2, 2};

const u8 TETRINO_3[] = {
    0, 0, 0,
    3, 3, 3,
    0, 3, 0};

const u8 TETRINO_4[] = {
    0, 4, 4,
    4, 4, 0,
    0, 0, 0};

const u8 TETRINO_5[] = {
    5, 5, 0,
    0, 5, 5,
    0, 0, 0};

const u8 TETRINO_6[] = {
    6, 0, 0,
    6, 6, 6,
    0, 0, 0};

const u8 TETRINO_7[] = {
    0, 0, 7,
    7, 7, 7,
    0, 0, 0};

const Tetrino TETRINOS[] = {
    tetrino(TETRINO_1, 4),
    tetrino(TETRINO_2, 2),
    tetrino(TETRINO_3, 3),
    tetrino(TETRINO_4, 3),
    tetrino(TETRINO_5, 3),
    tetrino(TETRINO_6, 3),
    tetrino(TETRINO_7, 3),
};