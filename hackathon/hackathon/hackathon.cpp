#include <iostream>
#include <fstream>
#include <string>
#include <stdint.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include <algorithm>

using std::find_if;
using namespace cv;
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include <unordered_map>
#include <map>

using std::unordered_map;
enum class color
{
    red=0,
    green,
    blue
};
struct pixel_data
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    pixel_data(uint8_t red, uint8_t green, uint8_t blue) : 
        red(red),
        green(green),
        blue(blue)
        {};
 
    bool operator == (const pixel_data & pixel)
    {
        return this->red == pixel.red && this->green == pixel.green && this->blue == pixel.blue;
    }
    struct hash {
        std::size_t operator()(pixel_data const& p) const noexcept
        {
            std::size_t h1 = p.red << (p.green + 7);
            std::size_t h2 = p.blue;
            return h1 ^ (h2 << 1);
        }
    };
    

};
bool operator == (const pixel_data& pixel, const pixel_data& pixel_2)
{
    return pixel_2.red == pixel.red && pixel_2.green == pixel.green && pixel_2.blue == pixel.blue;
};


int main(int argc, char* argv[])
{
   
    int width, height, bpp;

    uint8_t* rgb_image = stbi_load("szyfr_2.png", &width, &height, &bpp, 3);
    if (rgb_image == NULL) {
        return -1;
    }
    std::vector <pixel_data> image;
    for (int i = 0; i <3* width * height; i+=3) {
        pixel_data act_pixel(rgb_image[i], rgb_image[i + 1], rgb_image[i + 2]);
        image.push_back(act_pixel);
    }
    stbi_image_free(rgb_image);
    std::unordered_map<pixel_data, int,pixel_data::hash> color_counter;
    for (auto pixel : image)
    {
        if (color_counter.find(pixel) == color_counter.end()) {
            
            color_counter.insert(std::pair<pixel_data,int>(pixel,0));
        }
        else
        {
            auto it = color_counter.find(pixel);
            it->second++;
        }
    }
    for (auto& pixel : image)
    {
        auto it = color_counter.find(pixel);
        if (it->second >= 1500)
        {
           
            pixel.red = 255;
            pixel.green = 255;
            pixel.blue = 255;
        }
        else
        {
            pixel.red = 0;
            pixel.green = 0;
            pixel.blue = 0;
        }
    }
    uint8_t* just_text_image = new uint8_t[3 * width * height];
    int x = 0;
    for (int i = 0; i < 3 * width * height; i += 3) {

        just_text_image[i] = image[x].red;
        just_text_image[i+1] = image[x].green;
        just_text_image[i+2] = image[x].blue;
        x++;
    }
    stbi_write_jpg("image.png", width, height, 3, just_text_image, width * 3);
    Mat image_to_blur = imread("image.png");
    Mat blurred_image;

    blurred_image.release();
    image_to_blur.release();
    


    
   
}