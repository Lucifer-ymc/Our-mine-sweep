#ifndef MSVIEWMODEL_H
#define MSVIEWMODEL_H

#include"../common/etlbase.h"
#include"./sinks/msviewmodelsink.h"
#include"../model/msdatamodel.h"
#include"../common/parameter.h"

#include"commands/leftclick.h"
#include"commands/rightclick.h"
#include"./commands/restart.h"
#include"commands/reset.h"
#include"commands/rank.h"

class MSViewModel : public Proxy_CommandNotification<MSViewModel>, public Proxy_PropertyNotification<MSViewModel>{
private:
    std::shared_ptr<MSDataModel> m_MSModel;

    std::shared_ptr<LEFTCLICK> m_cmd_left;
    std::shared_ptr<RIGHTCLICK> m_cmd_right;

    std::shared_ptr<Restart> m_cmd_restart;
    std::shared_ptr<Reset> m_cmd_reset;
    std::shared_ptr<Rank> m_cmd_rank;

    std::shared_ptr<MSViewModelSink> m_sink;
public:
    MSViewModel();
    void set_model(const std::shared_ptr<MSDataModel>& model);
    MSDataModel& get_model() throw();

    std::shared_ptr<ICommandBase> get_restart_command() throw();
    std::shared_ptr<ICommandBase> get_leftclick_command() throw();
    std::shared_ptr<ICommandBase> get_rightclick_command() throw();
    std::shared_ptr<ICommandBase> get_reset_command() throw();
    std::shared_ptr<ICommandBase> get_rank_command() throw();//7.19 ranklist
    std::shared_ptr<Block> get_block();
    bool restart(int row, int col, int boom_num);
    bool leftclick(int x_pos, int y_pos);
    bool rightclick(int x_pos, int y_pos);
    bool resetblock(SETTING setting,int row, int col, int boom_num);
    bool rankadd(UserParameter userinfo);

};

#endif // MSVIEWMODEL_H
