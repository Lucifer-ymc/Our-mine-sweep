#include "rightblockcommand.h"
#include "../msviewmodel.h"
//ccx 7.11
RightBlockCommand::RightBlockCommand(MSViewModel* p) throw(): m_pVM(p),m_rparam(3,3)
{

}

void RightBlockCommand::SetParameter(const std::any& param)
{
    m_rparam = std::any_cast<PosParameter>(param);
    //qDebug()<<"setpara";
}

void RightBlockCommand::Exec()
{
    
    int i,j;
    i = m_rparam.i;
    j = m_rparam.j;
    qDebug()<<"postion is"<<i<<j;
    m_pVM->rightblock(i,j);
}
