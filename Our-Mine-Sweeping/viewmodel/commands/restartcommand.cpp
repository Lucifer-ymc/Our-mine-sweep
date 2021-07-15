#include "restartcommand.h"
#include "../msviewmodel.h"
RestartCommand::RestartCommand(MSViewModel* p) throw(): m_pVM(p),m_param(0,0,0)
{
}

void RestartCommand::SetParameter(const std::any& param)
{
    m_param = std::any_cast<BlockParameter>(param);
}

void RestartCommand::Exec()
{
    int row,col,boom_num;
    row = m_param.row;
    col = m_param.col;
    boom_num = m_param.boom_num;
    m_pVM->restart(row,col,boom_num);
}
