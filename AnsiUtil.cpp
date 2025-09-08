#include "AnsiUtil.h"

/* 커서 이동: 1,1 기준 보정 */
void gotoXY(int _posX, int _posY)
{
    printf("\x1b[%d;%dH", _posY + ANSISCREEN_OFFSET_Y, _posX + ANSISCREEN_OFFSET_X);
}

void TextColor(int _color)
{
    printf("\x1b[%dm", _color);
}

void TextBGColor(int _color)
{
    printf("\x1b[%dm", _color);
}

void TextBold()
{
    printf("\x1b[1m");
}

void TextUnderLine()
{
    printf("\x1b[4m");
}

void HideCursor()
{
    printf("\x1b[?25l");
}

void ShowCursor()
{
    printf("\x1b[?25h");
}

void TextRGB(int _r, int _g, int _b)
{
    printf("\x1b[38;2;%d;%d;%dm", _r, _g, _b);
}

void TextBG_RGB(int _r, int _g, int _b)
{
    printf("\x1b[48;2;%d;%d;%dm", _r, _g, _b);
}

void InitTextColor()
{
    printf("\x1b[0m");
}

void ClearScreen()
{
    printf("\x1b[2J");
    printf("\x1b[H");
    fflush(stdout);
}

__int64 GetTIck()
{
    return GetTickCount64();
}
