#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "PixLabel.h"
#include "TextLabel.h"
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QDebug>
#include <QTimer>
#include <QList>
#include "IconInfo.h"
#include "ClickPixLabel.h"
#include <QTextEdit>
#include <QDateTime>
#include <cmath>

#define PREPARING           0
#define READY               1
#define STARTED             2
#define RUNNING_NORMAL      3
#define RUNNING_ACCELERATE  4
#define RUNNING_MODERATE    5
#define WAITING             6
#define STOPED              7

#define GP          0
#define GR          1
#define GN          2
#define GD          3


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init_widget_pointer();
    void init_left_data();
    void init_right_data();
    void init_car_data();
    void init_left_ui();
    void init_right_ui();
    void init_log_ui();
    void append_log(QString str);
    void connect_signal_slot();
    void init_timer();
    void onPrepare();
    void gearChange(bool st);
    void setRotateLeft(float r);
    void setRotateRight(float r);
    void setFactor(float fac);
    void setLabelPic(QLabel *label, QString p);

private:
    Ui::MainWindow *ui;

    float factor=g_factor;
    float rotate_left=0;
    float rotate_right=0;
    int sec_icon=0;
    int sec_pic=0;
    int sec_rpm=0;
    int sec_velocity=0;
    int car_state=PREPARING;
    int car_rpm=0;
    float car_velocity=0;
    int gear;

    QTimer *timer_icon;
    QTimer *timer_pic;
    QTimer *timer_rpm;
    QTimer *timer_velocity;
    
    QList<struct IconInfo> left_info_list;
    QList<struct IconInfo> right_info_list;

    QList<QString> car_list;
    QList<QString> gear_list;
    /*****************left******************/
    PixLabel *label_background;
    QLabel *label_safety;
    QLabel *label_oil;
    QLabel *label_temp;
    QLabel *label_engine;
    QLabel *label_door;
    QLabel *label_led;
    QLabel *label_ble;
    QLabel *label_turn_left;
    QLabel *label_turn_right;
    QLabel *label_bottom;
    QLabel *label_car_state;

    TextLabel *label_velocity;
    TextLabel *label_rpm;
    TextLabel *label_gear;
    TextLabel *label_feel;
    TextLabel *label_tip;
    /*********************right********************/
    QLabel *label_ctrl;
    QLabel *label_ctrl_wheel;
    ClickPixLabel *label_ctrl_start;
    ClickPixLabel *label_ctrl_turn_right;
    ClickPixLabel *label_ctrl_turn_left;
    ClickPixLabel *label_ctrl_up;
    ClickPixLabel *label_ctrl_down;
    ClickPixLabel *label_ctrl_moderate;
    ClickPixLabel *label_ctrl_accelerate;
    ClickPixLabel *label_ctrl_test_l;
    ClickPixLabel *label_ctrl_test_r;
    QTextEdit *text_log;

public slots:
    void timerIcon();
    void timerRpm();
    void timerVelocity();
    void timerPic();
    void onStart();
    void onAccelerate();
    void onModerate();
    void onUpGear();
    void onDownGear();
};

#endif // MAINWINDOW_H
