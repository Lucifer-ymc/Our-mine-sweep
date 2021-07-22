#ifndef RIGHTCLICK_H
#define RIGHTCLICK_H
#include "../../common/etlbase.h"
#include "common/parameter.h"
class MSViewModel;
class RIGHTCLICK : public ICommandBase{
private:
    MSViewModel* m_pVM;
    PosParameter m_rparam;
public:
    RIGHTCLICK(MSViewModel* p) throw();
    virtual void SetParameter(const std::any &rparam);
    virtual void Exec();
};

#endif // RIGHTCLICK_H
