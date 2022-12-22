#include "control.h"

static int unit_to_change=80;
static std::string folder_lf_path = "..\\gui-lf\\Datasets\\R1";
//static std::string ref_name = "R1";

control::control(QObject *parent, LFimage *distorded_left, LFimage *distorded_right, std::string order_path)
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

    this->order.open(order_path);

    if (!order) {
        std::cerr << "Unable to open file order.txt";
        exit(1);   // call system to stop
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
            if(index < (this->distorded_left->getNbx()*(this->distorded_left->getNby()-1)))
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
            if(index < (this->distorded_left->getNbx()*(this->distorded_left->getNby()-1))){
                index+=this->distorded_left->getNbx();
            }
            if ((index%this->distorded_left->getNbx())) {
                index-=1;
            }
            break;
        case bottom_right:
            if(index < (this->distorded_left->getNbx()*(this->distorded_left->getNby()-1))){
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



void control::set_LF_name(std::string dir_left, std::string dir_right){
    this->distorded_left->setName(dir_left);
    this->distorded_left->loadSAIfromDir(dir_left,this->distorded_left->getNbx()*this->distorded_left->getNby());
    //std::cout << *this->original << std::endl;
    this->distorded_right->setName(dir_right);
    this->distorded_right->loadSAIfromDir(dir_right,this->distorded_right->getNbx()*this->distorded_right->getNby());
    //std::cout << *this->distorded << std::endl;

    emit update_view_event(QString::fromStdString(this->distorded_left->getCurrent()->getName()),0);
    emit update_view_event(QString::fromStdString(this->distorded_right->getCurrent()->getName()),1);
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

    //std::cout << dir << std::endl;
    if(this->distorded_left->getName() != ""){
        this->update_current_SAI(dir);
        emit update_view_event(QString::fromStdString(this->distorded_left->getCurrent()->getName()),0);
        emit update_view_event(QString::fromStdString(this->distorded_right->getCurrent()->getName()),1);
    }
}


void control::readNewPair(){
    //std::cout << "nouveau test a faire" << std::endl;
    std::string str;
    std::string str_left;
    //char *str_arr_left= new char[7];
    std::string str_right;
    //char *str_arr_right=new char[7];
    for(int i=1;i<=272;i++){
        std::getline(this->order, str);
        int n=str.length();
        bool passed=0;
        for(int c=0;c<n;c++){
            if(str[c]!=';'){
                //char debug =str[c];
                if (passed) {
                    str_right.push_back(str[c]);
                }
                if (!passed){
                    str_left.push_back(str[c]);
                }
            }else{
                passed=1;
            }
        }
        break;
    }
    if((str_left.compare(""))&&(str_right.compare(""))){
        this->set_LF_name(folder_lf_path+"\\"+str_left, folder_lf_path+"\\"+str_right);
    }
}


void control::next_lf_image(QString toWrite){
    //ecrire le résultat dans fichier de sortie
    std::cout << toWrite.toStdString() << std::endl;
    readNewPair();
}
