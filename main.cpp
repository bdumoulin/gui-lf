#include "mainwindow.h"
#include "control.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    control c;

    MainWindow::connect(&w,SIGNAL(choice_made_event(QString)),&c,SLOT(next_lf_image(QString)));
    MainWindow::connect(&c,SIGNAL(update_view_event(QString,bool)),&w,SLOT(lf_update_display(QString,bool)));
    MainWindow::connect(&w,SIGNAL(change_view_event(QPoint)),&c,SLOT(receive_update_view(QPoint)));

    c.readNewPair();

    w.showFullScreen();
    int res = a.exec();
    return res;
}
