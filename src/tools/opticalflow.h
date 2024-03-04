/*
    Flow between two images (like what they did for The Matrix's bullet time)
*/
#ifndef OPTICALFLOW_H
#define OPTICALFLOW_H
#include <iostream>
#include <sstream>

#include <tool.h>
#include <math/conv.h>
class OpticalFlow : public Tool{
private:
    void OpticFlowMain(Frame* f1, Frame* f2);
public:
    /*
        Initilize the tool
    */
    virtual void initTool(...) override;

    /* 
        Run the tool on two frames
    */
    virtual void runTool(Frame* f1, Frame* f2) override;

    
};
#endif