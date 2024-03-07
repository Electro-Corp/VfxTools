#include <iostream>
#include <filesystem>
#include <set>

#include <vfxtools.h>


namespace fs = std::filesystem;

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
    /*Frame* frame1 = new Frame(argv[1]);
    Frame* frame2 = new Frame(argv[2]);*/

    std::vector<Frame*> frames;

    std::set<fs::path> sorted_by_name;

    for (auto &entry : fs::directory_iterator("T3"))
        sorted_by_name.insert(entry.path());

    for (const auto & entry : sorted_by_name){
        Frame* frame1 = new Frame(entry);   
        frames.push_back(frame1);
	}
    system("rm OUT/*");
    system("rm INTER/*");
    system("rm COMBINED/*");
    system("rm CONVS/*");
    system("rm CONVSFULL/*");
    printf("\n");
    for(int i = 1; i < frames.size(); i++){
        printf("Percent Complete: %d | Frame %s\n", (int)((i/ (float)frames.size()) * 100.0f), frames[i]->getPath().c_str());
        vfxtools.OpticalFlow(frames[i - 1], frames[i]);
        delete(frames[i-1]);
    }
    system("cp T1/* COMBINED");
    system("cp OUT/* COMBINED");
    return 0;
}