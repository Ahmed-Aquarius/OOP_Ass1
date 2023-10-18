#include <iostream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

#define PI 3.14159265

using namespace std;

typedef unsigned char uc;

uc image[SIZE][SIZE];


void loadImage (uc image[SIZE][SIZE]);
void saveImage ();

void merge_image ();
void darken_or_lighten ();
void shrink ();
void blur ();
void skewUp ();
void skewRight ();

/*void shrink_and_blur ();
void blur_v1();
void blur_v2();
void slide_vertically (uc i, short &vertical_sum, const uc aux[SIZE][SIZE]);
void slide_horizontally (uc i, uc j, short &horizontal_sum, const uc aux[SIZE][SIZE]);
short get_n_summed_pixels (uc i, uc j);*/


int main()
{
    loadImage(image);
    blur();
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


void shrink()
{
    //get the shrink factor
    cout << "shrink to (1/2), (1/3), or (1/4)? ";
    string choice;
    cin >> choice;
    unsigned short shrink_factor = choice[2] - '0';

    //form an auxilary matrix (aux) and whiten all its pixels
    uc aux[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            aux[i][j] = 255;
        }
    }

    //from every square of side length == shrink_factor, add only the lower-right-most pixel to the (aux) matrix
    for (int i = shrink_factor-1, v = 0; i < SIZE; i += shrink_factor, v++)
    {
        for (int j = shrink_factor-1, h = 0; j < SIZE; j += shrink_factor, h++)
        {
            aux[v][h] = image[i][j];
        }
    }

    //copy the (aux) matrix to the (image) matrix
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = aux[i][j];
        }
    }
}


void blur ()
{
    cout << "enter the degree of blurring you want (the numbers starting from 1 and going ascendingly represent ascending degrees of blurring): ";
    short blur_degree;
    cin >> blur_degree;

    //make a copy of (image) into (aux)
    uc aux[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            aux[i][j] = image[i][j];
        }
    }

    short sum, n_pixels;

    //iterate over every pixel
    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x < SIZE; x++)
        {
            sum = n_pixels = 0;

            //for every pixel, add the gray values of all the pixels within the square whose center is the pixel that's being iterated over currently by the outer nested loop, and whose side length = (2 * blur_degree + 1)
            for (int i = -1 * blur_degree; i <= blur_degree; i++)
            {
                for (int j = -1 * blur_degree; j <= blur_degree; j++)
                {
                    //this condition ensures that no "out-of-bounds" error occurs. as this may happen when summing a square whose center is a pixel near the edge of the image
                    if (y+i >= 0 && y+i <= 255 && x+j >= 0 && x+j <= 255)
                    {
                        sum += aux[y+i][x+j];
                        n_pixels++;
                    }
                }
            }

            //equate the gray value of the pixel with the average of the pixels of its surrounding square.
            image[y][x] = sum / n_pixels;
        }
    }
}


void skewUp ()
{
    //get the degree from the user
    cout << "Please enter the degree to skew Up: ";
    float degree;
    cin >> degree;

    //claculate the length that this skewing will add to the vertical dimension
    long long added_length = round (tan (PI * (degree/180.0)) * SIZE);

    //make array aux and whiten all its pixels
    uc aux[SIZE + added_length][SIZE];
    for (int i = 0; i < SIZE + added_length; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            aux[i][j] = 255;
        }
    }


    //in "lifting_points", we will store the horizontal coordinates of the pixels at which we will start "lifting" the pixels of the image by one row
    int index = 1, n_lifting_points = added_length % SIZE;
    uc lifting_points[n_lifting_points];
    for (uc &point : lifting_points)
    {
        //the liftment points are distributed evenly via this equation in order to achieve a maximumly smooth and seamless slant
        point = round ((float)(index * SIZE) / (float)(n_lifting_points + 1));
        index++;
    }

    //copy (image) into (aux), and for every row, lift the image up inside aux whenever meeting a liftment point
    for (int i_skewed = (SIZE + added_length -1), i_orig = SIZE - 1, basic_lift_value = added_length / SIZE, basic_lift, specific_lift; i_skewed >= added_length, i_orig >= 0; i_skewed--, i_orig--)
    {
        basic_lift = 0;
        specific_lift = 0;

        for (int j = 0; j < SIZE; j++)
        {
            if (j == lifting_points[specific_lift])
            {
                specific_lift++;
            }
            aux[i_skewed - (basic_lift + specific_lift)][j] = image[i_orig][j];
            basic_lift += basic_lift_value;
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
    for (int i_aux = 0, i_image = 0; i_aux < SIZE + added_length; i_aux++)
    {
        if (i_aux == skipped_points[skip])
        {
            skip++;
            continue;
        }

        for (int j = 0; j < SIZE; j++)
        {
            image[i_image][j] = aux[i_aux][j];
        }

        i_image++;
    }
}


void skewRight ()
{
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