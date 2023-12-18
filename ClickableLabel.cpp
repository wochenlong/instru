#include "ClickableLabel.h"
#include <QDebug>
#include <QPainterPath>
ClickableLabel::ClickableLabel(QWidget *parent, QString p):QLabel(parent)
{
    path = p;
}
#if 1
void ClickableLabel::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.save();

    QPixmap px(path);
    QPixmap dst = px.scaled(px.width(),px.height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    painter.drawPixmap(0,0,dst);
    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::red);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(pen);
    painter.drawRect(0,0,24,24);
    painter.restore();
}
#endif

void ClickableLabel::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        emit pressed();
        qDebug()<<"hello";
        setStyleSheet("QLabel{border:3px solid rgb(255,0,0);}");
        repaint();
    }
    QLabel::mousePressEvent(event);
}
void ClickableLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        emit released();
        repaint();
    }
    QLabel::mouseReleaseEvent(event);
}
void ClickableLabel::mouseMoveEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
        emit moved();
    QLabel::mouseMoveEvent(event);
}
ClickableLabel::~ClickableLabel()
{

}
