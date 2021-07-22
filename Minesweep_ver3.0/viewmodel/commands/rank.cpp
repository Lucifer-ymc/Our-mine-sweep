#include "rank.h"
#include "../msviewmodel.h"
Rank::Rank(MSViewModel* p) throw(): m_pVM(p), m_param("0",0){
}

void Rank::SetParameter(const std::any& param){
    m_param = std::any_cast<UserParameter>(param);
}

void Rank::Exec(){
    m_pVM->rankadd(m_param);
}
