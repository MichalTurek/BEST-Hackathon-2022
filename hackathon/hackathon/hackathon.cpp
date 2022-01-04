#include <iostream>
#include <fstream>
#include <string>
#include <stdint.h>
#include <vector>
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
    int get_key_of_color() const {
        return 256*256 * red + 256 * green + blue;
    }


};
int main()
{
    int width, height, bpp;

    uint8_t* rgb_image = stbi_load("szyfr_1.png", &width, &height, &bpp, 3);
    if (rgb_image == NULL) {
        return -1;
    }
    std::vector <pixel_data > image;
    for (int i = 0; i <3* width * height; i+=3) {
        pixel_data act_pixel(rgb_image[i], rgb_image[i + 1], rgb_image[i + 2]);
        image.push_back(act_pixel);
    }
    stbi_image_free(rgb_image);
    std::unordered_map<int, int> color_counter;
    for (auto pixel : image)
    {
        if (color_counter.find(pixel.get_key_of_color()) == color_counter.end()) {
            
            color_counter.insert(std::pair<int,int>(pixel.get_key_of_color(),0));
        }
        else
        {
            auto it = color_counter.find(pixel.get_key_of_color());
            it->second++;
        }
    }
    for (auto& pixel : image)
    {
        auto it = color_counter.find(pixel.get_key_of_color());
        if (it->second >= 1500)
        {
            pixel.red = 0;
            pixel.green = 0;
            pixel.blue = 0;
        }
        else
        {
            pixel.red = 255;
            pixel.green = 255;
            pixel.blue = 255;
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

    std::vector < std::string > text;
    std::ifstream file ("w_pustyni_i_w_puszczy.txt");
    std::string s;
    if (file.good()) 
    {
        while (file >> s)
        {
            text.push_back(s);
        }

    }




}