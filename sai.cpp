#include "sai.h"

SAI::SAI(std::string name,int w, int h):w(w), h(h)
{
    if (name.compare("")){
        this->name=name;
    }
}

SAI::SAI(std::string name){
    if (name.compare("")){
        this->name=name;
        this->w=0;
        this->h=0;
    }
}

SAI::SAI(SAI &sai){
    this->w=sai.w;
    this->h=sai.h;
    this->name=sai.name;
}


// constructeur par défaut
SAI::SAI(){
    this->name="";
    this->w=0;
    this->h=0;
}


int SAI::getWidth() const {
    return this->w;
}
int SAI::getHeight() const {
    return this->h;
}

std::string SAI::getName() const {
    return this->name;
}

std::ostream& operator<<(std::ostream& os, const SAI& img) {
    os << img.getName() << "   " << img.getWidth() << "*" << img.getHeight() << std::endl;
    return os;
}
