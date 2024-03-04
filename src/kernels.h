/*
    Set of kernels to use
*/
#ifndef KERNELS_H
#define KERNELS_H
/*
    Sobel image derivitve kernel
*/
double sobel[3][3] = {
    {1.0f, 2.0f, 1.0f},
    {0.0f, 0.0f, 0.0f},
    {-1.0f, -2.0f, -1.0f}
};

double edge[3][3] = {
    {-1.0f, -1.0f, -1.0f},
    {-1.0f, 8.0f, -1.0f},
    {-1.0f, -1.0f, -1.0f}
};

double gauss[3][3] = {
    {0.0625f, 0.125f ,0.0625f},
    {0.125, 0.25, 0.125},
    {0.0625, 0.125f, 0.0625}
};
#endif