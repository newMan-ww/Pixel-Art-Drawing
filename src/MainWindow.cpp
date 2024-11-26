#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitDialogControls();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitDialogControls()
{
    ui->horizontalLayout_2->setAlignment(ui->pushButton_hide_show, Qt::AlignRight);
}

void MainWindow::on_pushButton_hide_show_clicked()
{
    if (ui->widget_control->isVisible()) {
        ui->widget_control->hide();  // 隐藏控制面板
        ui->pushButton_hide_show->setText("<<");  // 更新按钮文本

        ui->horizontalSpacer->changeSize(0,20,QSizePolicy::Fixed, QSizePolicy::Fixed);
        ui->verticalSpacer->changeSize(0,0,QSizePolicy::Fixed, QSizePolicy::Expanding);

    } else {
        ui->widget_control->show();  // 显示控制面板
        ui->pushButton_hide_show->setText(">>");  // 更新按钮文本

        ui->horizontalSpacer->changeSize(40,20,QSizePolicy::Expanding, QSizePolicy::Fixed);
        ui->verticalSpacer->changeSize(0,0,QSizePolicy::Expanding, QSizePolicy::Fixed);
    }

}

