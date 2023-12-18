#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ClickableLabel.h"
// -156,154

extern float g_factor;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setContentsMargins(0,0,0,0);
    // 加载背景图
    label_background = new PixLabel(this);
    /********************初始化各指针***************************/
    init_widget_pointer();
    /********************初始化UI***************************/
    init_left_ui();
    init_right_ui();
    init_log_ui();
    /********************定时器***************************/
    init_timer();
    /********************绑定信号和槽函数***************************/
    connect_signal_slot();
    // 上电自检
    onPrepare();
}
/*********************************************初始化*************************************************/
void MainWindow::init_widget_pointer(){
    label_door = new QLabel((QLabel *)label_background);
    label_engine = new QLabel((QLabel *)label_background);
    label_ble = new QLabel((QLabel *)label_background);
    label_led = new QLabel((QLabel *)label_background);
    label_temp = new QLabel((QLabel *)label_background);
    label_safety = new QLabel((QLabel *)label_background);
    label_oil = new QLabel((QLabel *)label_background);
    label_turn_left = new QLabel((QLabel *)label_background);
    label_turn_right = new QLabel((QLabel *)label_background);

    label_bottom = new QLabel((QLabel *)label_background);
    label_car_state = new QLabel((QLabel *)label_background);

    label_velocity = new TextLabel((QLabel *)label_background);
    label_feel = new TextLabel((QLabel *)label_background);
    label_rpm = new TextLabel((QLabel *)label_background);
    label_gear = new TextLabel((QLabel *)label_background);
    label_tip = new TextLabel((QLabel *)label_background);


    label_ctrl = new QLabel(this);
    label_ctrl_wheel = new QLabel(label_ctrl);
    label_ctrl_start = new ClickPixLabel(label_ctrl);
    label_ctrl_turn_right = new ClickPixLabel(label_ctrl);
    label_ctrl_turn_left = new ClickPixLabel(label_ctrl);
    label_ctrl_up = new ClickPixLabel(label_ctrl);
    label_ctrl_down = new ClickPixLabel(label_ctrl);
    label_ctrl_moderate = new ClickPixLabel(label_ctrl);
    label_ctrl_accelerate = new ClickPixLabel(label_ctrl);
    label_ctrl_test_l = new ClickPixLabel(label_ctrl);
    label_ctrl_test_r = new ClickPixLabel(label_ctrl);

}
void MainWindow::init_left_ui(){
    /*******************初始化坐标xy，宽高wh，路径path**********************/
    init_left_data();
    /*******************加载图标**********************/
    for(int i=0; i<11; i++){
        //获取参数
        int x=left_info_list.at(i).x, y=left_info_list.at(i).y;
        int w=left_info_list.at(i).w, h=left_info_list.at(i).h;
        // 设置几何大小
        ((QLabel *)(left_info_list.at(i).widget))->setGeometry(x*factor, y*factor, w*factor, h*factor);
        // 设置图片
        setLabelPic((QLabel *)(left_info_list.at(i).widget), left_info_list.at(i).p_on);
    }

    /*******************加载5个文本label**********************/
    for(int i=11; i<16; i++){
        // 获取参数
        int x=left_info_list.at(i).x, y=left_info_list.at(i).y;
        int w=left_info_list.at(i).w, h=left_info_list.at(i).h;
        // 设置几何大小
        left_info_list.at(i).widget->setGeometry(x*factor, y*factor, w*factor, h*factor);
    }
    // 设置文本
    label_rpm->setLabelText(QString("2"), 35);
    label_velocity->setLabelText(QString("120"),35);
    label_gear->setLabelText(QString("D"),12);
    label_feel->setLabelText(QString("舒适"),8);
    label_tip->setLabelText(QString("正在启动..."),14);
}
void MainWindow::init_right_ui()
{
    /*******************初始化坐标xy，宽高wh，路径path**********************/
    init_right_data();
    /*******************设置几何大小**********************/
    label_ctrl->setGeometry(right_info_list.at(0).x, right_info_list.at(0).y,
                            right_info_list.at(0).w, right_info_list.at(0).h);
    label_ctrl_wheel->setGeometry(right_info_list.at(1).x, right_info_list.at(1).y,
                            right_info_list.at(1).w, right_info_list.at(1).h);
    // 设置背景图
    setLabelPic(label_ctrl, QString(":/icon/bg.png"));
    setLabelPic(label_ctrl_wheel, QString(":/icon/wheel.png"));

    // 设置几个小按钮的位置和图标，最后要repaint一下
    for(int i=2; i<11; i++){
        //right_info_list.at(i).widget = new ClickPixLabel(label_ctrl);
        int x=right_info_list.at(i).x, y=right_info_list.at(i).y;
        int w=right_info_list.at(i).w, h=right_info_list.at(i).h;
        QString p = right_info_list.at(i).p_on;
        ((ClickPixLabel *)(right_info_list.at(i).widget))->setX(x);
        ((ClickPixLabel *)(right_info_list.at(i).widget))->setY(y);
        ((ClickPixLabel *)(right_info_list.at(i).widget))->setW(w);
        ((ClickPixLabel *)(right_info_list.at(i).widget))->setH(h);
        ((ClickPixLabel *)(right_info_list.at(i).widget))->setP(p);
        right_info_list.at(i).widget->setGeometry(x, y, w, h);
        repaint();
    }
}
/***************************************************************
 * discription  :   初始化左侧图片的参数，包括坐标xy，宽高wh，路径p
 * params       :   none
 * return       :   none
 ***************************************************************/
