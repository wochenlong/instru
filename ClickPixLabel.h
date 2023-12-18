#ifndef CLICKPIXLABEL_H
#define CLICKPIXLABEL_H
#include <QLabel>
#include <QWidget>
#include <QPaintEvent>
#include <QPixmap>
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>

extern float g_factor;
class ClickPixLabel:public QLabel
{
    Q_OBJECT
public:
    explicit ClickPixLabel(QWidget *parent=nullptr);
    void paintEvent(QPaintEvent *);
    void setX(float x);
    void setY(float y);
    void setW(float w);
    void setH(float h);
    void setP(QString path);
private:
    float x;
    float y;
    float w;
    float h;
    QString p;
    bool is_press=false;
    float factor=g_factor;

protected:
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
signals:
    void pressed();
    void released();
};

#endif // CLICKPIXLABEL_H
