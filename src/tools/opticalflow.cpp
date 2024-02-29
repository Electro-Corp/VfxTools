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

/*
    Optical Flow
*/
void OpticalFlow::OpticFlowMain(Frame* f1, Frame* f2){
    Frame out("frame2.png", f1->getWidth(), f1->getHeight());   

    /*for(int y = 0; y < f1->getHeight(); y++){
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
    }*/

    // Find a block in the image
    
    Block tmp;
    // First clump of pixels
    int blockStartX = 302;
    int blockStartY = 203;
    tmp.p1 = {blockStartX, blockStartY};
    tmp.p2 = {-1, -1};

    tmp.pixels1[0] = (*(f1->getRow(blockStartY)))[blockStartX];
    tmp.pixels1[1] = (*(f1->getRow(blockStartY)))[blockStartX + 1];
    tmp.pixels1[2] = (*(f1->getRow(blockStartY + 1)))[blockStartX];
    tmp.pixels1[3] = (*(f1->getRow(blockStartY + 1)))[blockStartX + 1];


    int currentPix = 0;

    // Find the block in the next frame
    for(int y = blockStartY - 5; y < blockStartY; y++){
        for(int x = blockStartX - 5; x < blockStartX; x++){
            if(doesPixelMatch((*(f1->getRow(y)))[x], tmp.pixels1[currentPix])){
                currentPix++;
                tmp.pixels2[currentPix] = (*(f1->getRow(y)))[x];
                tmp.p2 = {x, y};
            }
            if(currentPix % 2 == 0){
                y++;
            }
        }
    }
    for(int y = blockStartY + 2; y < blockStartY + 7; y++){
        for(int x = blockStartX + 2; x < blockStartX + 7; x++){
            if(doesPixelMatch((*(f1->getRow(y)))[x], tmp.pixels1[currentPix])){
                currentPix++;
                tmp.pixels2[currentPix] = (*(f1->getRow(y)))[x];
                tmp.p2 = {x, y};
            }
            if(currentPix % 2 == 0){
                y++;
            }
        }
    }

    printf("%d %d\n%d %d\n", tmp.p1.x, tmp.p1.y, tmp.p2.x, tmp.p2.y);

    out.Write();
}