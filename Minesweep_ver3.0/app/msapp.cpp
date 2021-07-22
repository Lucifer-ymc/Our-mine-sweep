#include "msapp.h"
MSApp::MSApp(){

}
MSApp::~MSApp() throw(){

}
bool MSApp::Init(MainWindow& w){
    //objects
    std::shared_ptr<MSDataModel> spModel(std::make_shared<MSDataModel>());
    m_spViewModel = std::make_shared<MSViewModel>();
    m_spViewModel->set_model(spModel);
    //binding
    // properties
    w.set_block(m_spViewModel->get_block());
    // commands
    w.set_restart_command(m_spViewModel->get_restart_command());
    w.set_leftclick_command(m_spViewModel->get_leftclick_command());
    w.set_rightclick_command(m_spViewModel->get_rightclick_command());
    w.set_setting_command(m_spViewModel->get_reset_command());
    w.set_rank_command(m_spViewModel->get_rank_command());
    // notifications
    m_spViewModel->AddPropertyNotification(w.get_propertty_sink());
    w.setWindowTitle("Mine Sweeping");
    w.initialize();
    w.show();
    return true;
}
