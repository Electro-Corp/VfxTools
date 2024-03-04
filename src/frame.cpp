/*
*/
#include <frame.h>

Frame::Frame(std::string path){
    this->image = png::image<png::rgb_pixel>(path);
    this->width = image.get_width();
    this->height = image.get_height();
    this->path = path;

    // Load pixels
    for(int y = 0; y < height; y++){
        PixelRow pixelRow;
        for(int x = 0; x < width; x++){
            Pixel tmp = {image.get_pixel(x,y).red, image.get_pixel(x,y).green, image.get_pixel(x,y).blue};
            pixelRow.addPixel(tmp);
        }
        this->pixels.push_back(pixelRow);
    }

    std::cout << "Frame from image path " << path << " loaded.\n";
}

Frame::Frame(std::string path, int width, int height){
    this->image = png::image<png::rgb_pixel>(width, height);
    this->width = width;
    this->height = height;
    this->path = path;

    // Make a basic image
    for(float y = 0; y < height; y++){
        this->pixels.push_back(PixelRow());
        for(float x = 0; x < width; x++){
            this->pixels[y].addPixel({x, y, x+ y});
        }
    }
}

PixelRow* Frame::getRow(int y){
    return &(pixels[y]);
}

void Frame::setRow(PixelRow row, int y){
    pixels[y] = row;
}

int Frame::getWidth(){
    return width;
}

int Frame::getHeight(){
    return height;
}

void Frame::Write(){
    //std::cout << "Writing image to " << this->path << "\n";
    for (png::uint_32 y = 0; y < image.get_height(); ++y){
        for (png::uint_32 x = 0; x < image.get_width(); ++x){
            image[y][x] = png::rgb_pixel(this->pixels[y][x].r, this->pixels[y][x].g, this->pixels[y][x].b);
        }
    }
    image.write(this->path);
}

PixelRow* Frame::operator[](int i){
    return &(pixels[i]);
}

std::string Frame::getPath(){
    return path;
}

void PixelRow::addPixel(Pixel p){
    this->pixels.push_back(p);
}

void PixelRow::setPixel(Pixel p, int x){
    this->pixels[x] = p;
}

Pixel PixelRow::operator[](int i){
    return this->pixels[i];
}


PixelRow PixelRow::operator=(PixelRow* other){
    other = this;
}