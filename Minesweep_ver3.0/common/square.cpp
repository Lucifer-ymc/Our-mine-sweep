#include "square.h"

Square::Square()
{
    is_boom = 0;
    is_flag = 0;
    is_mark = 0;
    is_show = 0;
    sur_boom = 0;
    visit=0;
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
QString Square::show_info(){
    QString str_debug;
    str_debug+="is_boom=";
    str_debug+=QString::number(is_boom);
    str_debug+=",is_flag=";
    str_debug+=QString::number(is_flag);
    str_debug+=",is_mark=";
    str_debug+=QString::number(is_mark);
    str_debug+=",is_show=";
    str_debug+=QString::number(is_show);
    str_debug+=",sur_boom=";
    str_debug+=QString::number(sur_boom);
    return str_debug;
}
