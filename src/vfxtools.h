#ifndef VFXTOOlS_H
#define VFXTOOLS_H
#include <iostream>
#include <vector>

#include <tool.h>
#include <tools/opticalflow.h>
#include <tools/shittyvhs.h>

class VfxTools{
    /*
        Main class for keeping each tool
    */
private:
    OpticalFlow opticFlowTool;
    VHSEffect vhsTool;
public:
    VfxTools();

    void OpticalFlow(Frame* f1, Frame* f2);

    void VHS(Frame* f1, Frame* f2);

    ~VfxTools();
};
#endif