#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Subfiles.h"
#include<QPushButton>
#include<iostream>
#include<QVector>
#include<QTimer>
using namespace std;
string str[64];
    static int n=0;
    int nn=0;//hang
    static int ttime=0;
    LRC *head;
    bool t_play=true;
    int flag_yin=50;
    int percent_pos = 0;
    float time_pos=0;
    static int flag_sui=0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //bianli();
    //ci
    qiege();
    set_zhuanji();
    //settile();
    this->slider=new QSlider(this);
    this->slider->setOrientation(Qt::Horizontal);
    this->slider->setGeometry(140,420,400,10);
    this->slider->setMinimum(0);
    this->slider->setMaximum(100);
    this->slider->setSingleStep(10);
    this->slider->setStyleSheet("font: bold; font-size:20px; color: green; background-color: red;border-radius:5px;border-width: 1px");
    connect(this->slider,SIGNAL(valueChanged(int)),this,SLOT(sider_press(int)));
    /*
    font: bold; 是否粗体显示
    border-image:""; 用来设定边框的背景图片。
    border-radius:5px; 用来设定边框的弧度。可以设定圆角的按钮
    border-width: 1px； 边框大小
    font-family:""; 来设定字体所属家族，
    font-size:20px; 来设定字体大小
    font-style:""; 来设定字体样式
    font-weight:20px; 来设定字体深浅
     background-color: green; 设置背景颜色
    background:transparent; 设置背景为透明
    color:rgb(241, 70, 62); 设置前景颜色
    selection-color:rgb(241, 70, 62); 用来设定选中时候的颜色

    */

    this->label_time1=new QLabel(this);
    this->label_time2=new QLabel(this);
    this->label_time3=new QLabel(this);
    this->label_time2->setGeometry(580,420,20,20);
    this->label_time3->setGeometry(600,420,20,20);
    //bj
    set_bj();
    //button  playr
    this->play=new QPushButton(this);
    this->play->setGeometry(310,460,60,50);
    this->play->clearMask();
    this->play->setStyleSheet("border-image:url(:/imige/pause.png)");
    connect(this->play,SIGNAL(pressed()),this,SLOT(play_press()));

    //button next
    this->next=new QPushButton(this);
    this->next->setGeometry(400,460,60,50);
    this->next->clearMask();
    this->next->setStyleSheet("border-image:url(:/imige/front1.png)");
    connect(this->next,SIGNAL(pressed()),this,SLOT(next_press()));


    //button jin
    this->jin=new QPushButton(this);
    this->jin->setGeometry(480,460,60,50);
    this->jin->clearMask();
    this->jin->setStyleSheet("border-image:url(:/imige/button-foward.png)");
    connect(this->jin,SIGNAL(pressed()),this,SLOT(jin_press()));

    //button tui
    this->tui=new QPushButton(this);
    this->tui->setGeometry(160,460,60,50);
    this->tui->clearMask();
    this->tui->setStyleSheet("border-image:url(:/imige/button-rewind.png)");
    connect(this->tui,SIGNAL(pressed()),this,SLOT(tui_press()));
    //button front
    this->front=new QPushButton(this);
    this->front->setGeometry(240,460,60,50);
    this->front->clearMask();
    this->front->setStyleSheet("border-image:url(:/imige/back1.png)");
    connect(this->front,SIGNAL(pressed()),this,SLOT(front_press()));

    //button yin
    this->yin=new QPushButton(this);
    this->yin->setGeometry(690,410,40,40);
    this->yin->clearMask();
    this->yin->setStyleSheet("border-image:url(:/imige/shengyin.png)");

    connect(this->yin,SIGNAL(pressed()),this,SLOT(yin_press()));
    //listwidget
    this->listWidget=new QListWidget(this);
    this->listWidget->setGeometry(790,30,200,350);
    this->listWidget->setHidden(80);
    this->listWidget->setStyleSheet("QToolButton{background-color:transparent}");
    connect(this->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(list_press()));

    //pushbutton
    ui->pushButton->setGeometry(940,395,40,40);
    ui->pushButton->setText("目录");
    //ui->pushButton->clearMask();
    ui->pushButton->setStyleSheet("border-image:url(:/imige/mulu.png)");
    //ci show
    this->label_lrc=new QLabel(this);
    this->label_lrc->setGeometry(200,200,700,100);
    this->label_lrcc=new QLabel(this);
    this->label_lrcc->setGeometry(200,240,700,100);
    QPalette pt;
    pt.setColor(QPalette::WindowText, Qt::blue); //color
    this->label_time2->setPalette(pt);
    this->label_time3->setPalette(pt);
    QPalette pt1;
    pt1.setColor(QPalette::WindowText, Qt::white); //color
    QFont font("Microsoft YaHei",20,63);
    this->label_lrc->setFont(font);
    this->label_lrcc->setFont(font);
    this->label_lrc->show();
    this->label_lrcc->show();
    this->label_lrc->setPalette(pt1);
    this->label_lrcc->setPalette(pt);

    //ci dainji
    this->ci_bt=new QPushButton(this);
    this->ci_bt->setGeometry(870,410,40,40);
    this->ci_bt->setText("词");
    connect(this->ci_bt,SIGNAL(pressed()),this,SLOT(ci_labe()));

    QTimer *timer = new QTimer(this);
    ttime=0;
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);

    //title
    this->title=new QLabel(this);
    this->title->setGeometry(200,100,700,100);
    this->title->setFont(font);
    settile();


    //yin volume

    this->yin_sider=new QSlider(this);
    this->yin_sider->setOrientation(Qt::Horizontal);
    this->yin_sider->setGeometry(750,420,100,10);
    this->yin_sider->setMinimum(0);
    this->yin_sider->setMaximum(100);
    this->yin_sider->setValue(flag_yin);
    this->yin_sider->setStyleSheet("font: bold; font-size:20px; color: green; background-color: red;border-radius:5px;border-width: 1px");
    connect(this->yin_sider,SIGNAL(valueChanged(int)),this,SLOT(slideryin_press(int)));
    this->l_zhuanji->hide();


}

