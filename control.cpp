#include "control.h"

static int unit_to_change=100;

control::control(QObject *parent, LFimage *original, LFimage *distorded)
    : QObject{parent}
{
    if(original==nullptr){
        this->original = new LFimage("");
    } else {
        this->original = original;
    }

    if(distorded==nullptr){
        this->distorded = new LFimage("");
    } else {
        this->distorded = distorded;
    }
}


void control::update_current_SAI(Direction change){
    int index = this->original->getCurrentIndex();
    switch(change){

        case left:
            if((index%this->original->getNbx()))
                index-=1;
            break;
        case right:
            if(((index+1)%this->original->getNbx()))
                index+=1;
            break;
        case top:
            if(index > this->original->getNbx())
                index-=this->original->getNbx();
            break;
        case bottom:
            if(index < (this->original->getNbx()*this->original->getNby()))
                index+=this->original->getNbx();
            break;
        case top_left:
            if(index > this->original->getNbx()){
                index-=this->original->getNbx();
            }
            if ((index%this->original->getNbx())) {
                index-=1;
            }
            break;
        case top_right:
            if(index > this->original->getNbx()){
                index-=this->original->getNbx();
            }
            if (((index+1)%this->original->getNbx())) {
                index+=1;
            }
            break;
        case bottom_left:
            if(index < (this->original->getNbx()*this->original->getNby())){
                index+=this->original->getNbx();
            }
            if ((index%this->original->getNbx())) {
                index-=1;
            }
            break;
        case bottom_right:
            if(index < (this->original->getNbx()*this->original->getNby())){
                index+=this->original->getNbx();
            }
            if (((index+1)%this->original->getNbx())) {
                index+=1;
            }
            break;
    }
    this->original->setCurrent(index);
    this->distorded->setCurrent(index);
}



void control::set_LF_name(std::string dir){
    this->original->setName(dir);
    this->original->loadSAIfromDir(dir,this->original->getNbx()*this->original->getNby());
    //std::cout << *this->original << std::endl;
    this->distorded->setName(dir);
    this->distorded->loadSAIfromDir(dir,this->distorded->getNbx()*this->distorded->getNby());
    //std::cout << *this->distorded << std::endl;

    emit update_view_event(QString::fromStdString(this->original->getCurrent()->getName()),0);
    emit update_view_event(QString::fromStdString(this->distorded->getCurrent()->getName()),1);
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
    if(this->original->getName() != ""){
        this->update_current_SAI(dir);
        emit update_view_event(QString::fromStdString(this->original->getCurrent()->getName()),0);
        emit update_view_event(QString::fromStdString(this->distorded->getCurrent()->getName()),1);
    }
}
