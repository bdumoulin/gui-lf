#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>

static int unit_to_change=100;
static QPoint pos_ref(960,540);
static int buffer=1;
static std::string folder_lf_path = "..\\gui-lf\\Datasets\\R1";
static std::string ref_name = "R1";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMouseTracking(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::lf_update_display(QString fn, bool flag){
    if (fn.compare("")){
        QImage lf_img;
        bool valid = lf_img.load(fn);

        if (valid){
            if (flag){
                //int width = lf_img.width();
                //int height = lf_img.height();
                ui->distorded_left->setPixmap(QPixmap::fromImage(lf_img));
            } else {
                //int width = lf_img.width();
                //int height = lf_img.height();
                ui->distorded_right->setPixmap(QPixmap::fromImage(lf_img));
            }
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    QPoint delta = pos_ref-(event->pos());
    std::cout << "new pos: " << event->pos().x() << ";" << event->pos().y() << std::endl;
    if ((abs(delta.x())>=unit_to_change) || (abs(delta.y())>=unit_to_change)){
        std::cout << "delta: " << delta.x() << ";" << delta.y() << std::endl;
        //pos_ref+=delta;
        pos_ref.setX(event->pos().x());
        pos_ref.setY(event->pos().y());
        std::cout << "ref: " << pos_ref.x() << ";" << pos_ref.y() << std::endl;
        emit change_view_event(delta);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    int res=0;
    switch(event->key()){
        case Qt::Key_Left:
            emit choice_made_event("10");
            res=1;
            break;
        case Qt::Key_Right:
            emit choice_made_event("01");
            res=1;
            break;
    }
    if (res) {
        //readNewPair("folder name here");
    }
}



void MainWindow::readNewPair(std::ifstream &order, control &c){
    //std::cout << "nouveau test a faire" << std::endl;
    std::string str;
    for(int i=1;;i++){
        std::getline(order,str);
        if(i==buffer){
            buffer++;
            break;
        }
    }
    if(str.compare("")){
        c.set_LF_name(folder_lf_path+"\\"+ref_name, folder_lf_path+"\\"+str);
    }
}
