#include <iostream>
#include <stdint.h>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

int main()
{
	int width, height, bpp;

	uint8_t* rgb_image = stbi_load("szyfr_1.png", &width, &height, &bpp, 3);
	if (rgb_image == NULL) {
		return -1;
	}
	std::vector < int > image;
	for (int i = 0; i < width * height; i++) {
		image.push_back(rgb_image[i]);
	}
	stbi_image_free(rgb_image);
	for (int x : image)
		std::cout << x << std::endl;






	
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
