#pragma once
#ifndef ANSI_UTIL_H
#define ANSI_UTIL_H

#include <stdio.h>
#include <windows.h>

/* ====== 컬러 코드 ====== */
#define RED        31
#define GRN        32
#define YEL        33
#define BLU        34
#define MAG        35
#define CYN        36

#define RED_BG     41
#define GRN_BG     42
#define YEL_BG     43
#define BLU_BG     44
#define MAG_BG     45
#define CYN_BG     46

/* ====== 화면 오프셋 ====== */
#define ANSISCREEN_OFFSET_X 1
#define ANSISCREEN_OFFSET_Y 1

/* ====== ANSI 제어 함수 ====== */
void gotoXY(int _posX, int _posY);
void TextColor(int _color);
void TextBGColor(int _color);
void TextBold();
void TextUnderLine();
void HideCursor();
void ShowCursor();
void TextRGB(int _r, int _g, int _b);     /* 0~255 */
void TextBG_RGB(int _r, int _g, int _b);  /* 0~255 */

void InitTextColor();
void ClearScreen();

/* 틱 유틸 (ms) */
__int64 GetTIck();

#endif /* ANSI_UTIL_H */
