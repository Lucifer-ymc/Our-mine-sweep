#ifndef LEFTBLOCK_H
#define LEFTBLOCK_H

#include "../../common/etlbase.h"
#include "common/parameter.h"
class MSViewModel;

class LeftBlockCommand : public ICommandBase
{
public:
    LeftBlockCommand(MSViewModel* p) throw();
    virtual void SetParameter(const std::any &lparam);
    virtual void Exec();
private:
    MSViewModel* m_pVM;
    
    PosParameter m_lparam;

};


#endif // LEFTBLOCK_H
