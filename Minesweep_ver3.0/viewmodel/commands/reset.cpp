#include "reset.h"
#include "../msviewmodel.h"
Reset::Reset(MSViewModel* p) throw(): m_pVM(p),m_param(JUNIOR,8,8,10){

}

void Reset::SetParameter(const std::any& param){
    m_param = std::any_cast<SettingParameter>(param);
}

void Reset::Exec(){
    m_pVM->resetblock(m_param.setting, m_param.row, m_param.col, m_param.boom_num);
}
