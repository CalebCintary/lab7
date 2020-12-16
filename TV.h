//
// Created by calebcintary on 12/15/20.
//

#ifndef UNTITLED_TV_H
#define UNTITLED_TV_H

#include "MatrixType.h"

struct TV {
    const char* model;
    const char* manufacturer;
    enum MatrixType matrixType;
    const char* resolution;
    const char* refreshRate;
};
#endif //UNTITLED_TV_H
