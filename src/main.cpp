#include "MainWindow.h"
#include <QApplication>

#include "Config.h"

int main(int argc, char *argv[])
{
    g_config.read_config(CONFIG_FILE);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

