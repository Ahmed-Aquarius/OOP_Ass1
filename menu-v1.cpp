// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name:				phedit.cpp
// Last Modification Date:	    9/10/2023
// Author1 and ID and Group:	Abdelrahman Ahmed Lotfy     20220474    Obidah05@gmail.com 
// Author2 and ID and Group:	Ahmed Hossam ElAlfy         20220016    ahalfy2005@gmail.com
// Author3 and ID and Group:	Mohab Mohammad Abdelwahed   20220472    mohab.fcai@gmail.com
// Teaching Assistant:          .......
// Purpose:                     Application for image processing in bitmap format using c++.



#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;

unsigned char image[SIZE][SIZE];


void loadImage(unsigned char picture[SIZE][SIZE]);
void saveImage();

void black_and_white();
void invert();
void merge_image();
void flip();
void darken_or_lighten();
void rotate_image();
void detectEdges();
void enlarge();
void shrink();
void mirror_by_half();
void shuffle();
void blur();
void crop();
void skewRight();
void skewUp();


int main()
{
    cout << "Ahlan ya user ya habibi\n";
    loadImage(image);

    while(true)
    {
        cout << "Please select a filter to apply or 0 to exit: \n";

        cout << "1- Black & White Filter\n";
        cout << "2- Invert Filter\n";
        cout << "3- Merge Filter\n";
        cout << "4- Flip Image\n";
        cout << "5- Darken and Lighten Image\n";
        cout << "6- Rotate Image\n";
        cout << "7- Detect Image Edges\n";
        cout << "8- Enlarge Image\n";
        cout << "9- Shrink Image\n";
        cout << "a- Mirror 1/2 Image\n";
        cout << "b- Shuffle Image\n";
        cout << "c- Blur Image\n";
        cout << "d- Crop Image\n";
        cout << "e- Skew Image Right\n";
        cout << "f- Skew Image up\n";
        cout << "s- Save the image to a file\n";
        cout << "l- Load another image\n";
        cout << "0- Exit\n";
        cout << '\n';

        char option;
        cin >> option;
        switch (option)
        {
            case '1':
                black_and_white();
                break;
            case '2':
                invert();
                break;
            case '3':
                merge_image();
                break;
            case '4':
                flip();
                break;
            case '5':
                darken_or_lighten();
                break;
            case '6':
                rotate_image();
                break;
            case '7':
                detectEdges();
                break;
            case '8':
                enlarge();
                break;
            case '9':
                shrink();
                break;
            case 'a':
                mirror_by_half();
                break;
            case 'b':
                shuffle();
                break;
            case 'c':
                blur();
                break;
            case 'd':
                crop();
                break;
            case 'e':
                skewRight();
                break;
            case 'f':
                skewUp();
                break;
            case 's':
                saveImage();
                break;
            case 'l':
                loadImage(image);
                break;
            case '0':
                return 0;
            default:
                cout << "Invalid input. Please choose an option from the menu.";
        }

        cout << '\n' << '\n' << '\n';
    }
}


void loadImage (unsigned char picture[SIZE][SIZE]) {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Please enter file name of the image to process: ";
    cin >> imageFileName;
    cout << endl;


    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, picture);
}


void saveImage () {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
    
    cout << "Image saved succesfully";
}




void black_and_white()
{
    cout << "put code here";
}


void invert() {
    //iterate over every pixel
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            //get the complement of the grayvalue of each pixel
            image[i][j] = 255 - image[i][j];
        }
    }
}


void merge_image()
{
    cout << "put code here";
}


void flip()
{
    cout << "put code here";
}


void darken_or_lighten()
{
    cout << "put code here";
}


void rotate_image()
{
    //To rotate an image clockwise by 90 degrees, you have to transpose the matrix by turning the rows into columns and vice versa, then reverse all rows in the matrix

    //rotate the image clockwise by what degree?
    cout << "Rotate (90), (180), (270) or (360) degrees?" << endl;
    int n;
    cin >> n;
    //check for invalid user input
    while(n != 90 && n != 180 && n != 270 && n != 360)
    {
        cout << "Please enter a valid number" << endl;
        cin >> n;
    }

    n /= 90;
    //Rotates image by 90 degrees n times
    while(n > 0)
    {
        //iterate over every pixel below the diagonal of the matrix
        for (int i = 0; i < SIZE; i++) {   
          for (int j = 0; j< i; j++)  {
                //Swaps pixels to switch rows into columns 
                swap(image[i][j], image[j][i]);
            }
        }

        //iterate over every pixel
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE/2; j++) {
                //swaps pixels to reverse the rows
                swap(image[i][j], image[i][255 - j]);
            }
        }
        
        n--;
    }
}




void detectEdges()
{
    cout << "Not implemented yet";
}


void enlarge()
{
    cout << "Not implemented yet";
}


void shrink()
{
    cout << "Not implemented yet";
}


void mirror_by_half()
{
    cout << "Not implemented yet";
}


void shuffle()
{
    cout << "Not implemented yet";
}


void blur()
{
    cout << "Not implemented yet";
}


void crop()
{
    cout << "Not implemented yet";
}


void skewRight()
{
    cout << "Not implemented yet";
}


void skewUp()
{
    cout << "Not implemented yet";
}