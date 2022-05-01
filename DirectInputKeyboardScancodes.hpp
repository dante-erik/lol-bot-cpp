#pragma once
#include <Windows.h>

/****************************************************************************
*
* DirectInput keyboard scan codes
*
****************************************************************************/

constexpr WORD INVALID_KEY = 0x00;
constexpr WORD DIK_ESCAPE = 0x01;
constexpr WORD DIK_1 = 0x02;
constexpr WORD DIK_2 = 0x03;
constexpr WORD DIK_3 = 0x04;
constexpr WORD DIK_4 = 0x05;
constexpr WORD DIK_5 = 0x06;
constexpr WORD DIK_6 = 0x07;
constexpr WORD DIK_7 = 0x08;
constexpr WORD DIK_8 = 0x09;
constexpr WORD DIK_9 = 0x0A;
constexpr WORD DIK_0 = 0x0B;
constexpr WORD DIK_MINUS = 0x0C; /* - on main keyboard */
constexpr WORD DIK_EQUALS = 0x0D;
constexpr WORD DIK_BACK = 0x0E; /* backspace */
constexpr WORD DIK_TAB = 0x0F;
constexpr WORD DIK_Q = 0x10;
constexpr WORD DIK_W = 0x11;
constexpr WORD DIK_E = 0x12;
constexpr WORD DIK_R = 0x13;
constexpr WORD DIK_T = 0x14;
constexpr WORD DIK_Y = 0x15;
constexpr WORD DIK_U = 0x16;
constexpr WORD DIK_I = 0x17;
constexpr WORD DIK_O = 0x18;
constexpr WORD DIK_P = 0x19;
constexpr WORD DIK_LBRACKET = 0x1A;
constexpr WORD DIK_RBRACKET = 0x1B;
constexpr WORD DIK_RETURN = 0x1C; /* Enter on main keyboard */
constexpr WORD DIK_LCONTROL = 0x1D;
constexpr WORD DIK_A = 0x1E;
constexpr WORD DIK_S = 0x1F;
constexpr WORD DIK_D = 0x20;
constexpr WORD DIK_F = 0x21;
constexpr WORD DIK_G = 0x22;
constexpr WORD DIK_H = 0x23;
constexpr WORD DIK_J = 0x24;
constexpr WORD DIK_K = 0x25;
constexpr WORD DIK_L = 0x26;
constexpr WORD DIK_SEMICOLON = 0x27;
constexpr WORD DIK_APOSTROPHE = 0x28;
constexpr WORD DIK_GRAVE = 0x29; /* accent grave */
constexpr WORD DIK_LSHIFT = 0x2A;
constexpr WORD DIK_BACKSLASH = 0x2B;
constexpr WORD DIK_Z = 0x2C;
constexpr WORD DIK_X = 0x2D;
constexpr WORD DIK_C = 0x2E;
constexpr WORD DIK_V = 0x2F;
constexpr WORD DIK_B = 0x30;
constexpr WORD DIK_N = 0x31;
constexpr WORD DIK_M = 0x32;
constexpr WORD DIK_COMMA = 0x33;
constexpr WORD DIK_PERIOD = 0x34; /* . on main keyboard */
constexpr WORD DIK_SLASH = 0x35; /* / on main keyboard */
constexpr WORD DIK_RSHIFT = 0x36;
constexpr WORD DIK_MULTIPLY = 0x37; /* * on numeric keypad */
constexpr WORD DIK_LMENU = 0x38; /* left Alt */
constexpr WORD DIK_SPACE = 0x39;
constexpr WORD DIK_CAPITAL = 0x3A;
constexpr WORD DIK_F1 = 0x3B;
constexpr WORD DIK_F2 = 0x3C;
constexpr WORD DIK_F3 = 0x3D;
constexpr WORD DIK_F4 = 0x3E;
constexpr WORD DIK_F5 = 0x3F;
constexpr WORD DIK_F6 = 0x40;
constexpr WORD DIK_F7 = 0x41;
constexpr WORD DIK_F8 = 0x42;
constexpr WORD DIK_F9 = 0x43;
constexpr WORD DIK_F10 = 0x44;
constexpr WORD DIK_NUMLOCK = 0x45;
constexpr WORD DIK_SCROLL = 0x46; /* Scroll Lock */
constexpr WORD DIK_NUMPAD7 = 0x47;
constexpr WORD DIK_NUMPAD8 = 0x48;
constexpr WORD DIK_NUMPAD9 = 0x49;
constexpr WORD DIK_SUBTRACT = 0x4A; /* - on numeric keypad */
constexpr WORD DIK_NUMPAD4 = 0x4B;
constexpr WORD DIK_NUMPAD5 = 0x4C;
constexpr WORD DIK_NUMPAD6 = 0x4D;
constexpr WORD DIK_ADD = 0x4E; /* + on numeric keypad */
constexpr WORD DIK_NUMPAD1 = 0x4F;
constexpr WORD DIK_NUMPAD2 = 0x50;
constexpr WORD DIK_NUMPAD3 = 0x51;
constexpr WORD DIK_NUMPAD0 = 0x52;
constexpr WORD DIK_DECIMAL = 0x53; /* . on numeric keypad */
constexpr WORD DIK_OEM_102 = 0x56; /* < > | on UK/Germany keyboards */
constexpr WORD DIK_F11 = 0x57;
constexpr WORD DIK_F12 = 0x58;
constexpr WORD DIK_F13 = 0x64; /* (NEC PC98) */
constexpr WORD DIK_F14 = 0x65; /* (NEC PC98) */
constexpr WORD DIK_F15 = 0x66; /* (NEC PC98) */
constexpr WORD DIK_KANA = 0x70; /* (Japanese keyboard) */
constexpr WORD DIK_ABNT_C1 = 0x73; /* / ? on Portugese (Brazilian) keyboards */
constexpr WORD DIK_CONVERT = 0x79; /* (Japanese keyboard) */
constexpr WORD DIK_NOCONVERT = 0x7B; /* (Japanese keyboard) */
constexpr WORD DIK_YEN = 0x7D; /* (Japanese keyboard) */
constexpr WORD DIK_ABNT_C2 = 0x7E; /* Numpad . on Portugese (Brazilian) keyboards */
constexpr WORD DIK_NUMPADEQUALS = 0x8D; /* = on numeric keypad (NEC PC98) */
constexpr WORD DIK_PREVTRACK = 0x90; /* Previous Track (DIK_CIRCUMFLEX on Japanese keyboard) */
constexpr WORD DIK_AT = 0x91; /* (NEC PC98) */
constexpr WORD DIK_COLON = 0x92; /* (NEC PC98) */
constexpr WORD DIK_UNDERLINE = 0x93; /* (NEC PC98) */
constexpr WORD DIK_KANJI = 0x94; /* (Japanese keyboard) */
constexpr WORD DIK_STOP = 0x95; /* (NEC PC98) */
constexpr WORD DIK_AX = 0x96; /* (Japan AX) */
constexpr WORD DIK_UNLABELED = 0x97; /* (J3100) */
constexpr WORD DIK_NEXTTRACK = 0x99; /* Next Track */
constexpr WORD DIK_NUMPADENTER = 0x9C; /* Enter on numeric keypad */
constexpr WORD DIK_RCONTROL = 0x9D;
constexpr WORD DIK_MUTE = 0xA0; /* Mute */
constexpr WORD DIK_CALCULATOR = 0xA1; /* Calculator */
constexpr WORD DIK_PLAYPAUSE = 0xA2; /* Play / Pause */
constexpr WORD DIK_MEDIASTOP = 0xA4; /* Media Stop */
constexpr WORD DIK_VOLUMEDOWN = 0xAE; /* Volume - */
constexpr WORD DIK_VOLUMEUP = 0xB0; /* Volume + */
constexpr WORD DIK_WEBHOME = 0xB2; /* Web home */
constexpr WORD DIK_NUMPADCOMMA = 0xB3; /* , on numeric keypad (NEC PC98) */
constexpr WORD DIK_DIVIDE = 0xB5; /* / on numeric keypad */
constexpr WORD DIK_SYSRQ = 0xB7;
constexpr WORD DIK_RMENU = 0xB8; /* right Alt */
constexpr WORD DIK_PAUSE = 0xC5; /* Pause */
constexpr WORD DIK_HOME = 0xC7; /* Home on arrow keypad */
constexpr WORD DIK_UP = 0xC8; /* UpArrow on arrow keypad */
constexpr WORD DIK_PRIOR = 0xC9; /* PgUp on arrow keypad */
constexpr WORD DIK_LEFT = 0xCB; /* LeftArrow on arrow keypad */
constexpr WORD DIK_RIGHT = 0xCD; /* RightArrow on arrow keypad */
constexpr WORD DIK_END = 0xCF; /* End on arrow keypad */
constexpr WORD DIK_DOWN = 0xD0; /* DownArrow on arrow keypad */
constexpr WORD DIK_NEXT = 0xD1; /* PgDn on arrow keypad */
constexpr WORD DIK_INSERT = 0xD2; /* Insert on arrow keypad */
constexpr WORD DIK_DELETE = 0xD3; /* Delete on arrow keypad */
constexpr WORD DIK_LWIN = 0xDB; /* Left Windows key */
constexpr WORD DIK_RWIN = 0xDC; /* Right Windows key */
constexpr WORD DIK_APPS = 0xDD; /* AppMenu key */
constexpr WORD DIK_POWER = 0xDE; /* System Power */
constexpr WORD DIK_SLEEP = 0xDF; /* System Sleep */
constexpr WORD DIK_WAKE = 0xE3; /* System Wake */
constexpr WORD DIK_WEBSEARCH = 0xE5; /* Web Search */
constexpr WORD DIK_WEBFAVORITES = 0xE6; /* Web Favorites */
constexpr WORD DIK_WEBREFRESH = 0xE7; /* Web Refresh */
constexpr WORD DIK_WEBSTOP = 0xE8; /* Web Stop */
constexpr WORD DIK_WEBFORWARD = 0xE9; /* Web Forward */
constexpr WORD DIK_WEBBACK = 0xEA; /* Web Back */
constexpr WORD DIK_MYCOMPUTER = 0xEB; /* My Computer */
constexpr WORD DIK_MAIL = 0xEC; /* Mail */
constexpr WORD DIK_MEDIASELECT = 0xED; /* Media Select */