void MainWindow::init_left_data()
{
    struct IconInfo info;
    info.widget = label_safety;
    info.x = 577; info.y=605; info.w=24; info.h=24;
    info.p_on = QString(":/pic/safety_on_1.png");
    info.p_off = QString(":/pic/safety_off_1.png");
    left_info_list << info;

    info.widget = label_oil;
    info.x = 615; info.y=605; info.w=24; info.h=24;
    info.p_on = QString(":/pic/oil_on_1.png");
    info.p_off = QString(":/pic/oil_off_1.png");
    left_info_list << info;

    info.widget = label_temp;
    info.x = 653; info.y=605; info.w=24; info.h=24;
    info.p_on = QString(":/pic/temp_on_1.png");
    info.p_off = QString(":/pic/temp_off_1.png");
    left_info_list << info;

    info.widget = label_engine;
    info.x = 691; info.y=605; info.w=24; info.h=24;
    info.p_on = QString(":/pic/engine_on_1.png");
    info.p_off = QString(":/pic/engine_off_1.png");
    left_info_list << info;

    info.widget = label_door;
    info.x = 729; info.y=605; info.w=24; info.h=24;
    info.p_on = QString(":/pic/door_on_1.png");
    info.p_off = QString(":/pic/door_off_1.png");
    left_info_list << info;

    info.widget = label_led;
    info.x = 767; info.y=605; info.w=24; info.h=24;
    info.p_on = QString(":/pic/led_on_1.png");
    info.p_off = QString(":/pic/led_off_1.png");
    left_info_list << info;

    info.widget = label_ble;
    info.x = 805; info.y=605; info.w=24; info.h=24;
    info.p_on = QString(":/pic/ble_on_1.png");
    info.p_off = QString(":/pic/ble_off_1.png");
    left_info_list << info;

    info.widget = label_turn_left;
    info.x = 515; info.y=278; info.w=21; info.h=22.07;
    info.p_on = QString(":/pic/left_on_1.png");
    info.p_off = QString(":/pic/left_off_1.png");
    left_info_list << info;

    info.widget = label_turn_right;
    info.x = 868; info.y=278; info.w=21; info.h=22.07;
    info.p_on = QString(":/pic/right_on_1.png");
    info.p_off = QString(":/pic/right_off_1.png");
    left_info_list << info;

    info.widget = label_bottom;
    info.x = 567; info.y=474; info.w=258; info.h=38;
    info.p_on = QString(":/pic/bottom_1.png");
    left_info_list << info;

    info.widget = label_car_state;
    info.x = 596; info.y=389; info.w=202; info.h=152;
    info.p_on = QString(":/pic/P.png");
    left_info_list << info;

    info.widget = label_rpm;
    info.x = 334; info.y=447; info.w=36; info.h=70;
    left_info_list << info;

    info.widget = label_velocity;
    info.x = 990; info.y=447; info.w=94; info.h=70;
    left_info_list << info;

    info.widget = label_gear;
    info.x = 347; info.y=525; info.w=15; info.h=14;
    left_info_list << info;

    info.widget = label_feel;
    info.x = 1030; info.y=529; info.w=15; info.h=14;
    left_info_list << info;

    info.widget = label_tip;
    info.x = 515+21; info.y=278; info.w=868-515-21; info.h=24;
    left_info_list << info;

    car_list << QString(":/pic/car_s_1.png") << QString(":/pic/car_s_2.png") << QString(":/pic/car_s_3.png") << QString(":/pic/car_s_4.png");
    gear_list << QString(":/pic/P.png") << QString(":/pic/R.png") << QString(":/pic/N.png") << QString(":/pic/D.png");
}
/***************************************************************
 * discription  :   初始化右侧图片的参数，包括坐标xy，宽高wh，路径p
 * params       :   none
 * return       :   none
 ***************************************************************/
