#ifndef RESTARTCOMMAND_H
#define RESTARTCOMMAND_H

#include "../../common/etlbase.h"
#include "common/parameter.h"
class MSViewModel;

class RestartCommand : public ICommandBase
{
public:
    RestartCommand(MSViewModel* p) throw();
    virtual void SetParameter(const std::any &param);
    virtual void Exec();
private:
    MSViewModel* m_pVM;

    BlockParameter m_param;
    
};


#endif // RESTARTCOMMAND_H
