#ifndef RIGHTBLOCKCOMMAND_H
#define RIGHTBLOCKCOMMAND_H
#include "../../common/etlbase.h"
#include "common/parameter.h"
class MSViewModel;

class RightBlockCommand : public ICommandBase
{
public:
    RightBlockCommand(MSViewModel* p) throw();
    virtual void SetParameter(const std::any &rparam);
    virtual void Exec();
private:
    MSViewModel* m_pVM;
    PosParameter m_rparam;

};

#endif // RIGHTBLOCKCOMMAND_H
