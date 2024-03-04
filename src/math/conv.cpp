/*
    Convolution
*/
#include <math/conv.h>

int convS = 0;

Frame Math::conv(Frame input, double kernel[3][3]){
    Frame out(std::string{"CONVS/conv" + std::to_string(convS) + ".png"}, input.getWidth(), input.getHeight());
    /*for(int y = 0; y < input.getHeight(); y++){
        PixelRow row1 = *(input.getRow(y));
        PixelRow outRow = *(out.getRow(y));

        
        for(int x = 0; x < input.getWidth(); x++){
            Pixel tmp;
            // Calculate convolution at pixel
            double accR = 0, accB = 0, accG = 0;
            for(int kY = 0; kY < 3; kY++){
                for(int kX = 0; kX < 3; kX++){
                    accB += kernel[kY][kX] * row1[x].b;
                    accR += kernel[kY][kX] * row1[x].r;
                    accG += kernel[kY][kX] * row1[x].g;
                }
            }

            //getchar();
            //std::cout << "in the end it was " << acc << "\n";
            tmp.r = accR;
            tmp.g = accB;
            tmp.b = accG;
            outRow.setPixel(tmp, x);
        }
        out.setRow(outRow, y);
    }*/
    int pX = 0, pY = 0;
    for(int y = 1; y < input.getHeight() - 1; y++){
        PixelRow row = *(out.getRow(pY++));
        pX = 0;

        for(int x = 1; x < input.getWidth() - 1; x++){
            Pixel tmp;
            float accR = 0, accB = 0, accG = 0;
            for(int i = 0; i < 3; i++){
                accR += (*input[y - 1])[(x - 1) + i].r * kernel[0][i];
                accG += (*input[y - 1])[(x - 1) + i].g * kernel[0][i];
                accB += (*input[y - 1])[(x - 1) + i].b * kernel[0][i];
            }
            for(int i = 0; i < 3; i++){
                accR += (*input[y])[(x - 1) + i].r * kernel[1][i];
                accG += (*input[y])[(x - 1) + i].g * kernel[1][i];
                accB += (*input[y])[(x - 1) + i].b * kernel[1][i];
            }
            for(int i = 0; i < 3; i++){
                accR += (*input[y + 1])[(x - 1) + i].r * kernel[2][i];
                accG += (*input[y + 1])[(x - 1) + i].g * kernel[2][i];
                accB += (*input[y + 1])[(x - 1) + i].b * kernel[2][i];
            }
            row.setPixel({accR, accG, accB}, pX++);
        }
        
        out.setRow(row, pY);
    }
    Pixel tmp = (*input[1])[1];
    out.Write();
    convS++;
    return out;
}