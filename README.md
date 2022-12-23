# gui-lf

## Description

A GUI for light field images display and subjective tests. The aim of this GUI is to do subjective tests (pair comparison method), then it takes a databases of images with distorsions and display all pairs. The user can choose which is best and a result file is written.

This GUI use C++ with Qt. To compile and run it, make sure you have installed all the needed libraries. Please know this app is made for 1920x1080 screen to be fully optimized.

## Installation

### Project

Clone this repository with :

```bash
git clone https://github.com/bdumoulin/gui-lf.git
git checkout main
```

### Qt libraries

You need the Qt libraries to compile the project. Use the followings steps for linux and windows distributions.

-for linux :
```bash
sudo apt-get build-dep qtbase5-dev
```

-for windows:
Go to https://www.qt.io/download and download Qt (latest stable version).


### CMake

Please use cmake to create an operating cmakefile (the one in the project might not work).


## Configuration

A lot of things can be changed for now in the code for different working modes. 

-The path of the output, you can change the first part of the path to allow the output to go in the right folder for you. This code is in control.cpp in the control constructor.

```c++
std::string out_name = "C:\\Users\\Asus\\Temp\\tests_R1_"+std::to_string(test->tm_mday)+"_"
            +std::to_string(test->tm_mon+1)+"_"+std::to_string(test->tm_year+1900)+"_"+std::to_string(test->tm_min)+".txt";
```

-The order file path, you can change this path to have a different order for R1 images (note that the file take only in account a R1 random order). This code is in control.h in the default argument of the explicit constructor of control.

```c++
explicit control(QObject *parent = nullptr, LFimage *distorded_left=nullptr, LFimage *distorded_right=nullptr, std::string order_path="..\\gui-lf\\order_R1.txt");
```

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

