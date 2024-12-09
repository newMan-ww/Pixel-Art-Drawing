#include "DialogPixelSetting.h"
#include "ui_DialogPixelSetting.h"

#include "Config.h"
#include "functions.h"

DialogPixelSetting::DialogPixelSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPixelSetting)
{
    ui->setupUi(this);
    setWindowTitle(QString::fromStdString(GBKToUTF8("设置像素数量")));
    //关闭帮助按钮
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint | Qt::WindowCloseButtonHint);
    initdialog();
}

DialogPixelSetting::~DialogPixelSetting()
{
    delete ui;
}

void DialogPixelSetting::initdialog()
{
    ui->lineEdit_row->setText(QString::number(g_config.m_rowNumber));
    ui->lineEdit_column->setText(QString::number(g_config.m_columnNumber));
}

void DialogPixelSetting::on_pushButton_ok_clicked()
{
    int row = ui->lineEdit_row->text().toInt();
    int col = ui->lineEdit_column->text().toInt();

    if(row != g_config.m_rowNumber || col != g_config.m_columnNumber)
    {
        g_config.m_rowNumber = row;
        g_config.m_columnNumber = col;
        
        emit printCanvse(true);
    }

    QDialog::accept();
}

void DialogPixelSetting::on_pushButton_cancel_clicked()
{
    QDialog::reject();
}

