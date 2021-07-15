#include "square.h"

Square::Square()
{
    is_boom = false;
    is_flag = false;
    is_mark = false;
    is_show = false;
    visit=0;
    sur_boom = 0;
}
bool Square::get_boom()
{
    return is_boom;
}
bool Square::get_flag()
{
    return is_flag;
}
bool Square::get_mark()
{
    return is_mark;
}
bool Square::get_show()
{
    return is_show;
}
void Square:: set_boom(bool x)
{
    is_boom=x;
}
void Square:: set_flag(bool x)
{
    is_flag=x;
}
void Square:: set_mark(bool x)
{
    is_mark=x;
}
void Square::set_show(bool x)
{
    is_show=x;
}
int Square:: get_sur()
{
    return sur_boom;
}
void Square:: set_sur(int sur)
{
    sur_boom=sur;
}
