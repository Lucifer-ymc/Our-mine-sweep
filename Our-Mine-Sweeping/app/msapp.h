#ifndef MSAPP_H
#define MSAPP_H
#include <QApplication>
#include "./view/mainwindow.h"
#include "../model/msdatamodel.h"
#include "../viewmodel/msviewmodel.h"
class MSApp
{
public:
    MSApp();
    ~MSApp() throw();
    bool Init(MainWindow& w);
private:
    std::shared_ptr<MSViewModel>  m_spViewModel;
};

#endif // MSAPP_H
