#include <vfxtools.h>

VfxTools::VfxTools(){
    std::cout << "VFXTOOLS\n";
}

void VfxTools::OpticalFlow(Frame* f1, Frame* f2){
    this->opticFlowTool.initTool();
    this->opticFlowTool.runTool(f1, f2);
}

VfxTools::~VfxTools(){

}