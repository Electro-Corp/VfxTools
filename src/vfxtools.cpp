#include <vfxtools.h>

VfxTools::VfxTools(){
    std::cout << "VFXTOOLS\n";
    this->opticFlowTool.initTool();
    this->vhsTool.initTool();
}

void VfxTools::OpticalFlow(Frame* f1, Frame* f2){
    
    this->opticFlowTool.runTool(f1, f2);
}

void VfxTools::VHS(Frame* f1, Frame* f2){
    this->vhsTool.runTool(f1, f2);
}

VfxTools::~VfxTools(){

}