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
//��ʼ��
void MainWindow::init()
{
	//Ĭ����ʾ
	this->ui->lcd_play->display("00:00:00:000");

	this->pTimer = new QTimer;
	//�󶨶�ʱ�����ź�
	connect(this->pTimer, SIGNAL(timeout()), this, SLOT(updateDisplay()));
}

//��ʼ
void MainWindow::on_btn_start_clicked()
{
	//��ȡ��ǰʱ��
	this->baseTime = this->baseTime.currentTime();
	this->pTimer->start(1);
	}
}
//����
void MainWindow::on_btn_stop_clicked()
{
	if (this->ui->btn_stop->text() == "ֹͣ")
	{
		this->ui->btn_stop->setText("���");
		this->pTimer->stop();
	}
	else if (this->ui->btn_stop->text() == "���")
	{
		this->ui->btn_stop->setText("ֹͣ");
		this->ui->tb_display->clear();
		this->ui->lcd_play->display("00:00:00:000");
	}

}
//��ͣ
void MainWindow::on_btn_pause_clicked()
{
	static QTime pauseTime;
	if (this->ui->btn_pause->text() == "��ͣ")
	{
		pauseTime = QTime::currentTime();
		this->ui->btn_pause->setText("����");
		this->pTimer->stop();
	}
	else if (this->ui->btn_pause->text() == "����")
	{
		//���в�ֵ����
		QTime cut = QTime::currentTime();
		int t = pauseTime.msecsTo(cut);
		this->baseTime = this->baseTime.addMSecs(t);
		this->ui->btn_pause->setText("��ͣ");
		this->pTimer->start();
	}
}

//����ʱ��
void MainWindow::updateDisplay()
{
	QTime currTime = QTime::currentTime();
	int t = this->baseTime.msecsTo(currTime);
	QTime showTime(0, 0, 0, 0);
	showTime = showTime.addMSecs(t);
	this->timeStr = showTime.toString("hh:mm:ss:zzz");
	this->ui->lcd_play->display(timeStr);
}


