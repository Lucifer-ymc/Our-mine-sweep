#ifndef RESTART_H
#define RESTART_H
#include "../../common/etlbase.h"
#include "common/parameter.h"
class MSViewModel;
class Restart:public ICommandBase{
private:
    MSViewModel* m_pVM;
    BlockParameter m_param;
public:
    Restart(MSViewModel* p) throw();
    virtual void SetParameter(const std::any &param);
    virtual void Exec();
};

#endif // RESTART_H
