#include "msviewmodelsink.h"
#include "../msviewmodel.h"
MSViewModelSink::MSViewModelSink(MSViewModel* p) throw():m_pVM(p)
{
}

void MSViewModelSink::OnPropertyChanged(const std::string &str)
{
        m_pVM->Fire_OnPropertyChanged(str);
}
