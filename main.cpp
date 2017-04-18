#include <iostream>
#include <fstream>
#include "image.h"
#include "filter.h"
#include "sobelfilter.h"
using namespace std;

int main()
{
	Image image1(256,256);
        Image newImage(256,256);

        char readFile[] = "./test_images/eye_test_image.jpg";
        char writeFile[] = "./images/outfile.bin";

        image1.readImage(readFile);

        SobelFilter sobelfilter;
        newImage = sobelfilter.process(image1,3,3);

        newImage.writeImage(writeFile);

}
