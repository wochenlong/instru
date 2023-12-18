#include "ClickPixLabel.h"

ClickPixLabel::ClickPixLabel(QWidget *parent):QLabel(parent)
{

}
void ClickPixLabel::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.save();
    QPixmap pix(p);
    QPixmap dst = pix.scaled(w*factor, h*factor,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    painter.drawPixmap(0*factor, 0*factor, dst);
    QPen pen;
    pen.setWidth(5*factor);
    pen.setColor(Qt::blue);
    if(!is_press)
        painter.setPen(Qt::NoPen);
    else
        painter.setPen(pen);
    painter.drawRect(0*factor, 0*factor, w*factor, h*factor);
    painter.restore();
}
void ClickPixLabel::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        is_press = true;
        emit pressed();
        repaint();
    }
    QLabel::mousePressEvent(event);
}
void ClickPixLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        is_press = false;
        emit released();
        repaint();
    }
    QLabel::mouseReleaseEvent(event);
}

void ClickPixLabel::setP(QString p){
    this->p = p;
}
void ClickPixLabel::setX(float x){
    this->x = x;
}
void ClickPixLabel::setY(float y){
    this->y = y;
}
void ClickPixLabel::setW(float w){
    this->w = w;
}
void ClickPixLabel::setH(float h){
    this->h = h;
}



