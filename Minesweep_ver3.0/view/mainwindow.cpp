#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include<string>
int BLOCK_LENGTH=21;
int BLOCK_HEIGHT=21;
int TITLE_HEIGHT=63;
int TITLE_BEGIN=23;
int ELENUM_LENGTH=20;
QPainter *paint_my_window;
MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow),m_sink_property(std::make_shared<MainWindowPropertySink>(this)){

    ui->setupUi(this);

    connect(ui->actionJunior, SIGNAL(triggered(bool)), this, SLOT(set_junior()));
    connect(ui->actionMiddle, SIGNAL(triggered(bool)),this,SLOT(set_middle()));
    connect(ui->actionSenior, SIGNAL(triggered(bool)),this,SLOT(set_senior()));
    connect(ui->actionCreators,SIGNAL(triggered(bool)),this,SLOT(show_creators()));
    connect(ui->actionCHEAT,SIGNAL(triggered(bool)),this,SLOT(set_cheat()));
    connect(ui->actionCustom,SIGNAL(triggered(bool)),this,SLOT(set_custom()));
    connect(ui->actionRanking,SIGNAL(triggered(bool)),this,SLOT(show_ranking()));

    runtime=new QTimer(this);
    connect(runtime,SIGNAL(timeout()),this,SLOT(addtime()));
    runtime->start(1000);
    connect(runtime,SIGNAL(timeout()),this,SLOT(update()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialize()//draw the initial ui
{
    int LENGTH=B->get_col()*21;
    int HEIGHT=B->get_row()*21+63;//63 is the height of title
    setFixedSize(LENGTH,HEIGHT);
    this->resize(LENGTH,HEIGHT);
}

void MainWindow::addtime()//when the game does not finish, add the time.
{
    if(!B->get_win())
        B->change_time(1);
}

//7.17 难度切换
void MainWindow::set_junior()
{
	std::any param(std::make_any<SettingParameter>(JUNIOR, 0, 0, 0));
    m_cmd_setting->SetParameter(param);
    m_cmd_setting->Exec();
}

void MainWindow::set_middle()
{
	std::any param(std::make_any<SettingParameter>(MIDDLE, 0, 0, 0));
    m_cmd_setting->SetParameter(param);
    m_cmd_setting->Exec();
}

void MainWindow::set_senior()
{
	std::any param(std::make_any<SettingParameter>(SENIOR, 0, 0, 0));
    m_cmd_setting->SetParameter(param);
    m_cmd_setting->Exec();
}

void MainWindow::set_cheat()
{
    if(B->get_cheat()==true)
        B->set_cheat(false);
    else
        B->set_cheat(true);
    this->update();
}

void MainWindow::set_custom()
{   //QHBoxLayout *Mainlayout =new QHBoxLayout;
    QGridLayout *layout= new QGridLayout;
    QDialog *dialog = new QDialog(this);
    QString explain1 = "please coustomize the number of Rows/";
    QString explain2 = "Columns/Booms in the map.";
    QString s1="Number of Rows:";
    QString s2="Number of Cols:";
    QString s3="Number of Booms:";
    QLabel *lable_exp1= new QLabel(explain1);
    QLabel *lable_exp2= new QLabel(explain2);
    QLabel *lable1= new QLabel(s1);
    QLabel *lable2= new QLabel(s2);
    QLabel *lable3= new QLabel(s3);
    QLineEdit *edit1 = new QLineEdit;
    QLineEdit *edit2 = new QLineEdit;
    QLineEdit *edit3 = new QLineEdit;
    QPushButton *button = new QPushButton("OK");
    dialog->setWindowTitle("Customize");
    layout->addWidget(lable_exp1,0,0,1,3);
    layout->addWidget(lable_exp2,2,0,1,3);
    layout->addWidget(lable1,4,0,1,1);
    layout->addWidget(edit1,4,2,1,1);
    layout->addWidget(lable2,6,0,1,1);
    layout->addWidget(edit2,6,2,1,1);
    layout->addWidget(lable3,8,0,1,1);
    layout->addWidget(edit3,8,2,1,1);
    layout->addWidget(button,10,0,1,3);
    dialog->setLayout(layout);


    dialog->show();
    connect(button,&QPushButton::clicked,this,[=]{
        QString str1=edit1->text();
        QString str2=edit2->text();
        QString str3=edit3->text();
        int row=str1.toInt();
        int col=str2.toInt();
        int boom_num=str3.toInt();
        std::any param(std::make_any<SettingParameter>(CUSTOM, row, col, boom_num));
        m_cmd_setting->SetParameter(param);
        m_cmd_setting->Exec();
        dialog->close();
    });
}

void MainWindow::show_creators()
{   QGridLayout *layout= new QGridLayout;
    QDialog *dialog = new QDialog(this);
    QString s1="The game<b> \"Mine Sweeping\"</b> is created by";
    QString s2="Yu Mingchen, Wang Ziqing, Xue Yuan.";
    QString s3="This is version 2.0.";
    QString s4="<b>Thank you for playing!</b>" ;
    QLabel *lable1= new QLabel(s1);
    QLabel *lable2= new QLabel(s2);
    QLabel *lable3= new QLabel(s3);
    QLabel *lable4= new QLabel(s4);
    dialog->setWindowTitle("Creator");
    layout->addWidget(lable1,4,0);
    layout->addWidget(lable2,6,0);
    layout->addWidget(lable3,8,0);
    layout->addWidget(lable4,10,0);
    dialog->setLayout(layout);
    dialog->show();

}

void MainWindow::show_ranking()
{
    QGridLayout *layout=new QGridLayout;
    QDialog *dialog = new QDialog(this);

    QLabel *title1=new QLabel();//title and a horizontal line to divide
    QLabel *title2=new QLabel();
    QLabel *title3=new QLabel();
    QLabel *hor_line=new QLabel();

    QLabel *lable1=new QLabel();
    QLabel *lable2=new QLabel();
    QLabel *lable3=new QLabel();

    //QPushButton *button_rst = new QPushButton("Reset the list");
    QString s1="";
    QString s2="";
    QString s3="";
    QString stitle1="junior";
    QString stitle2="middle";
    QString stitle3="senior";
    QString hl="\n—————————————————————";
    int num1=0,num2=0,num3=0;
    QFile file1("JUNIOR");
    if(!file1.open(QIODevice::ReadOnly|QIODevice::Text))
        qDebug()<<"can't read from junior.txt\n";
    for(int i=0;i<10;i++){
        QByteArray line=file1.readLine();
            QString str(line);
            std::string s = str.toStdString();
            if(!s.empty()){//have data,input it into our ranking list
                s1.append(str);
            }else{
                num1=i;
                break;
            }
        }
    for(int j=10-num1;j<=10;j++){
        s1.append("\n");
    }
    QFile file2("MIDDLE");
    if(!file2.open(QIODevice::ReadOnly|QIODevice::Text))
        qDebug()<<"can't read from middle.txt\n";
    for(int i=0;i<10;i++){
        QByteArray line=file2.readLine();
            QString str(line);
            std::string s = str.toStdString();
            if(!s.empty()){//have data,input it into our ranking list
                s2.append(str);
            }else{
                num2=i;
                break;
            }
        }
    for(int j=10-num2;j<=10;j++){
        s2.append("\n");
    }

    QFile file3("SENIOR");
    if(!file3.open(QIODevice::ReadOnly|QIODevice::Text))
        qDebug()<<"can't read from senior.txt\n";
    for(int i=0;i<10;i++){
        QByteArray line=file3.readLine();
            QString str(line);
            std::string s = str.toStdString();
            if(!s.empty()){//have data,input it into our ranking list
                s3.append(str);
            }else{
                num3=i;
                break;

            }
    }

    for(int j=10-num3;j<=10;j++){
        s3.append("\n");
    }


    title1->setText(stitle1);
    title2->setText(stitle2);
    title3->setText(stitle3);
    hor_line->setText(hl);
    lable1->setText(s1);
    lable2->setText(s2);
    lable3->setText(s3);

    layout->addWidget(title1,1,0,1,3);//title
    layout->addWidget(title2,1,3,1,3);
    layout->addWidget(title3,1,6,1,3);
    layout->addWidget(hor_line,1,0,1,8);

    layout->addWidget(lable1,2,0,Qt::AlignTop);//alignment
    layout->addWidget(lable2,2,3,Qt::AlignTop);
    layout->addWidget(lable3,2,6,Qt::AlignTop);

    //layout->addWidget(button_rst,5,0,1,3);
    dialog->setLayout(layout);
    dialog->setWindowTitle("Ranking");
    dialog->show();
    //setStyleSheet("text-align: top;");
}

void MainWindow::time_initialize()//reset the time
{
    B->set_time(0);
}

void MainWindow::show_win(){
    if((B->get_setting()==JUNIOR)||(B->get_setting()==MIDDLE)||(B->get_setting()==SENIOR)){
        //which have ranking list
        QGridLayout *layout =new QGridLayout;
        QDialog *dialog = new QDialog(this);
        QString s0="Congratulations! You beat this game!";
        QString s1="You use ";
        QString s2=QString::number(B->get_time());
        QString s3="s. Please input your name:";
        s1.append(s2);
        s1.append(s3);
        QLabel *lable0 = new QLabel(s0);
        QLabel *lable1 = new QLabel(s1);
        QLineEdit *edit = new QLineEdit;
        QPushButton *button = new QPushButton("OK");
        layout->addWidget(lable0,0,0);
        layout->addWidget(lable1,2,0,Qt::AlignTop);
        layout->addWidget(edit,2,5,Qt::AlignTop);
        layout->addWidget(button);
        dialog->setLayout(layout);
        dialog->setWindowTitle("WIN");
        dialog->show();
        connect(button,&QPushButton::clicked,this,[=]{
            QString user_name=edit->text();
            std::any param (std::make_any<UserParameter>());
            UserParameter& user= std::any_cast<UserParameter&>(param);
            user.time=B->get_time();
            user.name = user_name.toStdString();

            m_cmd_rank->SetParameter(param);
            m_cmd_rank->Exec();
            dialog->close();
        });
    }else{//customize
        QGridLayout *layout =new QGridLayout;
        QDialog *dialog = new QDialog(this);
        QString s0="Congratulations! You beat this game!";
        QString s1="You use ";
        QString s2=QString::number(B->get_time());
        QString s3="s.";
        s1.append(s2);
        s1.append(s3);
        QLabel *lable1= new QLabel(s1);
        QPushButton *button = new QPushButton("OK");
        QLabel *lable0 = new QLabel(s0);
        layout->addWidget(lable0,0,0);
        layout->addWidget(lable1,2,0,Qt::AlignTop);
        layout->addWidget(button);
        dialog->setLayout(layout);
        dialog->setWindowTitle("WIN");
        dialog->show();
        connect(button,&QPushButton::clicked,this,[=]{
            dialog->close();
        });
    }
}

void MainWindow::set_restart_command(const std::shared_ptr<ICommandBase> &cmd) throw(){
     m_cmd_restart = cmd;
}

void MainWindow::set_leftclick_command(const std::shared_ptr<ICommandBase> &cmd) throw(){
     m_cmd_left = cmd;
}

void MainWindow::set_rightclick_command(const std::shared_ptr<ICommandBase> &cmd) throw(){
	m_cmd_right = cmd;
}

void MainWindow::set_setting_command(const std::shared_ptr<ICommandBase> &cmd) throw(){
    m_cmd_setting = cmd;
}

void MainWindow::set_rank_command(const std::shared_ptr<ICommandBase> &cmd) throw(){
    m_cmd_rank = cmd;
}

std::shared_ptr<IPropertyNotification> MainWindow::get_propertty_sink() throw(){
    return std::static_pointer_cast<IPropertyNotification>(m_sink_property);
}
void MainWindow ::paint_boom(QPainter  * painter){
    QPixmap ele_0(":img/image/ele0.bmp");
    QPixmap ele_1(":img/image/ele1.bmp");
    QPixmap ele_2(":img/image/ele2.bmp");
    QPixmap ele_3(":img/image/ele3.bmp");
    QPixmap ele_4(":img/image/ele4.bmp");
    QPixmap ele_5(":img/image/ele5.bmp");
    QPixmap ele_6(":img/image/ele6.bmp");
    QPixmap ele_7(":img/image/ele7.bmp");
    QPixmap ele_8(":img/image/ele8.bmp");
    QPixmap ele_9(":img/image/ele9.bmp");
    int LENGTH=B->get_col()*21;
    static int num_flag = 0;
    if (B->get_play()){
        num_flag = B->get_flag_num();
    }
    painter->drawPixmap((int)(LENGTH*40)/200-30,5+TITLE_BEGIN,ele_0,0,0,1000,1000);
        switch(num_flag/100){//hundred point
        case 0:  painter->drawPixmap((int)(LENGTH*40)/200-30,5+TITLE_BEGIN,ele_0,0,0,1000,1000);break;
        case 1:  painter->drawPixmap((int)(LENGTH*40)/200-30,5+TITLE_BEGIN,ele_1,0,0,1000,1000);break;
        case 2:  painter->drawPixmap((int)(LENGTH*40)/200-30,5+TITLE_BEGIN,ele_2,0,0,1000,1000);break;
        case 3:  painter->drawPixmap((int)(LENGTH*40)/200-30,5+TITLE_BEGIN,ele_3,0,0,1000,1000);break;
        case 4:  painter->drawPixmap((int)(LENGTH*40)/200-30,5+TITLE_BEGIN,ele_4,0,0,1000,1000);break;
        case 5:  painter->drawPixmap((int)(LENGTH*40)/200-30,5+TITLE_BEGIN,ele_5,0,0,1000,1000);break;
        case 6:  painter->drawPixmap((int)(LENGTH*40)/200-30,5+TITLE_BEGIN,ele_6,0,0,1000,1000);break;
        case 7:  painter->drawPixmap((int)(LENGTH*40)/200-30,5+TITLE_BEGIN,ele_7,0,0,1000,1000);break;
        case 8:  painter->drawPixmap((int)(LENGTH*40)/200-30,5+TITLE_BEGIN,ele_8,0,0,1000,1000);break;
        case 9:  painter->drawPixmap((int)(LENGTH*40)/200-30,5+TITLE_BEGIN,ele_9,0,0,1000,1000);break;
        }

        switch((num_flag/10)%10){
        case 0:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGTH,5+TITLE_BEGIN,ele_0,0,0,1000,1000);break;
        case 1:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGTH,5+TITLE_BEGIN,ele_1,0,0,1000,1000);break;
        case 2:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGTH,5+TITLE_BEGIN,ele_2,0,0,1000,1000);break;
        case 3:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGTH,5+TITLE_BEGIN,ele_3,0,0,1000,1000);break;
        case 4:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGTH,5+TITLE_BEGIN,ele_4,0,0,1000,1000);break;
        case 5:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGTH,5+TITLE_BEGIN,ele_5,0,0,1000,1000);break;
        case 6:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGTH,5+TITLE_BEGIN,ele_6,0,0,1000,1000);break;
        case 7:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGTH,5+TITLE_BEGIN,ele_7,0,0,1000,1000);break;
        case 8:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGTH,5+TITLE_BEGIN,ele_8,0,0,1000,1000);break;
        case 9:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGTH,5+TITLE_BEGIN,ele_9,0,0,1000,1000);break;
        }

        switch (num_flag%10){
        case 0:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGTH+ELENUM_LENGTH,5+TITLE_BEGIN,ele_0,0,0,1000,1000);break;
        case 1:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGTH+ELENUM_LENGTH,5+TITLE_BEGIN,ele_1,0,0,1000,1000);break;
        case 2:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGTH+ELENUM_LENGTH,5+TITLE_BEGIN,ele_2,0,0,1000,1000);break;
        case 3:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGTH+ELENUM_LENGTH,5+TITLE_BEGIN,ele_3,0,0,1000,1000);break;
        case 4:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGTH+ELENUM_LENGTH,5+TITLE_BEGIN,ele_4,0,0,1000,1000);break;
        case 5:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGTH+ELENUM_LENGTH,5+TITLE_BEGIN,ele_5,0,0,1000,1000);break;
        case 6:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGTH+ELENUM_LENGTH,5+TITLE_BEGIN,ele_6,0,0,1000,1000);break;
        case 7:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGTH+ELENUM_LENGTH,5+TITLE_BEGIN,ele_7,0,0,1000,1000);break;
        case 8:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGTH+ELENUM_LENGTH,5+TITLE_BEGIN,ele_8,0,0,1000,1000);break;
        case 9:  painter->drawPixmap((int)(LENGTH*40)/200-30+ELENUM_LENGTH+ELENUM_LENGTH,5+TITLE_BEGIN,ele_9,0,0,1000,1000);break;
        }
}
void MainWindow ::paint_time(QPainter  * painter){
    QPixmap ele_0(":img/image/ele0.bmp");
    QPixmap ele_1(":img/image/ele1.bmp");
    QPixmap ele_2(":img/image/ele2.bmp");
    QPixmap ele_3(":img/image/ele3.bmp");
    QPixmap ele_4(":img/image/ele4.bmp");
    QPixmap ele_5(":img/image/ele5.bmp");
    QPixmap ele_6(":img/image/ele6.bmp");
    QPixmap ele_7(":img/image/ele7.bmp");
    QPixmap ele_8(":img/image/ele8.bmp");
    QPixmap ele_9(":img/image/ele9.bmp");
    int LENGTH=B->get_col()*21;
    static int num_time=0;
    if (B->get_play()){
        num_time = B->get_time();
    }
    switch  (num_time/100){
        case 0:  painter->drawPixmap((int)(LENGTH*163)/200-30,5+TITLE_BEGIN,ele_0,0,0,1000,1000);break;
        case 1:  painter->drawPixmap((int)(LENGTH*163)/200-30,5+TITLE_BEGIN,ele_1,0,0,1000,1000);break;
        case 2:  painter->drawPixmap((int)(LENGTH*163)/200-30,5+TITLE_BEGIN,ele_2,0,0,1000,1000);break;
        case 3:  painter->drawPixmap((int)(LENGTH*163)/200-30,5+TITLE_BEGIN,ele_3,0,0,1000,1000);break;
        case 4:  painter->drawPixmap((int)(LENGTH*163)/200-30,5+TITLE_BEGIN,ele_4,0,0,1000,1000);break;
        case 5:  painter->drawPixmap((int)(LENGTH*163)/200-30,5+TITLE_BEGIN,ele_5,0,0,1000,1000);break;
        case 6:  painter->drawPixmap((int)(LENGTH*163)/200-30,5+TITLE_BEGIN,ele_6,0,0,1000,1000);break;
        case 7:  painter->drawPixmap((int)(LENGTH*163)/200-30,5+TITLE_BEGIN,ele_7,0,0,1000,1000);break;
        case 8:  painter->drawPixmap((int)(LENGTH*163)/200-30,5+TITLE_BEGIN,ele_8,0,0,1000,1000);break;
        case 9:  painter->drawPixmap((int)(LENGTH*163)/200-30,5+TITLE_BEGIN,ele_9,0,0,1000,1000);break;
        }
    switch  ((num_time/10)%10){
        case 0:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGTH,5+TITLE_BEGIN,ele_0,0,0,1000,1000);break;
        case 1:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGTH,5+TITLE_BEGIN,ele_1,0,0,1000,1000);break;
        case 2:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGTH,5+TITLE_BEGIN,ele_2,0,0,1000,1000);break;
        case 3:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGTH,5+TITLE_BEGIN,ele_3,0,0,1000,1000);break;
        case 4:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGTH,5+TITLE_BEGIN,ele_4,0,0,1000,1000);break;
        case 5:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGTH,5+TITLE_BEGIN,ele_5,0,0,1000,1000);break;
        case 6:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGTH,5+TITLE_BEGIN,ele_6,0,0,1000,1000);break;
        case 7:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGTH,5+TITLE_BEGIN,ele_7,0,0,1000,1000);break;
        case 8:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGTH,5+TITLE_BEGIN,ele_8,0,0,1000,1000);break;
        case 9:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGTH,5+TITLE_BEGIN,ele_9,0,0,1000,1000);break;
        }
    switch  (num_time%10){
        case 0:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGTH+ELENUM_LENGTH,5+TITLE_BEGIN,ele_0,0,0,1000,1000);break;
        case 1:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGTH+ELENUM_LENGTH,5+TITLE_BEGIN,ele_1,0,0,1000,1000);break;
        case 2:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGTH+ELENUM_LENGTH,5+TITLE_BEGIN,ele_2,0,0,1000,1000);break;
        case 3:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGTH+ELENUM_LENGTH,5+TITLE_BEGIN,ele_3,0,0,1000,1000);break;
        case 4:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGTH+ELENUM_LENGTH,5+TITLE_BEGIN,ele_4,0,0,1000,1000);break;
        case 5:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGTH+ELENUM_LENGTH,5+TITLE_BEGIN,ele_5,0,0,1000,1000);break;
        case 6:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGTH+ELENUM_LENGTH,5+TITLE_BEGIN,ele_6,0,0,1000,1000);break;
        case 7:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGTH+ELENUM_LENGTH,5+TITLE_BEGIN,ele_7,0,0,1000,1000);break;
        case 8:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGTH+ELENUM_LENGTH,5+TITLE_BEGIN,ele_8,0,0,1000,1000);break;
        case 9:  painter->drawPixmap((int)(LENGTH*163)/200-30+ELENUM_LENGTH+ELENUM_LENGTH,5+TITLE_BEGIN,ele_9,0,0,1000,1000);break;
        }
}


