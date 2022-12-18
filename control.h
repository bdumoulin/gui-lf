#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include <QCursor>
#include <iostream>
#include <cstdlib>
#include "lfimage.h"

enum Direction {left=1, right, top, bottom, top_left, top_right, bottom_left, bottom_right}; // utile ????


class control : public QObject
{

    Q_OBJECT
public:
    explicit control(QObject *parent = nullptr, LFimage *original=nullptr, LFimage *distorded=nullptr);

    void update_current_SAI(Direction change);
    void set_LF_name(std::string dir);

signals:
    void update_view_event(QString fn, bool flag);

public slots:
    void receive_test_sequence(QString fn);
    void receive_update_view(QPoint delta);

private:
    LFimage *original;
    LFimage *distorded;
};

#endif // CONTROL_H
