#ifndef ICONINFO_H
#define ICONINFO_H

#include <QLabel>
#include <QString>

struct IconInfo{
    QWidget *widget;
    float x;
    float y;
    float w;
    float h;
    QString p_on;
    QString p_off;
};

#endif // ICONINFO_H
