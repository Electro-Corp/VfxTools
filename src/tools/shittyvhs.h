/*
    Create a shitty VHS effect
*/
#ifndef VHS_H
#define VHS_H
#include <iostream>
#include <sstream>

#include <tool.h>
class VHSEffect : public Tool{
private:
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