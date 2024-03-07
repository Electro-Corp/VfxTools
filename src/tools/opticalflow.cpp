/*
*/
#include <tools/opticalflow.h>
#include <kernels.h>
#include <complex>


void OpticalFlow::initTool(...){
    // It dosen't care about args tbh
    std::cout << "Tool \"Optical Flow\" initilized.\n";
}

/*
    Preform Optical Flow between two frames
*/
void OpticalFlow::runTool(Frame* f1, Frame* f2){
    assert(f1->getHeight() == f2->getHeight());
    assert(f2->getWidth() == f1->getWidth());
    OpticFlowMain(f1, f2);
}

typedef struct{
    int x, y;
} Point;

typedef struct{
    Pixel pixels1[4];
    Point p1;

    Pixel pixels2[4];
    Point p2;
} Block;

int doesPixelMatch(Pixel a, Pixel b){
    return a.r == b.r &&
            a.g == b.g &&
            a.b == b.b;
}
Frame greenScreenReplace("point.png");
/*
    Optical Flow
*/
void OpticalFlow::OpticFlowMain(Frame* f1, Frame* f2){
    
    int num = std::stoi(f2->getPath().erase(f2->getPath().find("T3/"), 3)) - 1;
    Frame out("OUT/" + std::to_string(num), f1->getWidth(), f1->getHeight());   


    /*
        Find intensity of each pixel in image 
        (simpily convert to grayscale)
    */

    Frame grayf1("frame1G.png", f1->getWidth(), f1->getHeight());
    Frame grayf2("frame3G.png", f1->getWidth(), f1->getHeight());

    Frame intermediate("INTER/" + std::to_string(num),f1->getWidth(), f1->getHeight());

    for(int y = 0; y < f1->getHeight(); y++){
        PixelRow row1 = *(f1->getRow(y));
        PixelRow row2 = *(f2->getRow(y));
        for(int x = 0; x < f1->getWidth(); x++){
            Pixel tmp;
            float mid1 = (row1[x].r + row1[x].g + row1[x].b) / 3;
            float mid2 = (row2[x].r + row2[x].g + row2[x].b) / 3;
            tmp.r = mid1;
            tmp.g = mid1;
            tmp.b = mid1;
            row1.setPixel(tmp, x);
            tmp.r = mid2;
            tmp.g = mid2;
            tmp.b = mid2;
            row2.setPixel(tmp, x);
        }
        grayf1.setRow(row1, y);
        grayf2.setRow(row2, y);
    }

    Frame dervY = Math::conv(grayf1, sobelY);
    Frame dervX = Math::conv(grayf1, sobelX);
    dervY.Write();
    dervX.Write();

    Frame derv("CONVSFULL/" + std::to_string(num), dervY.getWidth(), dervX.getHeight());

    for(int y = 0; y < derv.getHeight(); y++){
        PixelRow rowDY = *(dervY.getRow(y));
        PixelRow rowDX = *(dervX.getRow(y));
        for(int x = 1; x < derv.getWidth() - 1; x++){
            Pixel tmp;
            tmp.r = sqrt((rowDY[x].r * rowDY[x].r) + (rowDX[x].r * rowDX[x].r));
            tmp.g = sqrt((rowDY[x].g * rowDY[x].g) + (rowDX[x].g * rowDX[x].g));
            tmp.b = sqrt((rowDY[x].b * rowDY[x].b) + (rowDX[x].b * rowDX[x].b));
            rowDY.setPixel(tmp, x);
        }
        derv.setRow(rowDY, y);
    }


    derv.Write();

    //grayf1.Write();
    //grayf2.Write();

    /*
        I(x, y, t) = (x + deltaX, y + deltaY, t + deltaT)
    */
    for(int y = 0; y < f1->getHeight(); y++){
        PixelRow row1 = *(f1->getRow(y));
        PixelRow row2 = *(f2->getRow(y));
        for(int x = 1; x < f1->getWidth() - 1; x++){
            Pixel tmp;
            float I = (row2[x].r - row1[x].r);
            tmp.r = (1/I);
            tmp.b = (1/I);
            tmp.g = (1/I);
            row1.setPixel(tmp, x);
        }
        intermediate.setRow(row1, y);
    }
    
    intermediate.Write();

    /*for(int y = 0; y < f1->getHeight(); y++){
        PixelRow row1 = *(f1->getRow(y));
        PixelRow row2 = *(f2->getRow(y));
        PixelRow rowDY = *(dervY.getRow(y));
        PixelRow rowDX = *(dervX.getRow(y));
        PixelRow replace = *(greenScreenReplace.getRow(y));
        for(int x = 1; x < f1->getWidth() - 1; x++){
            Pixel tmp;
            float thing = ((((rowDY[x].r) / 255.0f)) + ((rowDY[x].g) / 255.0f) + ((rowDY[x].b) / 255.0f)) / 3;
            tmp.r = ((row2[x].r / thing) + (row1[x].r)) / 2;
            tmp.g = ((row2[x].g / thing) + (row1[x].g)) / 2;
            tmp.b = ((row2[x].b / thing) + (row1[x].b)) / 2;
            row1.setPixel(tmp, x);
        }
        out.setRow(row1, y);
    }*/
    for(int y = 0; y < f1->getHeight(); y++){
        PixelRow row1 = *(f1->getRow(y));
        PixelRow row2 = *(f2->getRow(y));
        PixelRow rowDY = *(dervY.getRow(y));
        PixelRow rowDX = *(dervX.getRow(y));
        for(int x = 0; x < f1->getWidth(); x++){
            Pixel tmp;
            float iX = rowDX[x].r;
            float iY = rowDY[x].r;
            float iXY = iX * iY;
            float iT = 0.4;
            float deter = 1 / ((iX * iY) - (iXY * iXY));

            float inv1 = deter * iX;
            float inv2 = deter * iXY;
            float inv4 = deter * iY;

            float vX = (inv1 * (-1 * iX * iT)) + (inv2 * (-1 * iY * iT)); 
            float vY = (inv4 * (-1 * iX * iT)) + (inv2 * (-1 * iY * iT)); 

            float mag = sqrt((vX * vX) + (vY * vY));

            tmp.r = mag;
            tmp.g = mag;
            tmp.b = mag;
            

            row1.setPixel(tmp, x);
        }
        out.setRow(row1, y);
    }

    out.Write();
}