void *deal_fun2(void *arg)
{
    int fifo_fd = *(int *)arg ;

    //不停的给fifo_cmd发送获取当前时间以及进度
    while(1)
    {

        if(t_play==true)
        {

            usleep(500*1000);//0.5秒发指令
            write(fifo_fd,"get_percent_pos\n", strlen("get_percent_pos\n"));
            usleep(500*1000);//0.5秒发指令
            write(fifo_fd,"get_time_pos\n", strlen("get_time_pos\n"));
        }
        else
            continue;

    }
    close(fifo_fd);
}

void *deal_fun(void *arg)
{
    DATA *p_data =  (DATA *)arg;
    srand(time(NULL));

    while(1)
    {
        char buf[128]="";
        read(p_data->read_fd, buf,sizeof(buf));
        //printf("buf=%s\n", buf);

        char cmd[128]="";
        sscanf(buf,"%[^=]",cmd);
        if(strcmp(cmd,"ANS_PERCENT_POSITION") == 0)//百分比
        {

            sscanf(buf,"%*[^=]=%d", &percent_pos);
           // printf("\r当前的百分比为:%%%d \t", percent_pos);
             p_data->p_w->slider->setValue(percent_pos);
            if(percent_pos>98)
            {

                     p_data->p_w->next_press();

            }

        }
        else if(strcmp(cmd,"ANS_TIME_POSITION") == 0)//当前时间
        {

            sscanf(buf,"%*[^=]=%f", &time_pos);
            printf("当前的时间为:%02d:%02d", (int)(time_pos+0.5)/60, (int)(time_pos+0.5)%60);
            p_data->p_w->label_time2->setText(QString::number((int)(time_pos+0.5)/60));
            p_data->p_w->label_time3->setText(QString::number((int)(time_pos+0.5)%60));

            //p_data->p_w->connect(p_data->p_w->ci_bt,SIGNAL(pressed()),p_data->p_w,SLOT(ci_press(vaule)));


        }


        fflush(stdout);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::bianli()
{

    //打开文件目录
    DIR *dir;
    struct dirent *ent=NULL;
    dir = opendir("/home/edu/work/mplayer01/song");

    buf_photos = new char*[2048];


    //不停的读取文件目录
    if(dir==NULL)
    {
        perror(" ");
    }
    nn=0;
    while(1)
    {
        ent = readdir(dir);
        if(ent == NULL)
                break;
        if(strcmp(ent->d_name,".")==0 || strcmp(ent->d_name,"..")==0)
                continue;
        if(ent->d_type==DT_REG)
        {
            buf_photos[nn++] = ent->d_name;

           qDebug()<<buf_photos[nn-1]<<n<<nn;
        }


    }
    //n=this->listWidget->count();
    closedir(dir);
}

QString MainWindow::str2qstr(const string str)
{
    return QString::fromLocal8Bit(str.data());
}

string MainWindow::qstr2str(const QString qstr)
{
    QByteArray cdata=qstr.toLocal8Bit();
    return string(cdata);
}
#if 1
void MainWindow::on_pushButton_clicked()
{

    if(flag1==0)
    {
        this->listWidget->show();

        flag1=1;
    }else if(flag1==1)
    {
        this->listWidget->hide();
        flag1=0;
    }
    this->listWidget->clear();
    //打开文件目录
    DIR *dir;
    struct dirent *ent=NULL;
    dir = opendir("/home/edu/work/mplayer01/song");
   //不停的读取文件目录
    if(dir==NULL)
    {
        perror(" ");
    }
    nn=0;
    while(1)
    {
        ent = readdir(dir);
        if(ent == NULL)
                break;
        if(strcmp(ent->d_name,".")==0 || strcmp(ent->d_name,"..")==0)
                continue;
        if(ent->d_type==DT_REG)
        {
            QListWidgetItem *item = new QListWidgetItem;
            item->setText(ent->d_name); //逐个设置列表项的文本
            this->listWidget->addItem(item);      //加载列表项到列表框
        }


    }
    closedir(dir);

}

void MainWindow::sider_press(int vaule)
{

    //printf("%d\n",vaule);
    int fifo_fd = open("fifo_cmd",O_WRONLY);
    int jindu= vaule-percent_pos;
    char buf[24]="";

    sprintf(buf,"%s%d%s","seek ",jindu,"\n");
     write(fifo_fd,buf, strlen(buf));
}

void MainWindow::next_press()
{
    bianli();
    this->l_zhuanji->hide();
   // qDebug()<<buf_photos[n];
     printf("%d",n);
    if(n>=0&&n<nn-1){

        n++;
        char str[128]="";
        sprintf(str,"%s%s%s","loadfile /home/edu/work/mplayer01/song/",buf_photos[n],"\n");
        //qDebug()<<str;
        int fifo_fd = open("fifo_cmd",O_WRONLY);

         usleep(1000);
         write(fifo_fd,str, strlen(str)); 
         //printf("tt%d",ttime);
         settile();
    }else
    {
        n=0;
        char str[128]="";
        sprintf(str,"%s%s%s","loadfile /home/edu/work/mplayer01/song/",buf_photos[n],"\n");
        printf("%S",str);
        int fifo_fd = open("fifo_cmd",O_WRONLY);
         usleep(1000);
        write(fifo_fd,str, strlen(str));        
    }
    settile();
    qiege();
    ttime=0;
    set_bj();
    set_zhuanji();
//this->title->setText(buf_photos[n]);
}

void MainWindow::front_press()
{
     bianli();
    this->l_zhuanji->hide();
    if(n>0&&n<=nn){

        n--;
        char str[128]="";
        sprintf(str,"%s%s%s","loadfile /home/edu/work/mplayer01/song/",buf_photos[n],"\n");

        int fifo_fd = open("fifo_cmd",O_WRONLY);
        usleep(1000);
        write(fifo_fd,str, strlen(str));        
    }else
    {
        n=nn-1;
        char str[128]="";
        sprintf(str,"%s%s%s","loadfile /home/edu/work/mplayer01/song/",buf_photos[n],"\n");

        int fifo_fd = open("fifo_cmd",O_WRONLY);
        usleep(1000);
        write(fifo_fd,str, strlen(str));

    }
    settile();
    qiege();
    ttime=0;
    set_bj();
    set_zhuanji();
}

void MainWindow::jin_press()
{
    int fifo_fd = open("fifo_cmd",O_WRONLY);
    write(fifo_fd,"seek 10\n", strlen("seek 10\n"));
}

void MainWindow::tui_press()
{
    int fifo_fd = open("fifo_cmd",O_WRONLY);
    write(fifo_fd,"seek -10\n", strlen("seek -10\n"));
}

void MainWindow::play_press()
{
#if 1

    if(t_play==true)
    {
       this->play->setStyleSheet("border-image:url(:/imige/pause.png)");
       t_play=false;
    }
    else if(t_play==false)
    {
        this->play->setStyleSheet("border-image:url(:/imige/play.png)");
        t_play=true;
    }
    //pthread_mutex_lock(&mutex);
    int fifo_fd = open("fifo_cmd",O_WRONLY);
    write(fifo_fd,"pause\n", strlen("pause\n"));
    //pthread_mutex_unlock(&mutex);
    //usleep(100000);
#endif



}

void MainWindow::yin_press()
{
    int fifo_fd = open("fifo_cmd",O_WRONLY);
    if(flag2==0)
    {
        write(fifo_fd,"mute 1\n", strlen("mute 1\n"));
        this->yin->setStyleSheet("border-image:url(:/imige/Gnome-Audio-Volume-Muted-64.png)");
        flag2=1;
    }else if(flag2==1)
    {
        write(fifo_fd,"mute 0\n", strlen("mute 0\n"));
        this->yin->setStyleSheet("border-image:url(:/imige/shengyin.png)");
        flag2=0;
    }
}

void MainWindow::list_press()
{
        //bianli();
        qiege();
        settile();
        this->l_zhuanji->hide();
        n=this->listWidget->currentRow();
        //this->listWidget->item(n)->setBackgroundColor("red");
        //printf("%d",n);
        ttime=0;
        set_bj();
        //printf("tt%d",ttime);
        settile();
        set_zhuanji();
        char str[1024]="";
        sprintf(str,"%s%s%s","loadfile /home/edu/work/mplayer01/song/",buf_photos[n],"\n");
        printf("%s",buf_photos[n]);

        int fifo_fd = open("fifo_cmd",O_WRONLY);

        usleep(1000);
        write(fifo_fd,str, strlen(str));

}


void MainWindow::update()
{

    if((int)(time_pos+0.5)==head->time)
    {

     ci_init(head->lrc);
     ci_initt(head->next->lrc);
     head=head->next;
    }
    else
        return;

}

void MainWindow::ci_labe()
{
    if(flag3==0)
    {
        this->label_lrc->hide();
        this->label_lrcc->hide();
        this->l_zhuanji->show();
        this->ci_bt->setText("词");
        flag3=1;
    }else if(flag3==1)
    {
        this->l_zhuanji->hide();
        this->label_lrc->show();
        this->label_lrcc->show();
        this->ci_bt->setText("图");
        flag3=0;
    }

}


void MainWindow::slideryin_press(int vaule)
{

    flag_yin=vaule;
    int fifo_fd = open("fifo_cmd",O_WRONLY);
    char buf[24]="";
    sprintf(buf,"%s%d%s","volume ",flag_yin," 1\n");
     printf("%s",buf);
    write(fifo_fd,buf, strlen(buf));

}

//******************ci

void MainWindow::ci_init(char *str)
{
    this->label_lrc->setText(str);
}

void MainWindow::ci_initt(char *str)
{
    this->label_lrcc->setText(str);
}

void MainWindow::qiege()
{
    char *lrc[128];
    bianli();
    char buf[128]="";
    char buf1[128]="";
    sscanf(buf_photos[n],"%[^.]",buf1);
    sprintf(buf,"%s%s%s","/home/edu/work/mplayer01/irc/",buf1,".lrc");
    printf("%s\n",buf);
//    printf("aaaaaaaaa");
    //QDebug()<<buf;
    char *str=Read(buf);
    int hang=Cutting(str,lrc);
    head=Unpacking(lrc,hang);
//    ci_init(head->lrc);
//    ci_initt(head->next->lrc);
}

void MainWindow::settile()
{
    this->title->setText(buf_photos[n]);
    QPalette ptt;
    ptt.setColor(QPalette::WindowText, Qt::red); //color
    this->title->setPalette(ptt);
}

void MainWindow::set_zhuanji()
{
    //zhuanji

    this->l_zhuanji=new QLabel(this);
    this->l_zhuanji->setGeometry(200,200,200,200);
    char buf[128]="";
    sprintf(buf,"%s%d%s","/home/edu/work/mplayer01/zhuanji/",n,".jpg");

    QPixmap pix;
    pix=QPixmap(buf);
    this->l_zhuanji->setPixmap(pix);

    //this->l_zhuanji->setScaledContents(true);
}

void MainWindow::set_bj()
{
    setAutoFillBackground(true);
    QPalette pal = this->palette();
    char buf[128]="";
    sprintf(buf,"%s%d%s","/home/edu/work/mplayer01/bj/",n,".jpg");
    pal.setBrush(backgroundRole(), QPixmap(buf));
    setPalette(pal);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int fifo_fd = open("fifo_cmd",O_WRONLY);
    write(fifo_fd,"quit\n", strlen("quit\n"));

}


# endif
