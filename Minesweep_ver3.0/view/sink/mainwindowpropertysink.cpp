#include "mainwindowpropertysink.h"
#include "../mainwindow.h"
MainWindowPropertySink::MainWindowPropertySink(MainWindow* pW) throw() : m_pW(pW)
{
}

void MainWindowPropertySink::OnPropertyChanged(const std::string& str){
    if( str == "block" ){ 
        m_pW->update();
    }
    //click the emoji
    if (str == "restart"){
        m_pW->paint_flag=0;
        m_pW->initialize();
        m_pW->time_initialize();
        m_pW->update();
    }
    //win or lose,show the message box
    if( str == "win" ){
		m_pW->update();
        m_pW->show_win();
    }
    if( str == "lose"){
		m_pW->update();
        QMessageBox::information(NULL,"Sorry","               You lose!\nClick the emoji to restart game.");
    }

}
