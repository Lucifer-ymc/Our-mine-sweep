#ifndef RESET_H
#define RESET_H
#include "../../common/etlbase.h"
#include "common/parameter.h"
class MSViewModel;
class Reset: public ICommandBase{
private:
    MSViewModel* m_pVM;
    SettingParameter m_param;
public:
    Reset(MSViewModel* p) throw();
    virtual void SetParameter(const std::any &param);
    virtual void Exec();

};

#endif // RESET_H