void MainWindow::init_right_data(){
    struct IconInfo info;
    info.widget = label_ctrl;
    info.x = 1396; info.y=0; info.w=800; info.h=600;
    info.p_on = QString(":/icon/bg.png");
    right_info_list << info;

    info.widget = label_ctrl_wheel;
    info.x = 100; info.y=114; info.w=600; info.h=373.09;
    info.p_on = QString(":/icon/wheel.png");
    right_info_list << info;

    info.widget = label_ctrl_start;
    info.x=359.64; info.y=243.61; info.w=80; info.h=80;
    info.p_on = QString(":/icon/start.png");
    right_info_list << info;

    info.widget = label_ctrl_turn_right;
    info.x=162; info.y=230; info.w=64; info.h=42.86;
    info.p_on = QString(":/icon/turn_right.png");
    right_info_list << info;

    info.widget = label_ctrl_turn_left;
    info.x=162; info.y=273; info.w=64; info.h=42;
    info.p_on = QString(":/icon/turn_left.png");
    right_info_list << info;

    info.widget = label_ctrl_up;
    info.x=575; info.y=229; info.w=64; info.h=42.86;
    info.p_on = QString(":/icon/up.png");
    right_info_list << info;

    info.widget = label_ctrl_down;
    info.x=575; info.y=273; info.w=64; info.h=40;
    info.p_on = QString(":/icon/down.png");
    right_info_list << info;

    info.widget = label_ctrl_moderate;
    info.x=348; info.y=382; info.w=47.5; info.h=45;
    info.p_on = QString(":/icon/moderate.png");
    right_info_list << info;

    info.widget = label_ctrl_accelerate;
    info.x=405; info.y=382; info.w=47.5; info.h=45;
    info.p_on = QString(":/icon/accelerate.png");
    right_info_list << info;

    info.widget = label_ctrl_test_l;
    info.x=320; info.y=243; info.w=40; info.h=64;
    info.p_on = QString(":/icon/test_l.png");
    right_info_list << info;

    info.widget = label_ctrl_test_r;
    info.x=440; info.y=243; info.w=40; info.h=64;
    info.p_on = QString(":/icon/test_r.png");
    right_info_list << info;
}
/***************************************************************
 * discription  :   初始化右下角的log模块
 * params       :   none
 * return       :   none
 ***************************************************************/
void MainWindow::init_log_ui()
{
    text_log = new QTextEdit(this);
    text_log->move(1396*factor, 600*factor);
    text_log->setFixedSize(800*factor, (781-600)*factor);
    text_log->setText("I'm instrument");
    QFont font;
    font.setPointSize(18*factor);
    text_log->setFont(font);
    text_log->setReadOnly(true);
}
/***************************************************************
 * discription  :   初始化定时器，设置定时超时
 * params       :   none
 * return       :   none
 ***************************************************************/
