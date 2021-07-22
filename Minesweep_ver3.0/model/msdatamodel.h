#ifndef MSDATAMODEL_H
#define MSDATAMODEL_H
#include"../common/etlbase.h"
#include"common/parameter.h"
#include"../common/block.h"
#include <QtDebug>
#include <fstream>
#include <cmath>
#include <vector>
#include <QFile>

class MSDataModel : public Proxy_PropertyNotification<MSDataModel>{
private:
    std::shared_ptr<Block> b;
public:
    MSDataModel();
    std::shared_ptr<Block> get_block() throw();
    bool restart(int row, int col, int boom_num);
    bool leftclick(int x_pos, int y_pos);
    bool rightclick(int x_pos, int y_pos);
    bool resetblock(SETTING setting,int row, int col, int boom_num);
    bool rankadd(UserParameter userinfo);//rank list
    
};

#endif // MSDATAMODEL_H
