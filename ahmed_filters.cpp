#include <iostream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;

typedef unsigned char uc;

uc image[SIZE][SIZE];


void loadImage (uc image[SIZE][SIZE]);
void saveImage ();

void merge_image ();
void darken_or_lighten ();
void shrink ();


int main()
{
    loadImage(image);
    shrink();
    saveImage();
    return 0;
}


void loadImage (uc image[SIZE][SIZE]) {
   // Get gray scale image file name
   char imageFileName[100];
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension, then load image
   strcat (imageFileName, ".bmp");

   readGSBMP(imageFileName, image);
}


void saveImage () {
   // Get gray scale image file name
   char imageFileName[100];
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension, then load image
   strcat (imageFileName, ".bmp");

   writeGSBMP(imageFileName, image);
}




void merge_image()
{
    //enter the second image
    unsigned char image2[SIZE][SIZE];
    loadImage(image2);

    //iterate over every pixel
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            //the gray value of the output pixel = the mean of the greyvalues of the 2 merged pixels
            image[i][j] = (image[i][j] + image2[i][j]) / 2;
        }
    }
}


void darken_or_lighten()
{
    //let the user choose whether to darken or lighten the image
    cout << "Do you want to darken or lighten?" << endl << "Press (d) for darkening or (l) for lightening: ";
    char filter;
    cin >> filter;
    bool is_lighten = filter == 'l';

    //iterate over every pixel
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            /*
            * the gray value of the output pixel = 
            * in the case of darkening: half the gray value of the input pixel 
            * int the case of lightening: the gray value of the input pixel + 0.5 * (255 - the gray value of the input pixel)
            */
            image[i][j] = (0.5 * image[i][j]) + (is_lighten * 127);
        }
    }
}


void shrink ()
{
    cout << "shrink to (1/2), (1/3), or (1/4)? ";
    string choice;
    cin >> choice;

    unsigned short shrink_factor = choice[2] - '0';
    int dimension = (int)floor(SIZE/shrink_factor);

    for (int box_vertical = 0, outPixel_vertical = 0; box_vertical < SIZE; box_vertical += shrink_factor, outPixel_vertical++)
    {
        for (int box_horizontal = 0, outPixel_horizontal = 0; box_horizontal < SIZE; box_horizontal += shrink_factor, outPixel_horizontal++)
        {
            unsigned short sumGrayValue = 0;

            for (int i = box_vertical; i < (box_vertical + shrink_factor); i++)
            {
                for (int j = box_horizontal; j < (box_horizontal + shrink_factor); j++)
                {
                    sumGrayValue += image[i][j];

                    if (box_vertical >= dimension-3 || box_horizontal >= dimension-3)
                    {
                        image[i][j] = 255;
                    }
                }
            }

            image[outPixel_vertical][outPixel_horizontal] = sumGrayValue/pow(shrink_factor, 2);
        }
    }
}
