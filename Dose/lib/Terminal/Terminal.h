#ifndef __TERMINAL__
#define __TERMINAL__
#include <Stream.h>

/*
    constexpr static char red[] = "\u001b[31m";
    constexpr static char reset[] = "\u001b[0m";

*/

namespace Term
{

enum Color
{
    Black   = 30,
    Red     = 31,
    Green   = 32,
    Yellow  = 33,
    Blue    = 34,
    Magenta = 35,
    Cyan    = 36,
    LightGray = 37,
    DarkGray = 90,
    White = 97,
    Default = 39

};

enum Direction
{
    Up = 'A',
    Down = 'B',
    Right = 'C',
    Left = 'D'
};

class Terminal
{

    public:
    Terminal(Stream&);
    void clear();
    void resetCursor();
    void setTextColor(Color c);
    void resetAll();
    void moveCursor(Direction dir, uint8_t n);
    void hideCursor(bool);
    void bold(bool);
    void blink(bool);
    void underlined(bool);


    private:
    Stream& io;
    char cmdBuf[10] = {0};


};

}


#endif