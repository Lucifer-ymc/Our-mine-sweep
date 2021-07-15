#ifndef MSDATAMODEL_H
#define MSDATAMODEL_H
#include <QtDebug>
#include <fstream>
#include <cmath>
#include <vector>
#include <QFile>
#include"../common/etlbase.h"
#include"common/parameter.h"
#include"../common/block.h"


class MSDataModel : public Proxy_PropertyNotification<MSDataModel>
{
public:
    MSDataModel();
    std::shared_ptr<Block> get_block() throw();
    bool restart(int row, int col, int boom_num);
    bool leftblock(int x_pos, int y_pos);
    bool rightblock(int x_pos, int y_pos);
    
private:
    std::shared_ptr<Block> b;
};

#endif // MSDATAMODEL_H
