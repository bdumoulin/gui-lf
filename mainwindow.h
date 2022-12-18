#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QMouseEvent>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void mouseMoveEvent(QMouseEvent *event) override;

signals:
    void transmit_LF_name(QString dir);
    void transmit_test_sequence(QString fn);
    void change_view_event(QPoint delta);

private slots:
    void lf_update_display(QString fn, bool flag);   // 0 pour gauche, 1 pour droite

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
