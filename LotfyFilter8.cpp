#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];

void loadImage ();
void saveImage ();
void enlarge();

int main()
{
  loadImage();
  enlarge();
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
void enlarge(){
  unsigned char Large_image[SIZE][SIZE] = {0};
  int n, x, y;

  cout << "Which quarter to enlarge 1, 2, 3 or 4?" << endl;
  cin >> n;
  if(n == 1)
  {
      x = 0;
      y = 0;
  }
  else if(n == 2)
  {
      x = 127;
      y = 0;
  }
  else if(n == 3)
  {
      x = 0;
      y = 127;
  }
  else
  {
      x = 127;
      y = 127;
  }



  for (int i = 0; i < SIZE; i += 2) {
    for (int j = 0; j< SIZE; j += 2) {

        Large_image[i][j] = Large_image[i+1][j+1] = image[(i/2) + y][(j/2) + x];

    }
  }
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j< SIZE; j++) {

        image[i][j] = Large_image[i][j];

    }
  }

}