void MainWindow::init_timer()
{
    timer_icon = new QTimer(this);
    timer_icon->setInterval(10);
    connect(timer_icon, SIGNAL(timeout()), this, SLOT(timerIcon()));

    timer_pic = new QTimer(this);
    timer_pic->setInterval(10);
    connect(timer_pic, SIGNAL(timeout()), this, SLOT(timerPic()));

    timer_rpm = new QTimer(this);
    timer_rpm->setInterval(10);
    connect(timer_rpm, SIGNAL(timeout()), this, SLOT(timerRpm()));

    timer_velocity = new QTimer(this);
    timer_velocity->setInterval(10);
    connect(timer_velocity, SIGNAL(timeout()), this, SLOT(timerVelocity()));
}
/***************************************************************
 * discription  :   绑定信号和槽函数
 * params       :   none
 * return       :   none
 ***************************************************************/
void MainWindow::connect_signal_slot()
{
    connect(label_ctrl_start, SIGNAL(pressed()), this, SLOT(onStart()));
    connect(label_ctrl_accelerate, SIGNAL(pressed()), this, SLOT(onAccelerate()));
    connect(label_ctrl_moderate, SIGNAL(pressed()), this, SLOT(onModerate()));
    connect(label_ctrl_up, SIGNAL(pressed()), this, SLOT(onUpGear()));
    connect(label_ctrl_down, SIGNAL(pressed()), this, SLOT(onDownGear()));
}
/*********************************************功能函数*************************************************/
/***************************************************************
 * discription  :   为label设置图片
 * params       :   label句柄，坐标(float)xy，宽高(float)wh，路径(QString)p
 * return       :   none
 ***************************************************************/
void MainWindow::setLabelPic(QLabel *label, QString p)
{
    // 加载图片资源
    QPixmap pix(p);
    // 设置缩放
    QPixmap dst = pix.scaled(label->width(), label->height(), Qt::KeepAspectRatio,Qt::SmoothTransformation);
    // 加载图片到label
    label->setPixmap(dst);
}
/***************************************************************
 * discription  :   追加日志
 * params       :   日志内容
 * return       :   none
 ***************************************************************/
void MainWindow::append_log(QString str)
{
    // 设置蓝色
    text_log->setTextColor(QColor(0,0,255));
    // 获取时间
    QDateTime cur_time = QDateTime::currentDateTime();
    // 将时间转为字符串
    QString content = cur_time.toString("yyyy-MM-dd hh:mm:ss");
    // 追加内容
    text_log->append(content);
    // 设置黑色
    text_log->setTextColor(QColor(0,0,0));
    // 追加内容
    content = str;
    text_log->append(content);
    // 将光标移动到最后
    text_log->moveCursor(QTextCursor::End);
}
/***************************************************************
 * discription  :   开机自检5s，车辆状态preparing，
 *                  档位P，9个小图标闪烁5次
 *                  仪表盘显示自检中，最后显示启动正常
 *                  时速指针0~120~0，转速指针0~7~0
 *                  更新日志
 * params       :   none
 * return       :   none
 ***************************************************************/
void MainWindow::onPrepare()
{  
    // 启动各种自检动画
    timer_rpm->start();
    timer_velocity->start();
    timer_icon->start();
    // 设置车的状态
    car_state = PREPARING;
    // 设置档位P
    gear = 0;
    // 设置UI
    setLabelPic(label_car_state , QString(":/pic/P.png"));
    label_gear->setLabelText( QString("P"),12);
    label_rpm->setText("0");
    label_velocity->setText("0");
    label_tip->setText("开机自检中，请等待...");
    append_log("preparing ...");
}
/*********************************************定时器槽函数*************************************************/
/***************************************************************
 * discription  :   定时器超时处理函数（槽函数）
 * params       :   none
 * return       :   none
 ***************************************************************/
