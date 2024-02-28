#include <iostream>

#include <vfxtools.h>

int main(int args, char** argv){
    if(args < 3){
        printf("Not enough args.\n");
        return -1;
    }
    VfxTools vfxtools;

    /*  
        Arg fornmat:

        vfxtools [frame1] [frame2] {tool}
    */
    Frame* frame1 = new Frame(argv[1]);
    Frame* frame2 = new Frame(argv[2]);

    vfxtools.OpticalFlow(frame1, frame2);

    return 0;
}