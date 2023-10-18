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
void skew_up ();

/*void shrink_and_blur ();
void blur_v1();
void blur_v2();
void slide_vertically (uc i, short &vertical_sum, const uc aux[SIZE][SIZE]);
void slide_horizontally (uc i, uc j, short &horizontal_sum, const uc aux[SIZE][SIZE]);
short get_n_summed_pixels (uc i, uc j);*/


int main()
{
    loadImage(image);
    skew_up();
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

    //from every square of side length == shrink_factor, add only the lowerleft most pixel to the (aux) matrix
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
    cout << "enter the degree of blurring you want (the numbers starting from 1 and goinf ascendingly represent ascending degrees of blurring): ";
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
    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x < SIZE; x++)
        {
            sum = n_pixels = 0;

            for (int i = -1 * blur_degree; i <= blur_degree; i++)
            {
                for (int j = -1 * blur_degree; j <= blur_degree; j++)
                {
                    if (y+i >= 0 && y+i <= 255 && x+j >= 0 && x+j <= 255)
                    {
                        sum += aux[y+i][x+j];
                        n_pixels++;
                    }
                }
            }

            image[y][x] = sum / n_pixels;
        }
    }
}


void skew_up ()
{
    cout << "Please enter the degree to skew Up: ";
    float degree;
    cin >> degree;

    int added_length = round (tan (PI * (degree/180.0)) * SIZE);

    //make a copy of (image) into (aux)
    uc aux[SIZE+added_length][SIZE];

    for (int i = 0; i < SIZE + added_length; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            aux[i][j] = 255;
        }
    }

    int lifted_distance = 1;
    uc liftment_points[added_length];
    for (uc &point : liftment_points)
    {
        point = round ((float)(lifted_distance * SIZE) / (float)(added_length + 1));
        lifted_distance++;
    }

    for (int skewed_v = (SIZE + added_length -1), orig_v = SIZE - 1; skewed_v >= added_length, orig_v >= 0; skewed_v--, orig_v--)
    {
        lifted_distance = 0;
        for (int j = 0; j < SIZE; j++)
        {
            if (j == liftment_points[lifted_distance])
            {
                lifted_distance++;
            }
            aux[skewed_v - lifted_distance][j] = image[orig_v][j];
        }
    }

    int skip = 1;
    short skipped_points[added_length];
    for (short &point : skipped_points)
    {
        point = floor((float)(skip * (SIZE + added_length)) / (float)(added_length + 1));
        skip++;
    }

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


/*
void blur_v1 ()
{
    //make a copy of (image) into (aux)
    uc aux[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            aux[i][j] = image[i][j];
        }
    }

    //the window sliding technique is used here.
    //The first step to implement this technique is to find the sum of the initial "window", which is here the upperleftmost squre of side length 2 pixels, and store it in (seed_sum)
    short seed_sum = 0;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            seed_sum += aux[i][j];
        }
    }
    
    //(vertical_sum) will represent the sum of the pixels of the window whose center is the very first pixel of the specific row which the loop iterates over at a given iteration. This window slides vertically
    //(horizontal_sum) will represent the sum of the pixels of the windows whose centers are the pixels of the specific row which the loop iterates over at a given iteration. This window slides horizontally
    short vertical_sum = seed_sum, horizontal_sum;
    for (int i = 0; i < SIZE; i++)
    {
        //we won't slide_vertically only for the first row, because we already did it in seed_sum 
        if (i != 0)
        {
            //this function adjusts the value of (vertical_sum), as the loop iterates over all rows
            slide_vertically(i, vertical_sum, aux);
        }

        //the main idea of blurring. we sum the gray value of the current pixel with all the pixels surrounding it, then divide them by the number, to get the average gray value around and including the pixel 
        image[i][0] = vertical_sum / get_n_summed_pixels(i, 0);

        //the initial value of the horizontal_sum is the sum of the window at the beggining of the row
        horizontal_sum = vertical_sum;

        //we start from j = 1 because we have already found the sum of the window at j = 0 when finding vertical_sum
        for (int j = 1; j < SIZE; j++)
        {
            //this function adjusts the value of (horizontal_sum), as the loop courses over all columns
            slide_horizontally(i, j, horizontal_sum, aux);

            image[i][j] = horizontal_sum / get_n_summed_pixels(i, j);
        }
    }
}
*/


