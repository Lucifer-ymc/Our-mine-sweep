#include "msviewmodel.h"

MSViewModel::MSViewModel() :
                                m_cmd_restart(std::make_shared<RestartCommand>(this)),
                                m_cmd_left(std::make_shared<LeftBlockCommand>(this)),
                                m_cmd_right(std::make_shared<RightBlockCommand>(this)),
                                m_sink(std::make_shared<MSViewModelSink>(this))
{
}

void MSViewModel::set_model(const std::shared_ptr<MSDataModel>& model)
{
    m_MSModel = model;
    m_MSModel->AddPropertyNotification(std::static_pointer_cast<IPropertyNotification>(m_sink));
}

std::shared_ptr<ICommandBase> MSViewModel::get_restart_command() throw()
{
    return std::static_pointer_cast<ICommandBase>(m_cmd_restart);
}

//ccx 7.10
std::shared_ptr<ICommandBase> MSViewModel::get_leftblock_command() throw()
{
    return std::static_pointer_cast<ICommandBase>(m_cmd_left );
}

//ccx 7.11
std::shared_ptr<ICommandBase> MSViewModel::get_rightblock_command() throw()
{
    return std::static_pointer_cast<ICommandBase>(m_cmd_right );
}

std::shared_ptr<Block> MSViewModel ::get_block()
{
    return m_MSModel->get_block();
}
MSDataModel& MSViewModel::get_model() throw()
{
    return *m_MSModel;
}
bool MSViewModel::restart(int row, int col, int boom_num)
{
    return m_MSModel->restart(row,col,boom_num);
}
bool MSViewModel::leftblock(int x_pos, int y_pos)
{
    return m_MSModel->leftblock(x_pos, y_pos);
}
bool MSViewModel::rightblock(int x_pos, int y_pos)
{
    return m_MSModel->rightblock(x_pos, y_pos);
}


