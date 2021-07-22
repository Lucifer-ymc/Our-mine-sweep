#ifndef BLOCK_H
#define BLOCK_H
#include "./square.h"
#include <QtMath>
#include <QTime>
#include <qdebug.h>
#include <QtGlobal>
#include "parameter.h"

class Block{
public:
    Block(int row ,int col,int boom_num);
    ~Block();
    int get_col();
    int get_row();
    int get_boom_num();
    int get_flag_num();
    int get_time();
	bool get_play();
	bool get_win();
	bool get_lose();
	bool get_lock();
    bool get_cheat();//wzq 7.17
    SETTING get_setting();
    void set_setting(SETTING x);
	void set_play(bool x);
	void set_win(bool x);
	void set_lose(bool x);
    void set_cheat(bool x);
    void set_flag_num(int num);
    void change_flag_num(int d_num);
    void set_time(int time);
    void change_time(int d_time);
	void set_lock(bool x);
    void bset_show(int x, int y);
    void reset_visit(int x, int y);
    void re_construct(int row ,int col,int boom_num);
    Square **p;

private:
    int row,col,boom_num;
    int time,flag;
	bool is_play;
	bool is_win;
	bool is_lose;
	bool is_lock;
    bool is_cheat;
    SETTING setting;
    int flag_num;
};


#endif // BLOCK_H
