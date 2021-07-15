#include "parameter.h"

BlockParameter::BlockParameter(int a, int b, int c)
{
    this->row = a;
    this->col = b;
    this->boom_num = c;
}
BlockParameter& BlockParameter::operator=(const BlockParameter& src)
{
    if( this != &src ) {
        row = src.row;
        col = src.col;
        boom_num = src.boom_num;
    }
    return *this;
}

BlockParameter& BlockParameter::operator=(BlockParameter&& src)
{
    if( this != &src ) {
        row = src.row;
        col = src.col;
        boom_num = src.boom_num;
    }
    return *this;
}
BlockParameter::BlockParameter() throw(){

}
BlockParameter::BlockParameter(const BlockParameter& src):row(src.row), col(src.col), boom_num(src.boom_num)
{
}
BlockParameter::BlockParameter(BlockParameter&& src){
    row = static_cast<int&&>(src.row);
    col = static_cast<int&&>(src.col);
    boom_num = static_cast<int&&>(src.boom_num);
}

PosParameter::PosParameter(int x,int y){
    this->i=x;
    this->j=y;
}
PosParameter& PosParameter::operator=(const PosParameter &src){
    if( this != &src ) {
        i = src.i;
        j = src.j;
    }
    return *this;
}
PosParameter& PosParameter::operator=(PosParameter &&src){
    if( this != &src ) {
        i = src.i;
        j = src.j;
    }
    return *this;
}
PosParameter::PosParameter() throw(){

}
PosParameter::PosParameter(const PosParameter& src):i(src.i),j(src.j){

}
PosParameter::PosParameter(PosParameter&& src){
    i = static_cast<int&&>(src.i);
    j = static_cast<int&&>(src.j);
}


