#include <iostream>
#include <opencv2/opencv.hpp>
#include <complex>
using namespace cv;
#define MAX_ITER 80
int mandelbrot(std::complex<double> c) {
    std::complex<double> z = 0;
    int n = 0;
    while(abs(z) <=2 && n < MAX_ITER) {
        z = z * z + c;
        n += 1;
    }
    return n;
}

void newFractals() {
    Mat image(20001, 20001, CV_8UC3, Scalar(0, 0, 0));
    for (int a = -10000; a <= 10000; a++) {
        for (int b = -10000; b <= 10000; b++) {
            using namespace std::complex_literals;
            std::complex<double> c = double(a) / 10000 + 1i * (double(b) / 10000);
            Vec3b color = image.at<Vec3b>(Point(a + 10000, b + 10000));
            int value = mandelbrot(c);
            color[0] = value;
            color[1] = value;
            color[2] = value;
            image.at<Vec3b>(Point(a + 10000, b + 10000)) = color;
        }
    }
    imwrite("fraktal.png", image);
}



int main()
{
    Mat src = imread(samples::findFile("fraktal.png"), IMREAD_COLOR); // Load an image
    Mat src_gray, dst;
    int threshold_value=25, max_binary_value=255, threshold_type=1;
    cvtColor(src, src_gray, COLOR_BGR2GRAY); // Convert the image to Gray
    threshold(src_gray, dst, threshold_value, max_binary_value, threshold_type);
    imwrite("fraktal_threshold.png", dst);
}