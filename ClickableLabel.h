#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H
#include <QLabel>
#include <QMouseEvent>
#include <QWidget>
#include <QPainter>
#include <QBrush>

class ClickableLabel : public QLabel
{
    Q_OBJECT
public:
   explicit ClickableLabel(QWidget *parent=nullptr, QString p=nullptr);
    ~ClickableLabel();
    void paintEvent(QPaintEvent *);
    QString path;
signals:
    void pressed();
    void released();
    void moved();
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
};

#endif // CLICKABLELABEL_H
