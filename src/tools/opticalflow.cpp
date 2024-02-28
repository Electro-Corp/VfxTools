/*
*/
#include <tools/opticalflow.h>


void OpticalFlow::initTool(...){
    // It dosen't care about args tbh
    std::cout << "Tool \"Optical Flow\" initilized.\n";
}

/*
    Preform Optical Flow between two frames
*/
void OpticalFlow::runTool(Frame* f1, Frame* f2){
    OpticFlowMain(f1, f2);
}


/*
    Optical Flow
*/
void OpticalFlow::OpticFlowMain(Frame* f1, Frame* f2){
    Frame out("frame2.png", f1->getWidth(), f1->getHeight());   

    for(int y = 0; y < f1->getHeight(); y++){
        PixelRow row1 = *(f1->getRow(y));
        PixelRow row2 = *(f2->getRow(y));
        for(int x = 0; x < f1->getWidth(); x++){
            Pixel tmp;
            tmp.r = row1[x].r + abs(row2[x].r - row1[x].r);
            tmp.g = row1[x].g + abs(row2[x].g - row1[x].g);
            tmp.b = row1[x].b + abs(row2[x].b - row1[x].b);
            row1.setPixel(tmp, x);
        }
        out.setRow(row1, y);
    }

    out.Write();
}