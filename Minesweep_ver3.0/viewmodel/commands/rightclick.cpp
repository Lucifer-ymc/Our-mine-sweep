#include "rightclick.h"
#include "../msviewmodel.h"
RIGHTCLICK::RIGHTCLICK(MSViewModel* p) throw(): m_pVM(p),m_rparam(3,3){

}

void RIGHTCLICK::SetParameter(const std::any& param){
    m_rparam = std::any_cast<PosParameter>(param);
}

void RIGHTCLICK::Exec(){
    m_pVM->rightclick(m_rparam.i,m_rparam.j);
}
