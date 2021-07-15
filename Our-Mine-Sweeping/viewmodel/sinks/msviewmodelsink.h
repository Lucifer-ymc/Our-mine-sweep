#ifndef MSVIEWMODELSINK_H
#define MSVIEWMODELSINK_H
#include "../../common/etlbase.h"

class MSViewModel;

class MSViewModelSink : public IPropertyNotification
{
public:
    MSViewModelSink(MSViewModel* p) throw();
    virtual void OnPropertyChanged(const std::string &str);
private:
    MSViewModel* m_pVM;
};

#endif // MSVIEWMODELSINK_H
