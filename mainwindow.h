#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include<stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <dirent.h>
#include<QPushButton>
#include<QListWidget>
#include<QLabel>
#include<QPixmap>
#include<QPalette>
#include<QDebug>
using namespace std ;



namespace Ui {
class MainWindow;
}
void *deal_fun2(void *arg);
void *deal_fun(void *arg);
//bool t_play=true;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //int flag=0;//pouse
    int flag1=0;//close list
    int flag2=0;//yin
    int flag3=0;//ci

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void bianli();
    QString str2qstr(const string str);
    string qstr2str(const QString qstr);
    void ci_init(char *str);
    void ci_initt(char *str);
    pthread_mutex_t mutex;

//    int timer();

    void qiege();
    void settile();
    void set_zhuanji();
    void set_bj();
    void closeEvent(QCloseEvent *event);
public slots:
    void on_pushButton_clicked();
    void sider_press(int vaule);
    void next_press();
    void front_press();
    void jin_press();
    void tui_press();
    void play_press();
    void yin_press();
    void list_press();
//    void lrc_show();
    void update();
    void ci_labe();

    void slideryin_press(int vaule);
signals:


public:
    Ui::MainWindow *ui;
    char **buf_photos;

    char **buf_lrc;
    int num[124];


    QSlider *slider;
    QSlider *yin_sider;
    QListWidget *listWidget;
    QPushButton *next;
    QPushButton *front;
    QPushButton *jin;
    QPushButton *tui;
    QPushButton *play;
    QPushButton *yin;
    QPushButton *ci_bt;
    QLabel *label_time1;
    QLabel *label_time2;
    QLabel *label_time3;
    QLabel *label_lrc;
    QLabel *label_lrcc;
    QLabel *title;
    QLabel *l_zhuanji;

};
typedef struct
{
    MainWindow *p_w;
    int read_fd;
    int writ_fd;
   // float time_pos;

}DATA;
#endif // MAINWINDOW_H
