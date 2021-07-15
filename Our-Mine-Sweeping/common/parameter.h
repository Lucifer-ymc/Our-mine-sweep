#ifndef PARAMETER_H
#define PARAMETER_H
#include<QString>
#include<string>

class BlockParameter
{
public:
    BlockParameter() throw();
    BlockParameter(const BlockParameter& src);
    BlockParameter(BlockParameter&& src);

    BlockParameter(int a, int b, int c);
    BlockParameter& operator=(const BlockParameter& src);
    BlockParameter& operator=(BlockParameter&& src);
public:
    int row;
    int col;
    int boom_num;
};

//ccx 7.10
class PosParameter{
public:
    PosParameter() throw();
    PosParameter(const PosParameter& src);
    PosParameter(PosParameter&& src);

    PosParameter(int a, int b);
    PosParameter& operator=(const PosParameter& src);
    PosParameter& operator=(PosParameter&& src);
public:
    int i;
    int j;
};

#endif // PARAMETER_H
