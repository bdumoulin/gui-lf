#include "control.h"

static int unit_to_change=100;

control::control(QObject *parent, LFimage *distorded_left, LFimage *distorded_right)
    : QObject{parent}
{
    if(distorded_left==nullptr){
        this->distorded_left = new LFimage("");
    } else {
        this->distorded_left = distorded_left;
    }

    if(distorded_right==nullptr){
        this->distorded_right = new LFimage("");
    } else {
        this->distorded_right = distorded_right;
    }
}


void control::update_current_SAI(Direction change){
    int index = this->distorded_left->getCurrentIndex();
    switch(change){

        case left:
            if((index%this->distorded_left->getNbx()))
                index-=1;
            break;
        case right:
            if(((index+1)%this->distorded_left->getNbx()))
                index+=1;
            break;
        case top:
            if(index > this->distorded_left->getNbx())
                index-=this->distorded_left->getNbx();
            break;
        case bottom:
            if(index < (this->distorded_left->getNbx()*this->distorded_left->getNby()))
                index+=this->distorded_left->getNbx();
            break;
        case top_left:
            if(index > this->distorded_left->getNbx()){
                index-=this->distorded_left->getNbx();
            }
            if ((index%this->distorded_left->getNbx())) {
                index-=1;
            }
            break;
        case top_right:
            if(index > this->distorded_left->getNbx()){
                index-=this->distorded_left->getNbx();
            }
            if (((index+1)%this->distorded_left->getNbx())) {
                index+=1;
            }
            break;
        case bottom_left:
            if(index < (this->distorded_left->getNbx()*this->distorded_left->getNby())){
                index+=this->distorded_left->getNbx();
            }
            if ((index%this->distorded_left->getNbx())) {
                index-=1;
            }
            break;
        case bottom_right:
            if(index < (this->distorded_left->getNbx()*this->distorded_left->getNby())){
                index+=this->distorded_left->getNbx();
            }
            if (((index+1)%this->distorded_left->getNbx())) {
                index+=1;
            }
            break;
    }
    this->distorded_left->setCurrent(index);
    this->distorded_right->setCurrent(index);
}



void control::set_LF_name(std::string dir){
    this->distorded_left->setName(dir);
    this->distorded_left->loadSAIfromDir(dir,this->distorded_left->getNbx()*this->distorded_left->getNby());
    //std::cout << *this->original << std::endl;
    this->distorded_right->setName(dir);
    this->distorded_right->loadSAIfromDir(dir,this->distorded_right->getNbx()*this->distorded_right->getNby());
    //std::cout << *this->distorded << std::endl;

    emit update_view_event(QString::fromStdString(this->distorded_left->getCurrent()->getName()),0);
    emit update_view_event(QString::fromStdString(this->distorded_right->getCurrent()->getName()),1);
}

void control::receive_test_sequence(QString fn){
    std::cout << "Texte charge : " << fn.toStdString() << std::endl;
}


void control::receive_update_view(QPoint delta){
    Direction dir;
    if(delta.x() > unit_to_change){
        dir = right;
        if(delta.y() > unit_to_change){
            dir = top_right;
        }
        if(delta.y() < (-unit_to_change)){
            dir = bottom_right;
        }
    } else if (delta.x() < -(unit_to_change)){
        dir = left;
        if(delta.y() > unit_to_change){
            dir = top_left;
        }
        if(delta.y() < (-unit_to_change)){
            dir = bottom_left;
        }
    } else {
        if(delta.y() > unit_to_change){
            dir = top;
        }
        if(delta.y() < (-unit_to_change)){
            dir = bottom;
        }
    }

    std::cout << dir << std::endl;
    if(this->distorded_left->getName() != ""){
        this->update_current_SAI(dir);
        emit update_view_event(QString::fromStdString(this->distorded_left->getCurrent()->getName()),0);
        emit update_view_event(QString::fromStdString(this->distorded_right->getCurrent()->getName()),1);
    }
}
