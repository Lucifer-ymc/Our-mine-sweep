#include "mainwindow.h"
#include "ui_mainwindow.h"
int BLOCK_LENGTH=21;
int BLOCK_HEIGHT=21;
int TITLE_HEIGHT=63;
int TITLE_BEGIN=23;
int ELENUM_LENGTH=20;
QPainter *paint_my_window;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_sink_property(std::make_shared<MainWindowPropertySink>(this))

{
    ui->setupUi(this);
    connect(ui->actionCustom,SIGNAL(triggered(bool)),this,SLOT(set_custom()));
    runtime=new QTimer(this);
    runtime->start(1000);
    connect(runtime,SIGNAL(timeout()),this,SLOT(update()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    int LENGTH=B->get_col()*21;
    int HEIGHT=B->get_row()*21+63;
    this->setMinimumSize(LENGTH,HEIGHT);
    this->setMaximumSize(LENGTH*2,HEIGHT*2);
    this->resize(LENGTH,HEIGHT);
}

void MainWindow::set_custom()
{
    QHBoxLayout *layout =new QHBoxLayout;
    QDialog *dialog = new QDialog(this);
    QString s1="Row:";
    QString s2="Col:";
    QString s3="Number of booms:";
    QLabel *lable1= new QLabel(s1);
    QLabel *lable2= new QLabel(s2);
    QLabel *lable3= new QLabel(s3);
    QLineEdit *edit1 = new QLineEdit;
    QLineEdit *edit2 = new QLineEdit;
    QLineEdit *edit3 = new QLineEdit;
    QPushButton *button = new QPushButton("OK");
    layout->addWidget(lable1);
    layout->addWidget(edit1);
    layout->addWidget(lable2);
    layout->addWidget(edit2);
    layout->addWidget(lable3);
    layout->addWidget(edit3);
    layout->addWidget(button);
    dialog->setLayout(layout);
    dialog->setWindowTitle("Custom");
    dialog->show();
    connect(button,&QPushButton::clicked,this,[=]{
        QString str1=edit1->text();
        QString str2=edit2->text();
        QString str3=edit3->text();
        int row=str1.toInt();
        int col=str2.toInt();
        int boom_num=str3.toInt();
        dialog->close();
    });
}

void MainWindow::time_init()
{
    B->set_time(0);
}

void MainWindow::show_win()
{
        QVBoxLayout *layout =new QVBoxLayout;
        QDialog *dialog = new QDialog(this);
        QString s1="Congratulations! You use ";
        QString s2=QString::number(B->get_time());
        QString s3="s";
        s1.append(s2);
        s1.append(s3);
        QLabel *lable= new QLabel(s1);
        QPushButton *button = new QPushButton("OK");
        layout->addWidget(lable);
        layout->addWidget(button);
        dialog->setLayout(layout);
        dialog->setWindowTitle("WIN");
        dialog->show();
        connect(button,&QPushButton::clicked,this,[=]{
            dialog->close();
        });

}

void MainWindow::set_restart_command(const std::shared_ptr<ICommandBase> &cmd) throw()
{
     m_cmd_restart = cmd;
}
void MainWindow::set_leftblock_command(const std::shared_ptr<ICommandBase> &cmd) throw()
{
     m_cmd_left = cmd;
}
void MainWindow::set_rightblock_command(const std::shared_ptr<ICommandBase> &cmd) throw()
{
	m_cmd_right = cmd;
}
std::shared_ptr<IPropertyNotification> MainWindow::get_propertty_sink() throw()
{
    return std::static_pointer_cast<IPropertyNotification>(m_sink_property);
}

void MainWindow :: paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    paint_my_window=&painter;
	int click_i, click_j;
	click_j = click_x / BLOCK_LENGTH;
	click_i = (click_y - TITLE_HEIGHT) / BLOCK_HEIGHT;
    QPixmap block_close(":img/image/block_close.bmp");
    QPixmap block_open(":img/image/block_open.bmp");
    QPixmap red_flag(":img/image/redflag.bmp");
    QPixmap keil_boom(":img/image/keilboom.bmp");
    QPixmap click_boom(":img/image/clickboom.bmp");
    QPixmap boom(":img/image/boom.bmp");
    QPixmap blk_1(":img/image/blk1.bmp");
    QPixmap blk_2(":img/image/blk2.bmp");
    QPixmap blk_3(":img/image/blk3.bmp");
    QPixmap blk_4(":img/image/blk4.bmp");
    QPixmap blk_5(":img/image/blk5.bmp");
    QPixmap blk_6(":img/image/blk6.bmp");
    QPixmap blk_7(":img/image/blk7.bmp");
    QPixmap blk_8(":img/image/blk8.bmp");
    QPixmap mark(":img/image/unknow.jpg");
    if(paint_flag==0){
        paint_title(paint_my_window);
        for(int i=0;i<B->get_row()*BLOCK_LENGTH;i+=BLOCK_LENGTH){
            for(int j=TITLE_HEIGHT;j<B->get_col()*BLOCK_HEIGHT+TITLE_HEIGHT;j+=BLOCK_HEIGHT)
                painter.drawPixmap(i,j,block_close,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);
        }
        paint_flag=1;
    }
    else
	{
        paint_title(paint_my_window);
        if(B->get_play()==true)
		{
                for(int i=0;i<B->get_row();i++){
                    for(int j=0;j<B->get_col();j++){
                        if(B->p[i][j].get_show()==false){
                            if (B->p[i][j].get_flag() == true)
                                painter.drawPixmap(j*BLOCK_LENGTH, i*BLOCK_HEIGHT + TITLE_HEIGHT, red_flag, 0, 0, BLOCK_LENGTH, BLOCK_HEIGHT);
                            else if (B->p[i][j].get_mark() == true)
                                painter.drawPixmap(j*BLOCK_LENGTH, i*BLOCK_HEIGHT + TITLE_HEIGHT, mark, 0, 0, BLOCK_LENGTH, BLOCK_HEIGHT);
                            else painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,block_close,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);
                        }
                        else{
                            if(B->p[i][j].get_boom()==true){
                                painter.drawPixmap(j*BLOCK_LENGTH, i*BLOCK_HEIGHT + TITLE_HEIGHT, boom, 0, 0, BLOCK_LENGTH, BLOCK_HEIGHT);
                            }
                            else{
                                switch(B->p[i][j].get_sur())
                                {
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
        else if(B->get_win()==true)
		{
            for(int i=0;i<B->get_row();i++)
                for(int j=0;j<B->get_col();j++)
				{
                    if(B->p[i][j].get_flag()==true)
                        painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,red_flag,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);
                    else
					{
                        switch(B->p[i][j].get_sur())
                        {
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
        else if(B->get_lose()==true)
		{
			for(int i=0;i<B->get_row();i++)
				for(int j=0;j<B->get_col();j++)
				{
					if(B->p[i][j].get_flag()==true)
						painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,red_flag,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);
					else if(B->p[i][j].get_boom()==true)
					{
						painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGHT+TITLE_HEIGHT,boom,0,0,BLOCK_LENGTH,BLOCK_HEIGHT);
					}
					else
					{
						switch(B->p[i][j].get_sur())
						{
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
			if (B->get_lock() == false)
			{
				painter.drawPixmap(click_j*BLOCK_LENGTH, click_i*BLOCK_HEIGHT + TITLE_HEIGHT, click_boom, 0, 0, BLOCK_LENGTH, BLOCK_HEIGHT);
				x = click_j * BLOCK_LENGTH;
				y = click_i * BLOCK_HEIGHT + TITLE_HEIGHT;
			}
			else
			{
				painter.drawPixmap(x, y, click_boom, 0, 0, BLOCK_LENGTH, BLOCK_HEIGHT);
			}
			
        }
    }
    
}

void MainWindow :: paint_title(QPainter  * painter)
{
    int LENGTH=B->get_col()*21;
    QPixmap mine_title(":img/image/mine_title.bmp");
    QPixmap qq_lose(":img/image/lose.bmp");
    QPixmap qq_pround(":img/image/proud.bmp");
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
    QPixmap ele_10(":img/image/ele10.bmp");
    QPixmap restart(":img/image/smile.bmp");
    int restart_x=(int)B->get_col()*21*100/200-11;
    mine_title=mine_title.scaled(QSize(B->get_col()*21,40));
    painter->drawPixmap(0,TITLE_BEGIN,mine_title,0,0,1000,1000);
	if (B->get_win() == true)
		painter->drawPixmap(restart_x, 30, qq_pround, 0, 0, 1000, 1000);
	else if (B->get_lose() == true) {
		painter->drawPixmap(restart_x, 30, qq_lose, 0, 0, 1000, 1000);
	}
	else
	{
		painter->drawPixmap(restart_x, 30, restart, 0, 0, 1000, 1000);
	}
	static int redflagnum = 0;
	if (B->get_play() == true)
	{
		redflagnum = B->get_flag_num();
	}
    if(redflagnum<0)
        {
            redflagnum = -redflagnum;
            painter->drawPixmap((int)(LENGTH*40)/200-30,5+TITLE_BEGIN,ele_10,0,0,1000,1000);
        }
    else painter->drawPixmap((int)(LENGTH*40)/200-30,5+TITLE_BEGIN,ele_0,0,0,1000,1000);
        switch(redflagnum/10)
        {
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
        switch (redflagnum%10)
        {
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
    static int timenum=0;
	if (B->get_play() == true)
	{
		timenum = B->get_time();
	}
        switch  (timenum/100)
        {
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
        switch  ((timenum/10)%10)
        {
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
        switch  (timenum%10)
        {
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

void MainWindow ::mousePressEvent(QMouseEvent * event)
{
   click_x=event->x();
   click_y=event->y();
   int restart_x=(int)B->get_col()*21*100/200-11;
   //if(false)
   if(event->buttons()==(Qt::LeftButton)&&(click_x>restart_x)&&(click_x<55+restart_x)&&(click_y>30)&&(click_y<55))
   {
       qDebug()<<"RESTART";
       //qDebug()<<"x:"<<click_x<<", y"<<click_y;
       std::any param1 (std::make_any<BlockParameter>());
       BlockParameter& ts= std::any_cast<BlockParameter&>(param1);
       ts.row = B->get_row();
       ts.col = B->get_col();
       ts.boom_num = B->get_boom_num();
       m_cmd_restart->SetParameter(param1);
       m_cmd_restart->Exec();
       //update();
   }
   if(B->get_play()==true)
   {
       if(event->buttons()==(Qt::LeftButton))
           if(click_x>0)
               if(click_x<B->get_col()*BLOCK_LENGTH)
                   if(click_y>TITLE_HEIGHT)
                       if(click_y<B->get_row()*BLOCK_HEIGHT+TITLE_HEIGHT)
       {
           //qDebug()<<"left_button";
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
           //qDebug()<<"right_button";
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


