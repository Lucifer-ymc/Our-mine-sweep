#include "block.h"
#include <QTime>
#include <QtGlobal>
Block::Block(int row, int col, int boom_num){
    srand(QTime(0,0,0).secsTo(QTime::currentTime()));
    p=new Square*[row];
    for (int i = 0; i < row ; i++){
        p[i] = new Square [col];
    }

    for (int i = 0; i < boom_num; i++){
        int index = rand()%(row*col);
        if(p[index/col][index%col].get_boom()==false){
            p[index/col][index%col].set_boom(true);
        }
        else{
            i--;
            continue;
        }
    }
    for (int i = 0; i < row ; i++){
        for (int j = 0; j < col ; j++){
			int sur = 0;
			if (p[i][j].get_boom() == true) continue;
            for (int tmp_row = i-1; tmp_row <= i+1; tmp_row++){
				if (tmp_row < 0 || tmp_row >= row ) continue;
                for (int tmp_col = j-1; tmp_col <= j+1; tmp_col++){
					if (tmp_col < 0 || tmp_col >= col || ((tmp_row == i) && (tmp_col == j))) continue;
                    if(p[tmp_row][tmp_col].get_boom()==true) sur++;
                }
            }
            p[i][j].set_sur(sur);
        }
    }
    this->col=col;
    this->row=row;
    this->boom_num=boom_num;
    this->flag=0;
    this->time=0;
	this->is_play = true;
	this->is_lose = false;
	this->is_win = false;
	this->is_lock = false;
    this->is_cheat = false;
    this->setting = JUNIOR;
    qDebug()<<"Construction Complete";
}

void Block::re_construct(int row, int col, int boom_num)
{
    srand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i =0;i < this->row;i++){
        delete[]  p[i];
    }
    delete [] p;
    p=new Square*[row];
    for (int i = 0; i < row ; i++){
        p[i] = new Square [col];
    }
    for (int i = 0; i < boom_num; i++){
        int index = rand()%(row*col);
        if(p[index/col][index%col].get_boom()==false){
            p[index/col][index%col].set_boom(true);
        }
        else{
            i--;
            continue;
        }
    }
    for (int i = 0; i < row ; i++){
        for (int j = 0; j < col ; j++){
            int sur = 0;
            if (p[i][j].get_boom() == true) continue;
            for (int tmp_row = i-1; tmp_row <= i+1; tmp_row++){
                if (tmp_row < 0 || tmp_row >= row ) continue;
                for (int tmp_col = j-1; tmp_col <= j+1; tmp_col++){
                    if (tmp_col < 0 || tmp_col >= col || ((tmp_row == i) && (tmp_col == j))) continue;
                    if(p[tmp_row][tmp_col].get_boom()==true) sur++;
                }
            }
            p[i][j].set_sur(sur);
        }
    }
    this->col=col;
    this->row=row;
    this->boom_num=boom_num;
    this->flag=0;
    this->time=0;
    this->is_play = true;
    this->is_lose = false;
    this->is_win = false;
	this->is_lock = false;
    this->is_cheat = false;
    this->setting = JUNIOR;
    qDebug()<<"Construction Complete";
}

Block::~Block(){
    for(int i =0;i<row;i++){
        delete[]  p[i];
    }
       delete [] p;
}
int Block::get_col(){
    return col;
}
int Block::get_row(){
    return row;
}
int Block::get_boom_num(){
    return boom_num;
}
int Block::get_flag_num(){
    return flag;
}
int Block:: get_time(){
    return time;
}
bool Block::get_play(){
	return is_play;
}
bool Block::get_win(){
	return is_win;
}
bool Block::get_lose(){
	return is_lose;
}
bool Block::get_lock(){
	return is_lock;
}
bool Block::get_cheat(){
    return is_cheat;
}

SETTING Block::get_setting(){
    return setting;
}
void Block::set_play(bool x){
	this->is_play = x;
}
void Block::set_win(bool x){
	this->is_win = x;
}
void Block::set_lose(bool x){
	this->is_lose = x;
}
void Block::set_lock(bool x){
	this->is_lock = x;
}
void Block::set_cheat(bool x){
    this->is_cheat=x;
}
void Block::set_flag_num(int num){
    flag=num;
}
void Block::set_setting(SETTING x){
    this->setting=x;
}
void Block::change_flag_num(int d_num){
    flag+=d_num;
}
void Block::set_time(int time){
    this->time = time;
}
void Block::change_time(int d_time){
    this->time += d_time;
}

//recursively block set show (when sur_boom == 0)
void Block::bset_show(int x, int y){
    if(this->p[x][y].visit==1) return;
    this->p[x][y].set_show(true);
    this->p[x][y].visit = 1;
	if (this->p[x][y].get_sur() != 0) return;
    for(int blockRow = x-1; blockRow <= x+1; blockRow++){
        for(int blockCol = y-1; blockCol <=y+1; blockCol++){
            if(blockRow<0||blockCol<0||blockRow>=this->get_row()||blockCol>=this->get_col())
               continue;
            if(this->p[blockRow][blockCol].visit == 0){
				if (this->p[blockRow][blockCol].get_boom()) continue;
				bset_show(blockRow, blockCol);
            }
        }
    }
}

void Block::reset_visit(int x, int y){
    for(int blockRow = x-1; blockRow <= x+1; blockRow++){
        for(int blockCol = y-1; blockCol <=y+1; blockCol++){
            //edge square
            if(blockRow<0||blockCol<0||blockRow>=this->get_row()||blockCol>=this->get_col())
               continue;
            this->p[blockRow][blockCol].visit= 0;
        }
    }
}
