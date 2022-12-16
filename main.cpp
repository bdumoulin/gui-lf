#include "mainwindow.h"
#include "control.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    control c;
    w.showMaximized();

    MainWindow::connect(&w,SIGNAL(transmit_LF_name(QString)),&c,SLOT(receive_LF_name(QString)));
    MainWindow::connect(&c,SIGNAL(update_view_event(QString,bool)),&w,SLOT(lf_update_display(QString,bool)));
    MainWindow::connect(&w,SIGNAL(transmit_test_sequence(QString)),&c,SLOT(receive_test_sequence(QString)));
    MainWindow::connect(&w,SIGNAL(change_view_event(QPoint)),&c,SLOT(receive_update_view(QPoint)));

    int res = a.exec();
    return res;
}