void MainWindow::timerIcon()
{
    // 计时器参数
    sec_icon++;
    /*******************图标闪烁**********************/
    if(car_state == PREPARING){
        if(sec_icon<500){
            if((sec_icon/50)%2==0){
                for(int i=0; i<9; i++){
                    setLabelPic((QLabel *)(left_info_list.at(i).widget), left_info_list.at(i).p_on);
                }
            }
            else{
                for(int i=0; i<9; i++){
                    setLabelPic((QLabel *)(left_info_list.at(i).widget), left_info_list.at(i).p_off);
                }
            }
        }else{
            car_state = READY;
            label_tip->setText("自检正常,车辆可启动");
            append_log("自检正常");
        }
    }
}
void MainWindow::timerPic(){
    sec_pic++;
    switch (car_state) {
    case RUNNING_NORMAL:
    case RUNNING_ACCELERATE:
    case RUNNING_MODERATE:
        if(sec_pic>300){
            if(sec_pic%20==0){
                setLabelPic(label_car_state, car_list.at((sec_pic/20)%4));
            }
        }
        break;
    default:
        break;
    }
}
void MainWindow::timerRpm(){
    sec_rpm++;
    //(car_rpm-0)/(x-(-156)) == (1000-0)/(31-0)
    switch (car_state) {
    case PREPARING:
        if(sec_rpm<250)
            label_background->setRotateLeft(label_background->getRotateLeft()+((float)70/(float)250)*3.1);
        else
            label_background->setRotateLeft(label_background->getRotateLeft()-((float)70/(float)250)*3.1);
        break;
    case READY:
        car_rpm -= 5;
        label_background->setRotateLeft(car_rpm*0.031-156);
        if(car_rpm<=0) timer_rpm->stop();
        label_rpm->setText(QString::number(round(car_rpm/1000.0)));
        break;
    case STARTED:
        car_rpm += 5;
        label_background->setRotateLeft(car_rpm*0.031-156);
        if(car_rpm>=1000) timer_rpm->stop();
        label_rpm->setText(QString::number(round(car_rpm/1000.0)));
        break;
    case RUNNING_NORMAL:
    case RUNNING_ACCELERATE:
        car_rpm += 5;
        label_background->setRotateLeft(car_rpm*0.031-156);
        if(car_rpm>=3000) timer_rpm->stop();
        label_rpm->setText(QString::number(round(car_rpm/1000.0)));
        break;
    case RUNNING_MODERATE:
        car_rpm -= 5;
        label_background->setRotateLeft(car_rpm*0.031-156);
        if(car_rpm<=800) timer_rpm->stop();
        label_rpm->setText(QString::number(round(car_rpm/1000.0)));
        break;
    default:
        break;
    }
}
void MainWindow::timerVelocity(){
    sec_velocity++;
    switch (car_state) {
    case PREPARING:
        if(sec_velocity<250)
            label_background->setRotateRight(label_background->getRotateRight()+((float)60/(float)250)*3.1);
        else
            label_background->setRotateRight(label_background->getRotateRight()-((float)60/(float)250)*3.1);
        break;
    case RUNNING_NORMAL:
    case RUNNING_ACCELERATE:
        if(gear == GR){
            if(car_velocity>=30 || sec_velocity>10){
                timer_velocity->stop();
                return;
            }
        }
        else{
            if(car_velocity>=120 || sec_velocity>10){
                timer_velocity->stop();
                return;
            }
        }
        car_velocity += 0.5;
        label_background->setRotateRight(3.1*car_velocity/2.0-156);
        label_velocity->setText(QString::number((int)(car_velocity)));
        break;
    case RUNNING_MODERATE:
            if(car_velocity<=0 || sec_velocity>10){
                if(car_velocity<=0){
                    car_state = WAITING;
                    car_velocity = 0;
                }
                timer_velocity->stop();
                return;
            }
        car_velocity -= 0.5;
        label_background->setRotateRight(3.1*car_velocity/2.0-156);
        label_velocity->setText(QString::number((int)(car_velocity)));
        break;
    default:
        break;
    }
}
/*********************************************右侧按键槽函数*************************************************/
void MainWindow::onStart()
{
    append_log("I'm started ...");
    if(car_state!=PREPARING){
        switch(car_state){
        case READY:
        {
            car_state = STARTED;
            timer_rpm->stop();
            sec_rpm = 0;
            timer_rpm->start();
            append_log("车辆已启动");
            label_tip->setText("车辆已启动");
            label_ctrl_start->setP(":/icon/stop.png");
            repaint();
            break;
        }
        case STARTED:
        {
            car_state = READY;
            timer_rpm->stop();
            sec_rpm = 0;
            timer_rpm->start();
            append_log("车辆已就绪");
            label_tip->setText("车辆已就绪");
            label_ctrl_start->setP(":/icon/start.png");
            repaint();
            break;
        }
        case RUNNING_NORMAL:
        case RUNNING_ACCELERATE:
        case RUNNING_MODERATE:
            label_tip->setText("请减速到0再熄火");
            append_log("试图在行车过程中熄火，系统已阻止");
            break;
        case WAITING:
            car_state = READY;
            sec_rpm = 0;
            timer_rpm->start();
            append_log("车辆已就绪");
            label_tip->setText("车辆已就绪");
            label_ctrl_start->setP(":/icon/start.png");
            repaint();
            break;
        }
    }
}
void MainWindow::onAccelerate()
{
    switch (car_state) {
    case PREPARING:
        break;
    case READY:
        break;
    case STARTED:
    case RUNNING_NORMAL:
    case RUNNING_MODERATE:
    case RUNNING_ACCELERATE:
        if(gear==GR || gear==GD){
            car_state = RUNNING_ACCELERATE;
            sec_rpm = 0;
            sec_velocity = 0;
            timer_rpm->stop();
            timer_rpm->start();
            timer_velocity->stop();
            timer_velocity->start();
        }
        break;
    case WAITING:
        break;
    default:
        break;
    }
}
void MainWindow::onModerate(){
    switch (car_state) {
    case PREPARING:
        break;
    case READY:
        break;
    case STARTED:
    case RUNNING_NORMAL:
    case RUNNING_ACCELERATE:
    case RUNNING_MODERATE:
        if(gear==GR || gear==GD){
            car_state = RUNNING_MODERATE;
            sec_rpm = 0;
            sec_velocity = 0;
            timer_rpm->stop();
            //timer_rpm->start();
            timer_velocity->stop();
            timer_velocity->start();
        }
        break;
    case WAITING:
        break;
    default:
        break;
    }
}
void MainWindow::onUpGear(){
    switch (car_state) {
    case READY:
    case STARTED:
    case WAITING:
        gearChange(true);
        timer_pic->stop();
        setLabelPic(label_car_state,  gear_list.at(gear));
        sec_pic = 0;
        timer_pic->start();
        break;
    default:
        break;
    }
}
void MainWindow::onDownGear(){
    switch (car_state) {
    case READY:
    case STARTED:
    case WAITING:
        gearChange(false);
        timer_pic->stop();
        setLabelPic(label_car_state, gear_list.at(gear));
        sec_pic = 0;
        timer_pic->start();
        break;
    default:
        break;
    }
}
void MainWindow::gearChange(bool st){
    if(st){
        switch (gear) {
        case GP:
            gear = GR;
            break;
        case GR:
            gear = GN;
            break;
        case GN:
            gear = GD;
            break;
        case GD:
            gear = GP;
            break;
        default:
            break;
        }
    }else{
        switch (gear) {
        case GP:
            gear = GD;
            break;
        case GD:
            gear = GN;
            break;
        case GN:
            gear = GR;
            break;
        case GR:
            gear = GP;
            break;
        default:
            break;
        }
    }
}
/*********************************************set 方法*************************************************/
void MainWindow::setRotateLeft(float r)
{
    rotate_left = r;
}
void MainWindow::setRotateRight(float r)
{
    rotate_right = r;
}
void MainWindow::setFactor(float fac)
{
    factor = fac;
}
MainWindow::~MainWindow()
{
    delete ui;
}

