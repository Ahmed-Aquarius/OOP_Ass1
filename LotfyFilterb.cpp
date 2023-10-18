#include <iostream>
#include <fstream>
#include <cstring>
#include <set>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];

void loadImage ();
void saveImage ();
void doSomethingForImage ();

int main()
{
  loadImage();
  doSomethingForImage();
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
void doSomethingForImage() {
    unsigned char Shuffle_image[SIZE][SIZE] = {0} ;
    set <int> quarters = {1, 2, 3, 4};
    int n1 , n2 , n3 , n4, x, y ;
    cout << "Please enter new order\n";
    cin >> n1;
    // rejects incorrect input
    while(quarters.count(n1) == 0)
    {
        cout << "please enter a valid order number\n";
        cin >> n1;
    }
    // checks which quarter was input and adjust x and y accordingly
    if(n1 == 1)
    {
        x = 0;
        y = 0;
    }
    else if(n1 == 2)
    {
        x = 127;
        y = 0;
    }
    else if(n1 == 3)
    {
        x = 0;
        y = 127;
    }
    else
    {
        x = 127;
        y = 127;
    }
    // loops over every pixel in 1st quarter in shuffled image
    for(int i = 0; i < SIZE/2; i++)
    {
        for(int j = 0; j < SIZE/2; j++)
        {
            // puts pixel into shuffled image
            Shuffle_image[i][j] = image[i + y][j + x];

        }
    }
    // removes number to prevent repeated quarters
    quarters.erase(n1);
    cin >> n2;
    // rejects incorrect input
    while(quarters.count(n2) == 0)
    {
        cout << "please enter a valid order number\n";
        cin >> n2;
    }
    // checks which quarter was input and adjust x and y accordingly
    if(n2 == 1)
    {
        x = 127;
        y = 0;
    }
    else if(n2 == 2)
    {
        x = 0;
        y = 0;
    }
    else if(n2 == 3)
    {
        x = 127;
        y = 127;
    }
    else
    {
        x = 0;
        y = 127;
    }
    // loops over every pixel in 2nd quarter in shuffled image
    for(int i = 0; i < SIZE/2; i++)
    {
        for(int j = 127; j < SIZE; j++)
        {
            // the subtraction was done to be able to get quarters before 127 where X or Y could be 0
            Shuffle_image[i][j] = image[i + y][j - x];
        }
    }
    quarters.erase(n2);
    cin >> n3;
    while(quarters.count(n3) == 0)
    {
        cout << "please enter a valid order number\n";
        cin >> n3;
    }
    if(n3 == 1)
    {
        x = 0;
        y = 127;
    }
    else if(n3 == 2)
    {
        x = 127;
        y = 127;
    }
    else if(n3 == 3)
    {
        x = 0;
        y = 0;
    }
    else
    {
        x = 127;
        y = 0;
    }
    for(int i = 127; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE/2; j++)
        {
            Shuffle_image[i][j] = image[i - y][j + x];
        }
    }
    quarters.erase(n3);
    cin >> n4;
    while(quarters.count(n4) == 0)
    {
        cout << "please enter a valid order number\n";
        cin >> n4;
    }
    if(n4 == 1)
    {
        x = 127;
        y = 127;
    }
    else if(n4 == 2)
    {
        x = 0;
        y = 127;
    }
    else if(n4 == 3)
    {
        x = 127;
        y = 0;
    }
    else
    {
        x = 0;
        y = 0;
    }
    for(int i = 127; i < SIZE; i++)
    {
        for(int j = 127; j < SIZE; j++)
        {
            Shuffle_image[i][j] = image[i - y][j - x];
        }
    }
    // loops over every pixel
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            // places shuffled image back into original image
            image[i][j] = Shuffle_image[i][j];
        }
    }



}




