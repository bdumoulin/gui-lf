#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include <QCursor>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <ctime>

#include "lfimage.h"

enum Direction {left=1, right, top, bottom, top_left, top_right, bottom_left, bottom_right}; // utile ????


class control : public QObject
{

    Q_OBJECT
public:
    explicit control(QObject *parent = nullptr, LFimage *distorded_left=nullptr, LFimage *distorded_right=nullptr, std::string order_path="..\\gui-lf\\order_R1.txt");

    void readNewPair();

    void update_current_SAI(Direction change);
    void set_LF_name(std::string dir_left, std::string dir_right);

signals:
    void update_view_event(QString fn, bool flag);

public slots:
    void receive_update_view(QPoint delta);
    void next_lf_image(QString toWrite);

private:
    LFimage *distorded_left;
    LFimage *distorded_right;
    std::ifstream order;
    std::ofstream *out;
};

#endif // CONTROL_H