//draw the boom_num,emoji,time and background
void MainWindow :: paint_title(QPainter  * painter){
    int LENGTH=B->get_col()*21;

    QPixmap mine_title(":img/image/mine_title.bmp");
    QPixmap lose(":img/image/lose.bmp");
    QPixmap win(":img/image/win.bmp");
    QPixmap smile(":img/image/smile.bmp");

    int restart_x=(int)B->get_col()*21*100/200-11;
    mine_title=mine_title.scaled(QSize(B->get_col()*21,40));
    painter->drawPixmap(0,TITLE_BEGIN,mine_title,0,0,1000,1000);
    if (B->get_win()){
        painter->drawPixmap(restart_x, 30, win, 0, 0, 1000, 1000);
    }else if (B->get_lose()) {
        painter->drawPixmap(restart_x, 30, lose, 0, 0, 1000, 1000);
    }else{
        painter->drawPixmap(restart_x, 30, smile, 0, 0, 1000, 1000);
    }
    paint_boom(painter);
    paint_time(painter);

}

void MainWindow :: paintEvent(QPaintEvent * event){
    QPainter painter(this);
    paint_my_window=&painter;
	int click_i, click_j;
    click_i = (click_y - TITLE_HEIGHT) / BLOCK_HEIGHT;
    click_j = click_x / BLOCK_LENGTH;
    QPixmap blk_1(":img/image/blk1.bmp");
    QPixmap blk_2(":img/image/blk2.bmp");
    QPixmap blk_3(":img/image/blk3.bmp");
    QPixmap blk_4(":img/image/blk4.bmp");
    QPixmap blk_5(":img/image/blk5.bmp");
    QPixmap blk_6(":img/image/blk6.bmp");
    QPixmap blk_7(":img/image/blk7.bmp");
    QPixmap blk_8(":img/image/blk8.bmp");
    QPixmap block_close(":img/image/block_close.bmp");
    QPixmap block_open(":img/image/block_open.bmp");
    QPixmap red_flag(":img/image/redflag.bmp");
    QPixmap click_boom(":img/image/clickboom.bmp");
    QPixmap boom(":img/image/boom.bmp");   
    QPixmap mark(":img/image/unknow.jpg");

    if(paint_flag==0){//paint the original map
        paint_title(paint_my_window);
        for(int i=0;i<B->get_row()*BLOCK_LENGTH;i+=BLOCK_LENGTH){
            for(int j=TITLE_HEIGHT;j<B->get_col()*BLOCK_HEIGHT+TITLE_HEIGHT;j+=BLOCK_HEIGHT)
                painter.drawPixmap(i,j,block_close,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);
        }
        paint_flag=1;
    }else{
        paint_title(paint_my_window);
        if(B->get_play()==true)
		{
            if(B->get_cheat()){
                for(int i=0;i<B->get_row();i++){
                    for(int j=0;j<B->get_col();j++){
                        if(B->p[i][j].get_show()==0){//unvisited
                            if(B->p[i][j].get_boom())
                                painter.drawPixmap(j*BLOCK_LENGTH, i*BLOCK_HEIGHT + TITLE_HEIGHT, boom, 0, 0, BLOCK_LENGTH, BLOCK_HEIGHT);
                            else if (B->p[i][j].get_flag())
                                painter.drawPixmap(j*BLOCK_LENGTH, i*BLOCK_HEIGHT + TITLE_HEIGHT, red_flag, 0, 0, BLOCK_LENGTH, BLOCK_HEIGHT);
                            else if (B->p[i][j].get_mark())
                                painter.drawPixmap(j*BLOCK_LENGTH, i*BLOCK_HEIGHT + TITLE_HEIGHT, mark, 0, 0, BLOCK_LENGTH, BLOCK_HEIGHT);
                            else{
                                painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,block_close,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);
                            }
                        } else{
                            if(B->p[i][j].get_boom()){
                                painter.drawPixmap(j*BLOCK_LENGTH, i*BLOCK_HEIGHT + TITLE_HEIGHT, boom, 0, 0, BLOCK_LENGTH, BLOCK_HEIGHT);
                            }else{
                                switch(B->p[i][j].get_sur()){
                                    case 0:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,block_open,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
                                    case 1:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,blk_1,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
                                    case 2:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,blk_2,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
                                    case 3:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,blk_3,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
                                    case 4:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,blk_4,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
                                    case 5:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,blk_5,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
                                    case 6:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,blk_6,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
                                    case 7:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,blk_7,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
                                    case 8:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,blk_8,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
                                }
                            }
                        }
                    }
                }

            }else{
                for(int i=0;i<B->get_row();i++){
                    for(int j=0;j<B->get_col();j++){
                        if(B->p[i][j].get_show()==0){
                            if (B->p[i][j].get_flag())
                                painter.drawPixmap(j*BLOCK_LENGTH, i*BLOCK_HEIGHT + TITLE_HEIGHT, red_flag, 0, 0, BLOCK_LENGTH, BLOCK_HEIGHT);
                            else if (B->p[i][j].get_mark())
                                painter.drawPixmap(j*BLOCK_LENGTH, i*BLOCK_HEIGHT + TITLE_HEIGHT, mark, 0, 0, BLOCK_LENGTH, BLOCK_HEIGHT);
                            else
                                painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,block_close,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);
                        } else{
                            if(B->p[i][j].get_boom()){
                                painter.drawPixmap(j*BLOCK_LENGTH, i*BLOCK_HEIGHT + TITLE_HEIGHT, boom, 0, 0, BLOCK_LENGTH, BLOCK_HEIGHT);
                            } else{
                                switch(B->p[i][j].get_sur()){
                                    case 0:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,block_open,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
                                    case 1:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,blk_1,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
                                    case 2:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,blk_2,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
                                    case 3:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,blk_3,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
                                    case 4:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,blk_4,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
                                    case 5:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,blk_5,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
                                    case 6:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,blk_6,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
                                    case 7:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,blk_7,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
                                    case 8:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,blk_8,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
                                }
                            }
                        }
                    }
                }
            }
        }else if(B->get_win()){
            for(int i=0;i<B->get_row();i++)
                for(int j=0;j<B->get_col();j++){
                    if(B->p[i][j].get_flag())
                        painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,red_flag,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);
                    else{
                        switch(B->p[i][j].get_sur()){
							case 0:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,block_open,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
							case 1:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,blk_1,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
							case 2:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,blk_2,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
							case 3:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,blk_3,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
							case 4:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,blk_4,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
							case 5:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,blk_5,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
							case 6:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,blk_6,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
							case 7:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,blk_7,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
							case 8:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,blk_8,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
						}
					}
				}
        }else if(B->get_lose()){
			for(int i=0;i<B->get_row();i++)
                for(int j=0;j<B->get_col();j++){
                    if(B->p[i][j].get_flag())
						painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,red_flag,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);
                    else if(B->p[i][j].get_boom()){
						painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,boom,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);
                    }else{
                        switch(B->p[i][j].get_sur()){
							case 0:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,block_open,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
							case 1:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,blk_1,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
							case 2:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,blk_2,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
							case 3:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,blk_3,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
							case 4:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,blk_4,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
							case 5:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,blk_5,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
							case 6:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,blk_6,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
							case 7:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,blk_7,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
							case 8:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,blk_8,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);break;
						}
					}
				}

			static int x, y;
            if (B->get_lock()){
                painter.drawPixmap(x, y, click_boom, 0, 0, BLOCK_LENGTH, BLOCK_HEIGHT);
            }else{
                painter.drawPixmap(click_j*BLOCK_LENGTH, click_i*BLOCK_HEIGHT + TITLE_HEIGHT, click_boom, 0, 0, BLOCK_LENGTH, BLOCK_HEIGHT);
                x = click_j * BLOCK_LENGTH;
                y = click_i * BLOCK_HEIGHT + TITLE_HEIGHT;
			}			
        }
    }   
}



