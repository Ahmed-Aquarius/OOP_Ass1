// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name:				phedit.cpp
// Last Modification Date:	    9/10/2023
// Author1 and ID and Group:	Abdelrahman Ahmed Lotfy     20220474    s22    Obidah05@gmail.com 
// Author2 and ID and Group:	Ahmed Hossam ElAlfy         20220016    s22    ahalfy2005@gmail.com
// Author3 and ID and Group:	Mohab Mohammad Abdelwahed   20220472    s11    mohab.fcai@gmail.com
// Teaching Assistant:          .......
// Purpose:                     Application for image processing in bitmap format using c++.



#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <set>
#include "bmplib.cpp"


using namespace std;

typedef unsigned char uc;

uc image[SIZE][SIZE];
const double PI = 3.14159265;


void loadImage(uc picture[SIZE][SIZE]);
void saveImage();

void black_and_white();
void invert();
void merge_image();
void flip();
void darken_or_lighten();
void rotate_image();
void detect_edges();
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
                detect_edges();
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




void loadImage (uc picture[SIZE][SIZE]) {
    // Get gray scale image file name
    char imageFileName[100];
    cout << "Please enter file name of the image to process: ";
    cin >> imageFileName;
    cout << endl;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, picture);
}


void saveImage () {
    // Get gray scale image target file name
    char imageFileName[100];
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);

    cout << "Image saved succesfully";
}




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
    //enter the second image
    uc image2[SIZE][SIZE];
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


void flip(){
    char flipLetter;
    //enter choice of flip: horizontally or vertically
    cout<<"Flip (h)orizontally or (v)ertically? ";
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


void detect_edges(){
    int total=0;
    //sum all pixels
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            total+=image[i][j];
        }
    }

    //divide sum by number to get average gray color level
    int avg = total/(SIZE*SIZE);

    //loop on pixels and compare pixels around selected pixel with the average to decide whether to
    //change the corresponding pixel in a new image to white or black
    uc outImage[SIZE][SIZE];
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(image[i][j]<avg){
                if(image[i+1][j]>avg || image[i-1][j]>avg || image[i][j+1]>avg || image[i][j-1]>avg){
                    outImage[i][j]=0;
                }
                else{
                    outImage[i][j]=255;
                }
            }
            else{
                outImage[i][j]=255;
            }
        }
    }

    //clear original image
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            image[i][j]=255;
        }
    }

    //put new image to original t save it
   for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            image[i][j]=outImage[i][j];
        }
    }
}


void enlarge(){
    uc Large_image[SIZE][SIZE] = {0};
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


void mirror_by_half(){
    //mirrors 1/2 image: left, right, upper or lower
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


void shuffle()
{
    uc Shuffle_image[SIZE][SIZE] = {0} ;
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


void crop(){
    //crops image to take a part of it and leave the rest
    int x,y,l,w;
    //input start position and length and width from user
    cout<<"Enter starting position of pixel in x,y: ";
    cin>>x>>y;
    cout<<"Enter length and width: ";
    cin>>l>>w;

    //clear new 2D array image
    uc cropImage[SIZE][SIZE];
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