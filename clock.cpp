#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	this->init();
}

MainWindow::~MainWindow()
{
	delete this->pTimer;
	delete ui;
}
//初始化
void MainWindow::init()
{
	//默认显示
	this->ui->lcd_play->display("00:00:00:000");

	this->pTimer = new QTimer;
	//绑定定时器的信号
	connect(this->pTimer, SIGNAL(timeout()), this, SLOT(updateDisplay()));
}

//开始
void MainWindow::on_btn_start_clicked()
{
	//获取当前时间
	this->baseTime = this->baseTime.currentTime();
	this->pTimer->start(1);
	}
}
//结束
void MainWindow::on_btn_stop_clicked()
{
	if (this->ui->btn_stop->text() == "停止")
	{
		this->ui->btn_stop->setText("清空");
		this->pTimer->stop();
	}
	else if (this->ui->btn_stop->text() == "清空")
	{
		this->ui->btn_stop->setText("停止");
		this->ui->tb_display->clear();
		this->ui->lcd_play->display("00:00:00:000");
	}

}
//暂停
void MainWindow::on_btn_pause_clicked()
{
	static QTime pauseTime;
	if (this->ui->btn_pause->text() == "暂停")
	{
		pauseTime = QTime::currentTime();
		this->ui->btn_pause->setText("继续");
		this->pTimer->stop();
	}
	else if (this->ui->btn_pause->text() == "继续")
	{
		//进行差值计算
		QTime cut = QTime::currentTime();
		int t = pauseTime.msecsTo(cut);
		this->baseTime = this->baseTime.addMSecs(t);
		this->ui->btn_pause->setText("暂停");
		this->pTimer->start();
	}
}

//更新时间
void MainWindow::updateDisplay()
{
	QTime currTime = QTime::currentTime();
	int t = this->baseTime.msecsTo(currTime);
	QTime showTime(0, 0, 0, 0);
	showTime = showTime.addMSecs(t);
	this->timeStr = showTime.toString("hh:mm:ss:zzz");
	this->ui->lcd_play->display(timeStr);
}


