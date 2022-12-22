#ifndef SAI_H
#define SAI_H

#include <iostream>

class SAI
{
public:
    SAI(std::string name, int w, int h);
    SAI(std::string name);
    SAI(SAI &sai);
    SAI();

    int getWidth() const;
    int getHeight() const;
    std::string getName() const;

    friend std::ostream& operator<<(std::ostream& os, const SAI& img);

private:
    int w,h;
    std::string name;
};

#endif // SAI_H
