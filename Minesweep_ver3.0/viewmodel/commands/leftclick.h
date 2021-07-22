#ifndef LEFTCLICK_H
#define LEFTCLICK_H
#include "../../common/etlbase.h"
#include "common/parameter.h"
class MSViewModel;
class LEFTCLICK : public ICommandBase{
private:
    MSViewModel* m_pVM;
    PosParameter m_lparam;
public:
    LEFTCLICK(MSViewModel* p) throw();
    virtual void SetParameter(const std::any &lparam);
    virtual void Exec();
};

#endif // LEFTCLICK_H
