#ifndef TEXTLABEL_H
#define TEXTLABEL_H
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QPalette>
extern float g_factor;
class TextLabel : public QLabel
{
    Q_OBJECT
private:
    float factor = g_factor;
public:
    explicit TextLabel(QWidget *parent=nullptr);
    void setLabelText(QString str, int size);
};

#endif // TEXTLABEL_H
