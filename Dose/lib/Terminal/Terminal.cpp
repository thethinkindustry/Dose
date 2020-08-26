#include "Terminal.h"

using namespace Term;

Terminal::Terminal(Stream& s)
:io{s}
{

}

void Terminal::clear()
{
    io.print("\e[2J");
}

void Terminal::resetCursor()
{
    io.print("\e[H");
}

void Terminal::resetAll()
{
    io.print("\e[0m");
}

void Terminal::moveCursor(Direction dir, uint8_t n)
{
    snprintf(cmdBuf, 10, "\e[%d%c", n, dir);
    io.print(cmdBuf);
}

void Terminal::hideCursor(bool flag)
{
    if(flag)
    {
        io.print("\e[?25l");
    }
    else
    {
        io.print("\e[?25h");
    }
    
}

void Terminal::bold(bool flag)
{
    if(flag) 
    {
        io.print("\e[1m");
    }
    else
    {
        io.print("\e[21m");
    }
    
}

void Terminal::blink(bool flag)
{
    if(flag)
    {
        io.print("\e[5m");
    }
    else
    {
        io.print("\e[25m");
    }
    
}

void Terminal::underlined(bool flag)
{
    if(flag)
    {
        io.print("\e[4m");
    }
    else
    {
        io.print("\e[24m");
    }
    
}

void Terminal::setTextColor(Color c)
{
    snprintf(cmdBuf,10, "\e[%dm", c);
    io.print(cmdBuf);
}