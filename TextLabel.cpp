#include "TextLabel.h"

TextLabel::TextLabel(QWidget *parent):QLabel(parent)
{

}
/*******************************************
 * name:    setLabelText
 * dscription   : set a label size\content\color\
 * param        :
 *                  str   content(setText)
 *                  size  font size
 * return       :   none
 ********************************************/
void TextLabel::setLabelText(QString str, int size)
{
    /****************content**********************/
    // 设置显示的内容
    setText(str);
    // 设置居中对齐Qt::AlignCenter， 水平居中Qt::AlignHCenter，垂Qt::AlignVCenter直居中
    setAlignment(Qt::AlignCenter);

    /*****************color***********************/
    // 调色板，用来设置控件的颜色
    QPalette palette;
    // 窗口文字，蓝色
    palette.setColor(QPalette::WindowText, Qt::white);
    // 加载调色板
    setPalette(palette);

    /*****************font size*********************/
    // 设置字体
    QFont font;
    // 设置大小
    font.setPointSize(size*factor);
    // 加载font
    setFont(font);
}
