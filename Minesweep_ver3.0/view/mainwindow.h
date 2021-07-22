#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMouseEvent>
#include <QPaintEvent>
#include <QMainWindow>
#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QMessageBox>
#include <fstream>
#include <string>
#include <iostream>
#include"../common/etlbase.h"
#include"sink/mainwindowpropertysink.h"
#include"common/parameter.h"
#include"common/block.h"
#include"common/square.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT
private:
    Ui::MainWindow *ui;
    QTimer *runtime;
    int click_x,click_y;
    std::shared_ptr<ICommandBase> m_cmd_restart;
    std::shared_ptr<ICommandBase> m_cmd_left;
    std::shared_ptr<ICommandBase> m_cmd_right;
    std::shared_ptr<ICommandBase> m_cmd_setting;
    std::shared_ptr<ICommandBase> m_cmd_rank;
    std::shared_ptr<MainWindowPropertySink> m_sink_property;
    std::shared_ptr<Block> B;

private slots:
    void set_junior();
    void set_middle();
    void set_senior();
    void set_cheat();
    void set_custom();
    void show_ranking();
    void show_creators();
    void addtime();

protected:
    virtual void paintEvent(QPaintEvent * event);
    virtual void mousePressEvent(QMouseEvent * event);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void set_restart_command(const std::shared_ptr<ICommandBase>& cmd) throw();
    void set_leftclick_command(const std::shared_ptr<ICommandBase>& cmd) throw();
    void set_rightclick_command(const std::shared_ptr<ICommandBase>& cmd) throw();
    void set_setting_command(const std::shared_ptr<ICommandBase>& cmd) throw();
    void set_rank_command(const std::shared_ptr<ICommandBase>& cmd) throw();
    void set_restart_num(const int num) throw();
    void set_block(const std:: shared_ptr<Block> b);
    std::shared_ptr<IPropertyNotification> get_propertty_sink() throw();
    void paint_restart_num();
    void paint_boom(QPainter  * painter);
    void paint_time(QPainter  * painter);
    void paint_title(QPainter  * painter);
    void initialize();
    void time_initialize();
    void show_win();
    int paint_flag=0;

};
#endif // MAINWINDOW_H
