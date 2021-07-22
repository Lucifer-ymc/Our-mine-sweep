#include "leftclick.h"
#include "../msviewmodel.h"
LEFTCLICK::LEFTCLICK(MSViewModel* p) throw(): m_pVM(p),m_lparam(3,3){

}

void LEFTCLICK::SetParameter(const std::any& param){
    m_lparam = std::any_cast<PosParameter>(param);
}

void LEFTCLICK::Exec(){
    m_pVM->leftclick(m_lparam.i,m_lparam.j);
}
