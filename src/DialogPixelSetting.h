#ifndef DIALOGPIXELSETTING_H
#define DIALOGPIXELSETTING_H

#include <QDialog>

namespace Ui {
class DialogPixelSetting;
}

class DialogPixelSetting : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPixelSetting(QWidget *parent = nullptr);
    ~DialogPixelSetting();

private slots:
    void on_pushButton_ok_clicked();

    void on_pushButton_cancel_clicked();

private:
    void initdialog();

signals:
    void printCanvse(bool shouldReprint);

private:
    Ui::DialogPixelSetting *ui;
};

#endif // DIALOGPIXELSETTING_H
