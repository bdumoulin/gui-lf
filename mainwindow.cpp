#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>

static int unit_to_change=500;
static QPoint pos_ref(960,500);

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


void MainWindow::on_lf_load_clicked()
{
    //QString filename = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Images (*.png *.jpg *.jpeg *.bmp)"));
    QString OutputFolder = QFileDialog::getExistingDirectory(0, ("Select Output Folder"), QDir::currentPath());

    if (OutputFolder.compare("")){
        emit transmit_LF_name(OutputFolder);
    }
}


void MainWindow::lf_update_display(QString fn, bool flag){
    if (fn.compare("")){
        QImage lf_img;
        bool valid = lf_img.load(fn);

        if (valid){
            if (flag){
                //int width = lf_img.width();
                //int height = lf_img.height();
                ui->original->setPixmap(QPixmap::fromImage(lf_img));
            } else {
                //int width = lf_img.width();
                //int height = lf_img.height();
                ui->distorded->setPixmap(QPixmap::fromImage(lf_img));
            }
        }
    }
    std::cout << "Start Here" << std::endl;
}



void MainWindow::on_test_seq_btn_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Text"), ".", tr("Text files (*.txt)"));

    if (filename.compare("")){
        emit transmit_test_sequence(filename);
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    //QPoint test = MainWindow::mapFromGlobal(event->pos());
    QPoint delta = pos_ref-(event->pos());
    //QPoint delta = pos_ref-test;
    std::cout << "new pos: " << event->pos().x() << ";" << event->pos().y() << std::endl;
    //std::cout << "test: " << test.x() << ";" << test.y() << std::endl;
    if ((abs(delta.x())>=unit_to_change) || (abs(delta.y())>=unit_to_change)){
        std::cout << "delta: " << delta.x() << ";" << delta.y() << std::endl;
        pos_ref+=delta;
        std::cout << "ref: " << pos_ref.x() << ";" << pos_ref.y() << std::endl;
        //emit change_view_event(delta);
    }
}

