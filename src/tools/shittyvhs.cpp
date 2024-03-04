/*
*/
#include <tools/shittyvhs.h>


void VHSEffect::initTool(...){
    // It dosen't care about args tbh
    std::cout << "Tool \"VHS Filter\" initilized.\n";
}
void VHS(Frame* f1, Frame* f2);
/*
    Preform Optical Flow between two frames
*/
void VHSEffect::runTool(Frame* f1, Frame* f2){
    assert(f1->getHeight() == f2->getHeight());
    assert(f2->getWidth() == f1->getWidth());
    VHS(f1, f2);
}

/*
    VHS
*/
void VHS(Frame* f1, Frame* f2){
    int num = std::stoi(f2->getPath().erase(f2->getPath().find("T1/"), 3)) - 1;
    Frame out("OUT/" + std::to_string(num), f1->getWidth(), f1->getHeight());   


    /*
        Find intensity of each pixel in image 
        (simpily convert to grayscale)
    */

    Frame grayf1("frame1G.png", f1->getWidth(), f1->getHeight());
    Frame grayf2("frame3G.png", f1->getWidth(), f1->getHeight());

    Frame intermediate("inter.png",f1->getWidth(), f1->getHeight());

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
            float I = abs((row1[x].r + row2[x].r) / 2);
            //float Iy = abs(row1[x].r - row2[x].r);
            tmp.r = (1/I) / 0.01;
            tmp.b = (1/I) / 0.01;
            tmp.g = (1/I) / 0.01;
            row1.setPixel(tmp, x);
        }
        intermediate.setRow(row1, y);
    }
    
    intermediate.Write();

    for(int y = 0; y < f1->getHeight(); y++){
        PixelRow row1 = *(f1->getRow(y));
        PixelRow row2 = *(f2->getRow(y));
        PixelRow row3 = *(intermediate.getRow(y));
        for(int x = 1; x < f1->getWidth() - 1; x++){
            Pixel tmp;
            float thing = row3[x].r;
            tmp.r = ((row2[x].r * thing) + (row1[x].r)) / 2;
            tmp.g = ((row2[x].g * thing) + (row1[x].g)) / 2;
            tmp.b = ((row2[x].b * thing) + (row1[x].b)) / 2;
            row1.setPixel(tmp, x);
        }
        out.setRow(row1, y);
    }

    out.Write();
}