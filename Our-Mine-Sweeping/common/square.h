#ifndef SQUARE_H
#define SQUARE_H
#include<QString>

class Square
{
public:
    Square();
    bool get_boom();
    bool get_flag();
    bool get_mark();
    bool get_show();//ccx 7.10
    void set_boom(bool x);
    void set_flag(bool x);
    void set_mark(bool x);
    void set_show(bool x);//ccx 7.10
    int get_sur();
    void set_sur(int sur);
    
    //ccx 10.7
    int visit = 0;//has been visited during bset_show session or not
    QString show_info()
    {
        QString x;
        x+="is_boom:";
        x+=QString::number(is_boom);
        x+=",is_flag:";
        x+=QString::number(is_flag);
        x+=",is_mark:";
        x+=QString::number(is_mark);
        x+=",is_show:";
        x+=QString::number(is_show);
        x+=",sur_boom:";
        x+=QString::number(sur_boom);
        return x;
    }

private:
    bool is_boom;
    bool is_mark;
    bool is_flag;
    bool is_show;//ccx 7.10
    int sur_boom;
};

#endif // SQUARE_H
