// Program: menu.cpp
// Purpose: Demonstrate use of bmplip for handling
//          bmp colored and grayscale images
//          Program load a gray image and store in another file
// Author:  Mohammad El-Ramly
// Date:    30 March 2018
// Version: 1.0

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"


using namespace std;
unsigned char image[SIZE][SIZE];


void loadImage ();
void saveImage ();
void skew_right ();

int main()
{
  loadImage();
  skew_right();
  saveImage();
  return 0;
}

//_________________________________________
void loadImage () {
   char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readGSBMP(imageFileName, image);
}

//_________________________________________
void saveImage () {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeGSBMP(imageFileName, image);
}

//_________________________________________
void skew_right(){

    //get the degree from the user
    cout << "Please enter the degree to skew right: ";
    float degree;
    cin >> degree;

    //claculate the length that this skewing will add to the vertical dimension
    long long added_length = round (tan (PI * (degree/180.0)) * SIZE);

    //make array aux and whiten all its pixels
    uc aux[SIZE][SIZE + added_length];
    for (int j = 0; j < SIZE + added_length; j++)
    {
        for (int i = 0; i < SIZE; i++)
        {
            aux[i][j] = 255;
        }
    }


    //in "shifting_points", we will store the horizontal coordinates of the pixels at which we will start "lifting" the pixels of the image by one row
    int index = 1, n_shifting_points = added_length % SIZE;
    uc shifting_points[n_shifting_points];
    for (uc &point : shifting_points)
    {
        //the liftment points are distributed evenly via this equation in order to achieve a maximumly smooth and seamless slant
        point = round ((float)(index * SIZE) / (float)(n_shifting_points + 1));
        index++;
    }

    //copy (image) into (aux), and for every row, lift the image up inside aux whenever meeting a liftment point
    for (int j_skewed = (SIZE + added_length -1), j_orig = SIZE - 1, basic_shift_value = added_length / SIZE, basic_shift, specific_shift; j_skewed >= added_length, j_orig >= 0; j_skewed--, j_orig--)
    {
        basic_shift = 0;
        specific_shift = 0;

        for (int i = 0; i < SIZE; i++)
        {
            if (i == shifting_points[specific_shift])
            {
                specific_shift++;
            }
            aux[i][j_skewed - (basic_shift + specific_shift)] = image[i][j_orig];
            basic_shift += basic_shift_value;
        }
    }


    //in (skipped_points), we will store the vertical coordinates of the pixels that whenever we pass by one of them, we shall discard the whole row that it occupies when copying (aux) into (image), which would effectively shrink (aux) to fit inside (image)
    int skip = 1;
    short skipped_points[added_length];
    for (short &point : skipped_points)
    {
        //the skipped points are distributed evenly via this equation in order to minimize the feeling of missing rows
        point = floor((float)(skip * (SIZE + added_length)) / (float)(added_length + 1));
        skip++;
    }

    //copy (aux) into (image), and for every row, if a skipped point lies in it, skip this row
    skip = 0;
    for (int j_aux = 0, j_image = 0; j_aux < SIZE + added_length; j_aux++)
    {
        if (j_aux == skipped_points[skip])
        {
            skip++;
            continue;
        }

        for (int i = 0; i < SIZE; i++)
        {
            image[i][j_image] = aux[i][j_aux];
        }

        j_image++;
    }
}






