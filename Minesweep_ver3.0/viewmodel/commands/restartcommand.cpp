﻿#include "restartcommand.h"
#include "../msviewmodel.h"
RestartCommand::RestartCommand(MSViewModel* p) throw(): m_pVM(p),m_param(0,0,0){

}

void RestartCommand::SetParameter(const std::any& param){
    m_param = std::any_cast<BlockParameter>(param);
}

void RestartCommand::Exec(){
    m_pVM->restart(m_param.row,m_param.col,m_param.boom_num);
}
