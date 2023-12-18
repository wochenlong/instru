#ifndef PIXLABEL_H
#define PIXLABEL_H

#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
#include <QRadialGradient>
extern float g_factor;
class PixLabel:QLabel
{
    Q_OBJECT
private:
    float factor=g_factor;
    float rotate_left=-156;
    float rotate_right=-156;
public:
    explicit PixLabel(QWidget *parent=nullptr);
    void paintEvent(QPaintEvent *);
    void drawPointer(QPainter *painter, float x, float y, float r);
    void setFactor(float fac);
    void setRotateLeft(float r);
    void setRotateRight(float r);
    float getRotateLeft();
    float getRotateRight();
};

#endif // PIXLABEL_H
