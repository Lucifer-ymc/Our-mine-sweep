#ifndef RANK_H
#define RANK_H
#include "../../common/etlbase.h"
#include "common/parameter.h"
class MSViewModel;
class Rank: public ICommandBase{
private:
    MSViewModel* m_pVM;
    UserParameter m_param;
public:
    Rank(MSViewModel* p) throw();
    virtual void SetParameter(const std::any &param);
    virtual void Exec();
};

#endif // RANK_H
