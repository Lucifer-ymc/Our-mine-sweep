#ifndef SQUARE_H
#define SQUARE_H
#include<QString>

class Square{
private:
    bool is_boom;
    bool is_mark;
    bool is_flag;
    bool is_show;
    int sur_boom;

public:
    Square();
    bool get_boom();
    bool get_flag();
    bool get_mark();
    bool get_show();
    void set_boom(bool x);
    void set_flag(bool x);
    void set_mark(bool x);
    void set_show(bool x);
    int get_sur();
    void set_sur(int sur);
    int visit = 0;//has been visited during bset_show session or not
    QString show_info();

};

#endif // SQUARE_H
