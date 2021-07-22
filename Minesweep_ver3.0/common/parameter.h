#ifndef PARAMETER_H
#define PARAMETER_H
#include<QString>
#include<string>

enum SETTING { JUNIOR, MIDDLE, SENIOR, CUSTOM };

class BlockParameter
{
public:
    BlockParameter() throw();
    BlockParameter(const BlockParameter& block);
    BlockParameter(BlockParameter&& block);

    BlockParameter(int a, int b, int c);
    BlockParameter& operator=(const BlockParameter& block);
    BlockParameter& operator=(BlockParameter&& block);
public:
    int row;
    int col;
    int boom_num;
};


class PosParameter{
public:
    PosParameter() throw();
    PosParameter(const PosParameter& pos);
    PosParameter(PosParameter&& pos);

    PosParameter(int a, int b);
    PosParameter& operator=(const PosParameter& pos);
    PosParameter& operator=(PosParameter&& pos);
public:
    int i;
    int j;
};

class SettingParameter{
public:
    SETTING setting;
    int row;
    int col;
    int boom_num;
public:
    SettingParameter() throw();
    SettingParameter(const SettingParameter& set);
    SettingParameter(SettingParameter&& set);

    SettingParameter(SETTING x,int row,int col, int boom_num);
    SettingParameter& operator=(const SettingParameter& set);
    SettingParameter& operator=(SettingParameter&& set);
};

//7.19 wzq
//write for rank list,save time and id
class UserParameter{
public:
    std::string name;
    int time;
    UserParameter() throw();
    UserParameter(const UserParameter& u);
    UserParameter(UserParameter&& u);

    UserParameter(std::string name, int time);
    UserParameter& operator=(const UserParameter& u);
    UserParameter& operator=(UserParameter&& u);
};


bool ranksort(const UserParameter& U1, const UserParameter& U2);
#endif // PARAMETER_H
