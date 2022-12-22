#ifndef LFIMAGE_H
#define LFIMAGE_H

#include <filesystem>
#include <string>

#include "sai.h"

class LFimage
{
public:
    LFimage(std::string lf_name, int nb_img_x=9, int nb_img_y=9);

    std::string getName() const;
    int getNbx() const;
    int getNby() const;
    SAI* getCurrent();

    int getCurrentIndex();

    void setName(const std::string name);
    void setNbx(const int nb_img_x);
    void setNby(const int nb_img_y);
    void setCurrent(const SAI &new_current);
    void setCurrent(const int index);

    void loadSAIfromDir(std::string path, int nb_sais);

    friend std::ostream& operator<<(std::ostream& os, const LFimage& img);

private:
    std::string lf_name;
    int nb_img_x, nb_img_y;
    std::vector<SAI*> tab;
    SAI current;

};

#endif // LFIMAGE_H
