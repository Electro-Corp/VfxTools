/*
    Compute convulutions 
*/
#ifndef CONV_H
#define CONV_H
#include <algorithm>

#include <frame.h>
namespace Math{
    Frame conv(Frame input, double kernel[3][3]);
}
#endif