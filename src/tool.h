/*
    Base class for a visual effect tool
*/
#ifndef TOOL_H
#define TOOL_H
#include <frame.h>

class Tool{
private:
public:
    /*
        Never used
    */
    Tool();
    /*
        Initilize the current tool
    */
    virtual void initTool(...) = 0;
    /*
        Do your magic
    */
    virtual void runTool(Frame* f1, Frame* f2) = 0;
};
#endif