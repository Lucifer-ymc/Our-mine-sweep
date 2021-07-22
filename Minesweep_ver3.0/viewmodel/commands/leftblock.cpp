#include "leftblock.h"
#include "../msviewmodel.h"
LeftBlockCommand::LeftBlockCommand(MSViewModel* p) throw(): m_pVM(p),m_lparam(3,3)
{
}

void LeftBlockCommand::SetParameter(const std::any& param)
{
    m_lparam = std::any_cast<PosParameter>(param);
}

void LeftBlockCommand::Exec()
{
    int i,j;
    i = m_lparam.i;
    j = m_lparam.j;
    qDebug()<<"postion is"<<i<<j;
    m_pVM->leftblock(i,j);
}
