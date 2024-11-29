#ifndef GRAYWHITEBUTTON_H
#define GRAYWHITEBUTTON_H

#include <QPushButton>

//用来展示背景为灰白色相间像素点的按钮
class GrayWhiteButton : public QPushButton {
    Q_OBJECT

public:
    explicit GrayWhiteButton(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // GRAYWHITEBUTTON_H