constexpr WORD scancode[91] =
{
    DIK_SPACE,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    DIK_APOSTROPHE,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    DIK_COMMA,
    DIK_MINUS,
    DIK_PERIOD,
    DIK_SLASH,
    DIK_0,
    DIK_1,
    DIK_2,
    DIK_3,
    DIK_4,
    DIK_5,
    DIK_6,
    DIK_7,
    DIK_8,
    DIK_9,
    INVALID_KEY,
    DIK_SEMICOLON,
    INVALID_KEY,
    DIK_EQUALS,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    INVALID_KEY,
    DIK_LBRACKET,
    DIK_BACKSLASH,
    DIK_RBRACKET,
    INVALID_KEY,
    INVALID_KEY,
    DIK_GRAVE,
    DIK_A,
    DIK_B,
    DIK_C,
    DIK_D,
    DIK_E,
    DIK_F,
    DIK_G,
    DIK_H,
    DIK_I,
    DIK_J,
    DIK_K,
    DIK_L,
    DIK_M,
    DIK_N,
    DIK_O,
    DIK_P,
    DIK_Q,
    DIK_R,
    DIK_S,
    DIK_T,
    DIK_U,
    DIK_V,
    DIK_W,
    DIK_X,
    DIK_Y,
    DIK_Z
};