/*void shrink_and_blur()
{
    //get the shrink factor
    cout << "shrink to (1/2), (1/3), or (1/4)? ";
    string choice;
    cin >> choice;

    unsigned short shrink_factor = choice[2] - '0';
    //the side length of the square that the shrinked image will occupy
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
}*/


/*void slide_vertically (uc i, short &vertical_sum, const uc aux[SIZE][SIZE])
{
    //those conditions are put to prevent going out of bounds

    if (i+1 <= 255)
    {
        //the added part of the window when sliding
        vertical_sum += aux[i+1][0] + aux[i+1][1];
    }

    if (i-2 >= 0)
    {
        //the discarded part of the window when sliding
        vertical_sum -= aux[i-2][0] + aux[i-2][1];
    }

}


void slide_horizontally (uc i, uc j, short &horizontal_sum, const uc aux[SIZE][SIZE])
{
    //those conditions are put to prevent going out of bounds

    //the added part to window (the right side)
    if (j+1 <= 255)
    {
        //just to the right
        horizontal_sum += aux[i][j+1];
        //upper right
        if (i-1 >= 0)
        {
            horizontal_sum += aux[i-1][j+1];
        }
        //lower right
        if (i+1 <= 255)
        {
            horizontal_sum += aux[i+1][j+1];
        }
    }

    //the discarded part of the window (the left side)
    if (j-2 >= 0)
    {
        //just to the left
        horizontal_sum -= aux[i][j];
        //upper left
        if (i-1 >= 0)
        {
            horizontal_sum -= aux[i-1][j-2];
        }
        //lower left
        if (i+1 <= 255)
        {
            horizontal_sum -= aux[i+1][j-2];
        }
    }
}*/


/*short get_n_summed_pixels (uc i, uc j)
{
    //get the # of the added pixels in a window according to the place of the pixel at its center
    //the window whose center lies at .... -> its window size is......
    //a corner -> 4
    //the borders (exept the corners) -> 6
    //otherwise -> 9
    short n_summed_pixels = 0;
    if (i == 0 || i == 255)
    {
        if (j == 0 || j == 255)
        {
            n_summed_pixels = 4;
        }
        else
        {
            n_summed_pixels = 6;
        }
    }
    else
    {
        if (j == 0 || j == 255)
        {
            n_summed_pixels = 6;
        }
        else
        {
            n_summed_pixels = 9;
        }
    }

    return n_summed_pixels;
}*/


/*void blur_v2 ()
{
    //make a copy of (image) into (aux)
    uc aux[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            aux[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0, sum, n_pixels; j < SIZE; j++)
        {
            n_pixels = 0;
            sum = aux[i][j];
            n_pixels++;
            if (i-1 >= 0)
            {
                sum += aux[i-1][j];
                n_pixels++;
                if (j-1 >= 0)
                {
                    sum += aux[i-1][j-1];
                    n_pixels++;
                }
                if (j+1 <= 255)
                {
                    sum += aux[i-1][j+1];
                    n_pixels++;
                }
            }
            if (i+1 <= 255)
            {
                sum += aux[i+1][j];
                n_pixels++;
                if (j-1 >= 0)
                {
                    sum += aux[i+1][j-1];
                    n_pixels++;
                }
                if (j+1 <= 255)
                {
                    sum += aux[i+1][j+1];
                    n_pixels++;
                }
            }
            if (j+1 <= 255)
            {
                sum += aux[i][j+1];
                n_pixels++;
            }
            if (j-1 >= 0)
            {
                sum += aux[i][j-1];
                n_pixels++;
            }

            image[i][j] = sum / n_pixels;
        }
    }
}*/