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

    uint8_t* rgb_image = stbi_load("szyfr_2.png", &width, &height, &bpp, 3);
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

   

    std::string alfabet1 = "a¹bcædeêfghijkl³mnñoópqrsœtuvwxyzŸ¿";
    std::string alfabet2 = "A¥BCÆDEÊFGHIJKL£MNÑOÓPQRSŒTUVWXYZ¯";
    std::string przyklad = "êuhœe tph¿¹h smgikm æê³œbg rhuhœb h tphuw æpkpm";
    std::cout << przyklad << std::endl;
    
    std::string przyklad2 = przyklad;
    for (int i = 0; i < przyklad.length() ; i++) {
        if (przyklad[i] == ' ') {
            continue;
        }
        int j = 0;
        bool wielka = false;
        while (true) {
            if (alfabet1[j] == przyklad[i]) {
                break;
            }
            if (alfabet2[j] == przyklad[i]) {
                wielka = true;
                break;
            }
            j++;
        }
        int x = 25;
        j += x;
        j = j % 35;
        if (wielka) {
            przyklad2[i] = alfabet2[j];
        }
        else {
            przyklad2[i] = alfabet1[j];
        }
    }

    std::cout << przyklad2 << std::endl;
    


















    std::vector <std::string> szyfr;
    szyfr.push_back("");
    int j = 0;
    for (int i = 0; i < przyklad2.length(); i++) {
        if (przyklad2[i] == ' ') {
            szyfr.push_back("");
            j++;
        }
        else if ((przyklad2[i] >= 'a' && przyklad2[i] <='z') || (przyklad2[i] >= 'A' && przyklad2[i] <= 'Z')) {
            szyfr[j].push_back(przyklad2[i]);
        }
        else if (przyklad2[i] == '¹') {
            szyfr[j].push_back(0xC4);
            szyfr[j].push_back(0x85);
        }
        else if (przyklad2[i] == 'ê') {
            szyfr[j].push_back(0xC4);
            szyfr[j].push_back(0x99);
        }
        else if (przyklad2[i] == 'æ') {
            szyfr[j].push_back(0xC4);
            szyfr[j].push_back(0x87);
        }
        else if (przyklad2[i] == '³') {
            szyfr[j].push_back(0xC5);
            szyfr[j].push_back(0x82);
        }
        else if (przyklad2[i] == 'ñ') {
            szyfr[j].push_back(0xC5);
            szyfr[j].push_back(0x84);
        }
        else if (przyklad2[i] == 'ó') {
            szyfr[j].push_back(0xC3);
            szyfr[j].push_back(0xB3);
        }
        else if (przyklad2[i] == 'Ÿ') {
            szyfr[j].push_back(0xC5);
            szyfr[j].push_back(0xBA);
        }
        else if (przyklad2[i] == '¿') {
            szyfr[j].push_back(0xC5);
            szyfr[j].push_back(0xBC);
        }
        else if (przyklad2[i] == 'œ') {
            szyfr[j].push_back(0xC5);
            szyfr[j].push_back(0x9B);
        }
        else if (przyklad2[i] == '¥') {
            szyfr[j].push_back(0xC4);
            szyfr[j].push_back(0x84);
        }
        else if (przyklad2[i] == 'Ê') {
            szyfr[j].push_back(0xC4);
            szyfr[j].push_back(0x98);
        }
        else if (przyklad2[i] == 'Æ') {
            szyfr[j].push_back(0xC4);
            szyfr[j].push_back(0x86);
        }
        else if (przyklad2[i] == '£') {
            szyfr[j].push_back(0xC5);
            szyfr[j].push_back(0x81);
        }
        else if (przyklad2[i] == 'Ñ') {
            szyfr[j].push_back(0xC5);
            szyfr[j].push_back(0x83);
        }
        else if (przyklad2[i] == 'Ó') {
            szyfr[j].push_back(0xC3);
            szyfr[j].push_back(0x93);
        }
        else if (przyklad2[i] == '') {
            szyfr[j].push_back(0xC5);
            szyfr[j].push_back(0xB9);
        }
        else if (przyklad2[i] == '¯') {
            szyfr[j].push_back(0xC5);
            szyfr[j].push_back(0xBB);
        }
        else if (przyklad2[i] == 'Œ') {
            szyfr[j].push_back(0xC5);
            szyfr[j].push_back(0x9A);
        }
        else {
            szyfr[j].push_back('?');
        }
    }
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
    int begin = 0, end;
    /*for (auto word : text) {
        std::cout << word << ' ';
    }
    std::cout << std::endl;
    for (auto word : szyfr) {
        std::cout << word << ' ';
    }*/
    












    while (begin < text.size()) {
        if (text[begin] == szyfr[0]) {
            bool found = true;
            for (int i = 0; i < szyfr.size(); i++) {
                if (text[begin + i] != szyfr[i]) {
                    found = false;
                    break;
                }
                end++;
            }
            if (found) {    
                break;
            }
            
        }

        begin++;
        end = begin;

    }
    begin++;
    end++;
    std::cout << begin << ' ' << end << std::endl;
    

}