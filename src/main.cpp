#include <iostream>
#include <filesystem>
#include <set>
#include <thread>

#include <vfxtools.h>

int finished1, finished2, finished3, finished4, finished5;

//int done = 0;
namespace fs = std::filesystem;

VfxTools tool;

void batchRun(int start, int end, std::vector<Frame*> frames, int* finished){
    
    for(int i  = start + 1; i < end; i++){
        *finished = (int)(((i - start) / (float)(end - start)) * 100.0f);
        //printf("(%d %d) | Percent done: %d\n", start, end, (int)((done / (float)frames.size()) * 100.0f));
        //printf("Thead (%d %d) is %d done\n", start, end, (int)(((float)i/(float)end) * 100.0f));
        tool.OpticalFlow(frames[i - 1], frames[i]);
        //done++;
    }
    *finished = (int)((end / (float)end) * 100.0f);
    printf("Thread (%d %d) finished!\n", start, end);
    return;
}

int main(int args, char** argv){
    if(args < 3){
        printf("Not enough args.\n");
        return -1;
    }
    

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

    int batches = frames.size() / 5;
    int start = 0;

    std::thread bat1(batchRun, start, start + batches - 1, frames, &finished1);
    start += batches;
    
    std::thread bat2(batchRun, start, start + batches - 1, frames, &finished2);
    start += batches;

    std::thread bat3(batchRun, start, start + batches - 1, frames, &finished3);
    start += batches;

    std::thread bat4(batchRun, start, start + batches - 1, frames, &finished4);
    start += batches;

    std::thread bat5(batchRun, start, start + batches - 1, frames, &finished5);
    start += batches;

    

    printf("\n\n\n");

    while(1){
        printf("==== PROGRESS ====\n");
        printf("Thread 1 | %d %   \n", finished1);
        printf("Thread 2 | %d %  \n", finished2);
        printf("Thread 3 | %d %  \n", finished3);
        printf("Thread 4 | %d %  \n", finished4);
        printf("Thread 5 | %d %  \n", finished5);
        printf("\x1b[6A");
    }

    bat5.join();
    bat3.join();
    bat1.join();
    bat2.join();
    bat4.join();
    
    

    /*for(int i = 1; i < frames.size(); i++){
        printf("Percent Complete: %d | Frame %s\n", (int)((i/ (float)frames.size()) * 100.0f), frames[i]->getPath().c_str());
        vfxtools.OpticalFlow(frames[i - 1], frames[i]);
    }*/
    system("cp T1/* COMBINED");
    system("cp OUT/* COMBINED");
    return 0;
}