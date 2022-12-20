#include "mainwindow.h"
#include "control.h"

#include <QApplication>

using std::cout; using std::cin;
using std::endl; using std::string;
using std::filesystem::current_path;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    control c;

    //MainWindow::connect(&w,SIGNAL(transmit_LF_name(QString)),&c,SLOT(receive_LF_name(QString)));
    MainWindow::connect(&c,SIGNAL(update_view_event(QString,bool)),&w,SLOT(lf_update_display(QString,bool)));
    MainWindow::connect(&w,SIGNAL(change_view_event(QPoint)),&c,SLOT(receive_update_view(QPoint)));

    std::string order_path = "..\\gui-lf\\order_R1.txt";

    std::ifstream order;
    order.open(order_path);

    if (!order) {
        std::cerr << "Unable to open file order.txt";
        exit(1);   // call system to stop
    }

    w.readNewPair(order, c);
    //c.set_LF_name(lf_path);

    w.showFullScreen();
    int res = a.exec();
    return res;
}
