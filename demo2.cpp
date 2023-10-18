// Program: demo2.cpp
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
unsigned char cropImage[SIZE][SIZE];

void loadImage ();
void saveImage ();
void black_and_white();
void flip();
void mirror();
void crop();

int main()
{
  loadImage();
  //black_and_white();
  //flip();
  //mirror();
  //crop();
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

//turns image black and white
void black_and_white() {
    int total=0;
    //sum all pixels
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            total+=image[i][j];
        }
    }
    //divide sum by number to get average gray color level
    int avg = total/(SIZE*SIZE);
  //loop on all pixels
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j< SIZE; j++) {
        //if gray level is greater than average, turn to white. If smaller, turn to black
        if (image[i][j] > avg)
            image[i][j] = 255;
        else
            image[i][j] = 0;
    }
  }
}
//-----------------------------------
//flips image horizontally or vertically
void flip(){
    char flipLetter;
    //enter choice of flip: horizontally or vertically
    cout<<"Flip (h)orizontally or (v)ertically?";
    cin>>flipLetter;

    int temp;
    //flips horizontally
    if(flipLetter=='h'){
        //loop on pixels
        for(int i=0;i<SIZE;i++){
            for(int j=0;j<SIZE/2;j++){
                //flipping process
                temp = image[i][j];
                image[i][j] = image[i][SIZE-j];
                image[i][SIZE-j] = temp;
            }
        }
    }
    //flips vertically
    else if (flipLetter=='v'){
        //loop on pixels
        for(int i=0;i<SIZE/2;i++){
            for(int j=0;j<SIZE;j++){
                //flipping process
                temp = image[i][j];
                image[i][j] = image[SIZE-i][j];
                image[SIZE-i][j] = temp;
            }
        }
    }
}
//--------------------------------------------
//mirrors 1/2 image: left, right, upper or lower
void mirror(){
    char mirrorLetter;
    //enter choice of mirroring: left/right/upper/lower
    cout<<"Mirror (l)eft, (r)ight, (u)pper, (d)own side?";
    cin>>mirrorLetter;

    //mirror left
    if(mirrorLetter=='l'){
        //loops on pixels
        for(int i=0;i<SIZE;i++){
            for(int j=0;j<SIZE/2;j++){
                //mirroring process
                image[i][SIZE-j] = image[i][j];
            }
        }

    }
    //mirror right
    else if(mirrorLetter=='r'){
        //loops on pixels
        for(int i=0;i<SIZE;i++){
            for(int j=0;j<SIZE/2;j++){
                //mirroring process
                image[i][j] = image[i][SIZE-j];
            }
        }
    }
    //mirror upper part
    else if(mirrorLetter=='u'){
        //loops on pixels
        for(int i=0;i<SIZE/2;i++){
            for(int j=0;j<SIZE;j++){
                //mirroring process
                image[SIZE-i][j] = image[i][j];
            }
        }
    }
    //mirror lower part
    else if(mirrorLetter=='d'){
        //loops on pixels
        for(int i=0;i<SIZE/2;i++){
            for(int j=0;j<SIZE;j++){
                //mirroring process
                image[i][j] = image[SIZE-i][j];
            }
        }
    }
}

//------------------------------------------------
void crop(){
    //crops image to take a part of it and leave the rest
    int x,y,l,w;
    //input start position and length and width from user
    cout<<"Enter starting position of pixel in x,y: ";
    cin>>x>>y;
    cout<<"Enter length and width: ";
    cin>>l>>w;
    //clear new 2D array image
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            cropImage[i][j]=255;
        }
    }
    //loop on original image and crop wanted part to the new image
    for(int i=x;i<x+l;i++){
        for(int j=y;j<y+w;j++){
            cropImage[i][j] = image[i][j];
        }
    }

    //put back the wanted part from the 2D array to the original image
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            image[i][j] = cropImage[i][j];
        }
    }
}

