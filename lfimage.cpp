#include "lfimage.h"

using namespace std;
using namespace filesystem;

LFimage::LFimage(string lf_name, int nb_img_x, int nb_img_y):
    lf_name(lf_name),nb_img_x(nb_img_x),nb_img_y(nb_img_y)
{
//    for (const auto entry : directory_iterator(lf_name)){
//        tab.emplace_back(entry.path().string());
//    }
//    this->current = tab[nb_img_x*nb_img_y/2];
}

string LFimage::getName() const
{
    return this->lf_name;
}

int LFimage::getNbx() const
{
    return this->nb_img_x;
}

int LFimage::getNby() const
{
    return this->nb_img_y;
}

SAI* LFimage::getCurrent()
{
    return &this->current;
}


int LFimage::getCurrentIndex(){
    int res = -1;
    for(int i=0; i<this->tab.size(); i++){
        if (this->tab[i]->getName()==this->current.getName()){
            res=i;
        }
    }
    return res;
}


void LFimage::setName(const std::string name)
{
    this->lf_name=name;
}

void LFimage::setNbx(const int nb_img_x)
{
    this->nb_img_x=nb_img_x;
}

void LFimage::setNby(const int nb_img_y)
{
    this->nb_img_y=nb_img_y;
}

void LFimage::setCurrent(const SAI &new_current)
{
    this->current=new_current;
}


void LFimage::setCurrent(const int index){
    this->current = *this->tab[index];
}


std::ostream& operator<<(std::ostream& os, const LFimage& img){
    os << img.getName() << "   (" <<img.getNbx() << "; " << img.getNby() << ")     " << img.current;
    return os;
}

/* pas de push back ou une re init du tableau avant chaque appel */
void LFimage::loadSAIfromDir(std::string path, int nb_sais){
    this->tab.clear();
    for (auto &entry : directory_iterator(lf_name)){
        this->tab.push_back(new SAI(entry.path().string()));
    }
    this->setCurrent(*tab[nb_sais/2]);
}


