#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <stdint.h>
#include <vector>
#include <unordered_map>
#include <thread>
#include <chrono>
#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

#define NUM_OF_CHANELLS 3

struct Pixel {
  uint8_t R;
  uint8_t G;
  uint8_t B;

  Pixel() : R(0), G(0), B(0) {};
  Pixel(uint8_t R, uint8_t G, uint8_t B) : R(R), G(G), B(B) {};

  int getValue() const {
    return R + G + B;
  }
};

struct PixelHash {
  std::size_t operator()(Pixel const& p) const noexcept
  {
    std::size_t h1 = p.R << (p.G + 7);
    std::size_t h2 = p.B;
    return h1 ^ (h2 << 1); // or use boost::hash_combine
  }
};

bool operator==(const Pixel& lhs, const Pixel& rhs) {
  return lhs.R == rhs.R && lhs.G == rhs.G && lhs.B == rhs.B;
}

void assignPixelsToVector(std::vector<Pixel>& output, const uint8_t input[], const std::size_t& size) {
  Pixel p;
  for (std::size_t i = 0; i < size; i++) {
    int tmp = i % 3;
    switch (tmp) {
    case 0: {
      p.R = input[i];
      break;
    }
    case 1: {
      p.G = input[i];
      break;
    }
    case 2: {
      p.B = input[i];
      output.push_back(p);
      break;
    }
    }
  }
}

class Timer {
public:
  void start() {
    m_StartTime = std::chrono::system_clock::now();
    m_bRunning = true;
  }

  void stop() {
    m_EndTime = std::chrono::system_clock::now();
    m_bRunning = false;
  }

  double elapsedMilliseconds() {
    std::chrono::time_point<std::chrono::system_clock> endTime;

    if (m_bRunning)
    {
      endTime = std::chrono::system_clock::now();
    }
    else
    {
      endTime = m_EndTime;
    }

    return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
  }

  double elapsedSeconds()
  {
    return elapsedMilliseconds() / 1000.0;
  }

private:
  std::chrono::time_point<std::chrono::system_clock> m_StartTime;
  std::chrono::time_point<std::chrono::system_clock> m_EndTime;
  bool                                               m_bRunning = false;
};
std::vector <std::string> decryption(std::string encoded_string, int key)
{
  std::string alfabet1 = "a¹bcædeêfghijkl³mnñoópqrsœtuvwxyzŸ¿";
  std::string alfabet2 = "A¥BCÆDEÊFGHIJKL£MNÑOÓPQRSŒTUVWXYZ¯";
  std::string przyklad = encoded_string;

  std::string przyklad2 = przyklad;
  for (int i = 0; i < przyklad.length(); i++) {
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
    j += key;
    j = j % 35;
    if (wielka) {
      przyklad2[i] = alfabet2[j];
    }
    else {
      przyklad2[i] = alfabet1[j];
    }
  }

  std::vector <std::string> szyfr;
  szyfr.push_back("");
  int j = 0;
  for (int i = 0; i < przyklad2.length(); i++) {
    if (przyklad2[i] == ' ') {
      szyfr.push_back("");
      j++;
    }
    else if ((przyklad2[i] >= 'a' && przyklad2[i] <= 'z') || (przyklad2[i] >= 'A' && przyklad2[i] <= 'Z')) {
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
  return szyfr;
}
int main(int argc, char* argv[]) {
  Timer timer;
  timer.start();
  while (timer.elapsedSeconds() < 10.0) {
    if (argc < 2) return -1;
    int width, height, bpp;

    uint8_t* rgb_image = stbi_load(argv[1], &width, &height, &bpp, NUM_OF_CHANELLS);
    if (rgb_image == NULL) {
      return -1;
    }

    const float THRESHOLD_RATE = (width * height) * 0.005;

    std::vector<Pixel> image;
    assignPixelsToVector(image, rgb_image, width * height * NUM_OF_CHANELLS);
    stbi_image_free(rgb_image);
    std::vector<Pixel> output;

    std::unordered_map<Pixel, unsigned int, PixelHash> histogram;
    for (Pixel p : image) {
      histogram[p]++;
    }

    unsigned int avrage = 0;
    for (auto p : histogram) {
      std::cout << "Pixel: " << std::hex << p.first.getValue() << "\t";
      std::cout << "Occurrences: " << std::dec << p.second << "\n";
    }

    for (Pixel p : image) {
      if (histogram[p] > THRESHOLD_RATE) {
        output.push_back(Pixel(0, 0, 0));
      }
      else {
        output.push_back(Pixel(UINT8_MAX, UINT8_MAX, UINT8_MAX));
      }
    }

    stbi_write_png("output.png", width, height, NUM_OF_CHANELLS, output.data(), NUM_OF_CHANELLS * width);

    FILE* tmp = fopen("tmp.txt", "w");
    tmp = _popen("tesseract output.png tmp.txt.txt -l pol --psm 6 -c load_system_dawg=0 -c load_freq_dawg=0", "w");
    std::fstream encodedStrem((char*)tmp, std::fstream::in | std::fstream::out | std::fstream::app);
    fclose(tmp);
    std::string inputLine;
    std::string encoded_string;
    while (std::getline(encodedStrem, inputLine)) {
      encoded_string += inputLine;
    }

    std::cout << encoded_string << "\n";
    std::vector < std::string > text;
    std::ifstream file("w_pustyni_i_w_puszczy.txt");
    std::string s;
    if (file.good())
    {
      while (file >> s)
      {
        text.push_back(s);
      }
    }

    int key = 17;
    std::vector<std::string> decrypted_text = decryption(encoded_string, key);
    std::vector<std::string*> possible_solutions;
    std::vector<int> possible_solution_pos;
    int i = 0;
    int first_pos = 0;

    //finding all possible solutions
    while (size(possible_solutions) == 0 && size(decrypted_text) > i)
    {
      first_pos = 0;
      for (auto word : text)
      {
        if (decrypted_text[i] == word && size(decrypted_text[i]) > 1)
        {
          possible_solutions.push_back(&word);

          possible_solution_pos.push_back(first_pos - i);
        }
        first_pos++;
      }
      if (size(decrypted_text) == i + 1)
      {
        key++;
        decrypted_text = decryption(encoded_string, key);
        i = -1;
      }
      i++;
    }
    std::vector<std::string*> possible_solutions_cpy = possible_solutions;
    int temp = possible_solution_pos[0];
    while (size(possible_solutions) <= 1)
    {
      //to do later
    }
    std::cout << possible_solution_pos[0] << " " << possible_solution_pos[0] + size(decrypted_text) << std::endl;
    std::cout << text[possible_solution_pos[0]] << std::endl;
    break;
  }
  return 0;
}
