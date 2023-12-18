#include "PixLabel.h"

// 构造函数，设置控件的初始化位置和大小
PixLabel::PixLabel(QWidget *parent):QLabel(parent)
{
    setGeometry(0, 0, 1391, 781);
}
/***************************************************************
 *  description     : 绘图函数，刷新的时候会调用此函数
 *  params          : QPaintEvent*
 *  return          : none
 ****************************************************************/
void PixLabel::paintEvent(QPaintEvent *)
{
    // 绘图句柄
    QPainter painter(this);
    /********************绘制背景图**************************/
    // 加载图片资源
    QPixmap pix(":/pic/background_1.png");
    // 设置缩放，原始大小是1396x781
    QPixmap dst = pix.scaled(1396*factor,781*factor,
       Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    // 绘制一个图片，参数是坐标xy，图片句柄
    painter.drawPixmap(0*factor,0*factor,dst);

    /************************绘制指针************************/
    drawPointer(&painter, 354, 453, rotate_left);
    drawPointer(&painter, 1040, 453, rotate_right);
}
/***************************************************************
 *  description     : 绘图函数，刷新的时候会调用此函数
 *  params          : QPaintEvent*
 *  return          : none
 ****************************************************************/
void PixLabel::drawPointer(QPainter *painter, float x, float y, float r)
{
    // 保存绘图 painter
    painter->save();
    // 平移整个绘图工具
    painter->translate(x*factor, y*factor);
    // 路径句柄
    QPainterPath pt;
    // 绘制梯形
    pt.moveTo(2.5*factor, 0*factor);
    pt.lineTo(0.25*factor, -157*factor);
    pt.lineTo(-0.25*factor, -157*factor);
    pt.lineTo(-2.5*factor, 0*factor);

    // 绘制扇形，参数是矩形的起始坐标xy，矩形宽高wh，扇形的起始角度、跨越角度
    pt.arcTo(-2.5*factor, 0*factor, 5*factor, 5*factor, 180,180);
    // 椭圆句柄
    QPainterPath in;
    // 绘制椭圆，参数是矩形的起始坐标xy，宽高wh
    in.addEllipse(-1.25*factor, -1.25*factor, 2.5*factor, 2.5*factor);

    // 设置颜色
    QRadialGradient radient(0,0,157*factor,0,0);
    // 颜色ARGB
    radient.setColorAt(0, QColor(0,199,140,150));
    radient.setColorAt(1, QColor(255,199,140,150));
    // 将颜色加载到画刷
    painter->setBrush(radient);
    // 设置旋转角度
    painter->rotate(r);
    // 开启反锯齿，让图形更加圆滑
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(Qt::NoPen);

    // 开始绘图，减去中间的圆圈，这样中间就是空心的
    painter->drawPath(pt.subtracted(in));
    // 恢复绘图矩形 painter
    painter->restore();
}

void PixLabel::setRotateLeft(float r)
{
    rotate_left = r;
    // 刷新，会调用paintEvent函数
    repaint();
}
void PixLabel::setRotateRight(float r)
{
    rotate_right = r;
    // 刷新，会调用paintEvent函数
    update();
}
float PixLabel::getRotateLeft()
{
    return rotate_left;
}
float PixLabel::getRotateRight()
{
    return rotate_right;
}
void PixLabel::setFactor(float fac)
{
    factor = fac;
}

