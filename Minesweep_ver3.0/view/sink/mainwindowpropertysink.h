#ifndef MAINWINDOWPROPERTYSINK_H
#define MAINWINDOWPROPERTYSINK_H

#include "../../common/etlbase.h"

class MainWindow;

class MainWindowPropertySink : public IPropertyNotification{
public:
    MainWindowPropertySink(MainWindow* pW) throw();
    virtual void OnPropertyChanged(const std::string& str);

private:
    MainWindow* m_pW;
};

#endif // MAINWINDOWPROPERTYSINK_H