void MainWindow ::mousePressEvent(QMouseEvent * event)
{
   click_x=event->x();
   click_y=event->y();
   int restart_x=(int)B->get_col()*21*100/200-11;
   //if(false)
   if(event->buttons()==(Qt::LeftButton)&&(click_x>restart_x)&&(click_x<55+restart_x)&&(click_y>30)&&(click_y<55)){
       std::any param1 (std::make_any<BlockParameter>());
       BlockParameter& ts= std::any_cast<BlockParameter&>(param1);
       ts.row = B->get_row();
       ts.col = B->get_col();
       ts.boom_num = B->get_boom_num();
       m_cmd_restart->SetParameter(param1);
       m_cmd_restart->Exec();
   }
   if(B->get_play()){
       if(event->buttons()==(Qt::LeftButton))
           if(click_x>0)
               if(click_x<B->get_col()*BLOCK_LENGTH)
                   if(click_y>TITLE_HEIGHT)
                       if(click_y<B->get_row()*BLOCK_HEIGHT+TITLE_HEIGHT)
       {
           std::any param2 (std::make_any<PosParameter>());
           PosParameter& pos= std::any_cast<PosParameter&>(param2);
           pos.j=click_x/BLOCK_LENGTH;
           pos.i=(click_y-TITLE_HEIGHT)/BLOCK_HEIGHT;
           m_cmd_left->SetParameter(param2);
           m_cmd_left->Exec();
       }
       if(event->buttons()==(Qt::RightButton))
           if(click_x>0)
               if(click_x<B->get_col()*BLOCK_LENGTH)
                   if(click_y>TITLE_HEIGHT)
                       if(click_y<B->get_row()*BLOCK_HEIGHT + TITLE_HEIGHT)
        {
           std::any param3 (std::make_any<PosParameter>());
           PosParameter& pos= std::any_cast<PosParameter&>(param3);
           pos.j=click_x/BLOCK_LENGTH;
           pos.i=(click_y-TITLE_HEIGHT)/BLOCK_HEIGHT;
           m_cmd_right->SetParameter(param3);
           m_cmd_right->Exec();
       }
   }
}

void MainWindow ::set_block(const std:: shared_ptr<Block> b)
{
    this->B=b;
}


