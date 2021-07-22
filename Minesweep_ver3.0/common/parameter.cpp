#include "parameter.h"

//block parameter
BlockParameter::BlockParameter(int a, int b, int c){
    this->row = a;
    this->col = b;
   this->boom_num = c;
}

BlockParameter::BlockParameter(const BlockParameter& block):row(block.row), col(block.col), boom_num(block.boom_num){

}
BlockParameter::BlockParameter(BlockParameter&& block){
    row = static_cast<int&&>(block.row);
    col = static_cast<int&&>(block.col);
    boom_num = static_cast<int&&>(block.boom_num);
}

BlockParameter& BlockParameter::operator=(const BlockParameter& block){
    if( this != &block ) {
        row = block.row;
        col = block.col;
        boom_num = block.boom_num;
    }
    return *this;
}

BlockParameter& BlockParameter::operator=(BlockParameter&& block){
    if( this != &block ) {
        row = block.row;
        col = block.col;
        boom_num = block.boom_num;
    }
    return *this;
}

BlockParameter::BlockParameter() throw(){

}

//position parameter
PosParameter::PosParameter(int x,int y){
    this->i=x;
    this->j=y;
}

PosParameter::PosParameter(const PosParameter& pos):i(pos.i),j(pos.j){

}

PosParameter::PosParameter(PosParameter&& pos){
    i = static_cast<int&&>(pos.i);
    j = static_cast<int&&>(pos.j);
}

PosParameter& PosParameter::operator=(const PosParameter &pos){
    if( this != &pos ) {
        i = pos.i;
        j = pos.j;
    }
    return *this;
}
PosParameter& PosParameter::operator=(PosParameter &&pos){
    if( this != &pos ) {
        i = pos.i;
        j = pos.j;
    }
    return *this;
}

PosParameter::PosParameter() throw(){

}


//setting parameter
SettingParameter::SettingParameter(SETTING x,int row,int col,int boom_num){
    this->setting=x;
    this->row=row;
    this->col=col;
    this->boom_num=boom_num;
}

SettingParameter::SettingParameter(const SettingParameter&set):setting(set.setting),row(set.row),col(set.col),boom_num(set.boom_num){

}

SettingParameter::SettingParameter(SettingParameter&& set){
    setting = static_cast<SETTING&&>(set.setting);
    row = static_cast<int&&>(set.row);
    col = static_cast<int&&>(set.col);
    boom_num = static_cast<int&&>(set.boom_num);
}

SettingParameter& SettingParameter::operator=(const SettingParameter &set){
    if( this != &set ) {
        this->setting=set.setting;
        this->row=set.row;
        this->col=set.col;
        this->boom_num=set.boom_num;
    }
    return *this;
}

SettingParameter& SettingParameter::operator=(SettingParameter &&set){
    if( this != &set ) {
        this->setting=set.setting;
        this->row=set.row;
        this->col=set.col;
        this->boom_num=set.boom_num;
    }
    return *this;
}

SettingParameter::SettingParameter() throw(){

}


//user parameter
//7.19 wzq
//write for rank list,save time and id
UserParameter::UserParameter(const UserParameter& u){
    this->name=u.name;
    this->time=u.time;
}

UserParameter::UserParameter(UserParameter&& u){
    name=static_cast<std::string&&>(u.name);
    time=static_cast<int&&>(u.time);
}

UserParameter::UserParameter(std::string name, int time){
    this->name=name;
    this->time=time;
}

UserParameter::UserParameter() throw(){

}


UserParameter& UserParameter::operator=(const UserParameter& u){
    if(this!=&u){
        this->name=u.name;
        this->time=u.time;
    }
    return *this;
}

UserParameter& UserParameter::operator=(UserParameter&& u){
    if(this!=&u){
        this->name=u.name;
        this->time=u.time;
    }
    return *this;
}

//sort of ranking list
//wzq 7.19
bool ranksort(const UserParameter& U1, const UserParameter& U2){
    if((U1.time<U2.time)||((U1.time==U2.time)&&(U1.name<U2.name))){
        return 1;
    }else{
        return 0;
    }

}
