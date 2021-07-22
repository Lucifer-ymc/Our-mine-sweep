#include "msviewmodel.h"

MSViewModel::MSViewModel(){
    m_cmd_restart=std::make_shared<Restart>(this);
    m_cmd_left=std::make_shared<LEFTCLICK>(this);
    m_cmd_right=std::make_shared<RIGHTCLICK>(this);
    m_cmd_reset=std::make_shared<Reset>(this);
    m_cmd_rank=std::make_shared<Rank>(this);
    m_sink=std::make_shared<MSViewModelSink>(this);
}
bool MSViewModel::restart(int row, int col, int boom_num){
    return m_MSModel->restart(row,col,boom_num);
}

bool MSViewModel::leftclick(int x_pos, int y_pos){
    return m_MSModel->leftclick(x_pos, y_pos);
}

bool MSViewModel::rightclick(int x_pos, int y_pos){
    return m_MSModel->rightclick(x_pos, y_pos);
}

bool MSViewModel::resetblock(SETTING setting,int row, int col, int boom_num){
    return m_MSModel->resetblock(setting,row,col,boom_num);
}

bool MSViewModel::rankadd(UserParameter userinfo){
    return m_MSModel->rankadd(userinfo);
}//ranklist

void MSViewModel::set_model(const std::shared_ptr<MSDataModel>& model){
    m_MSModel = model;
    m_MSModel->AddPropertyNotification(std::static_pointer_cast<IPropertyNotification>(m_sink));
}

std::shared_ptr<ICommandBase> MSViewModel::get_restart_command() throw()
{
    return std::static_pointer_cast<ICommandBase>(m_cmd_restart);
}

std::shared_ptr<ICommandBase> MSViewModel::get_leftclick_command() throw()
{
    return std::static_pointer_cast<ICommandBase>(m_cmd_left );
}

std::shared_ptr<ICommandBase> MSViewModel::get_rightclick_command() throw()
{
    return std::static_pointer_cast<ICommandBase>(m_cmd_right );
}


std::shared_ptr<ICommandBase> MSViewModel::get_reset_command() throw()
{
    return std::static_pointer_cast<ICommandBase>(m_cmd_reset);
}

std::shared_ptr<ICommandBase> MSViewModel::get_rank_command() throw()
{
    return std::static_pointer_cast<ICommandBase>(m_cmd_rank);
}

std::shared_ptr<Block> MSViewModel ::get_block(){
    return m_MSModel->get_block();
}

MSDataModel& MSViewModel::get_model() throw(){
    return *m_MSModel;
}


