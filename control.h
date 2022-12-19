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
    explicit control(QObject *parent = nullptr, LFimage *distorded_left=nullptr, LFimage *distorded_right=nullptr);

    void update_current_SAI(Direction change);
    void set_LF_name(std::string dir);

signals:
    void update_view_event(QString fn, bool flag);

public slots:
    void receive_test_sequence(QString fn);
    void receive_update_view(QPoint delta);

private:
    LFimage *distorded_left;
    LFimage *distorded_right;
};

#endif // CONTROL_H
