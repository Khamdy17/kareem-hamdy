/*
  File Name : CS112_A3_Part2A_ALL_20230261_20220248
  Author1 and ID : Omar farag abdelhalim abdallah    20230261
  Author2 and ID : Kareem hamdy metwally mosa    20220248
  filters(1,2,3,4,5,6) done by Author1
  filters(7,8,9,10,11,12) done by Author2
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;

unsigned char image [SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
unsigned char new_image [SIZE][SIZE];

void load_image();
void save_image();

void black_white();
void flip_image();
void mirror_image();
void darken_lighten();
void merge();
void blur();
void shrink();
void enlarge();
void shuffle();

/* -----------------------------------------------------------------------------------------*/

int main()
{
    int x;
    cout
            << "1- B&W \n 2- Invert\n 3- Merge \n 4- Flip \n 5- Rotate\n 6- Darken & lighten\n "
               "7- Detect image edge \n 8- Enlarge\n 9- Shrink\n 10- Mirror \n 11- Shuffle \n 12- Blur \n ";
    cin >> x;

    switch(x)
    {
        case 1:
            load_image();
            black_white();
            save_image();
            break;
        case 3:
            load_image();
            merge();
            save_image();
            break;
        case 4:
            load_image();
            flip_image();
            save_image();
            break;
        case 6:
            load_image();
            darken_lighten();
            save_image();
            break;
        case 8:
            load_image();
            enlarge();
            save_image();
            break;
        case 9:
            load_image();
            shrink();
            save_image();
            break;
        case 10:
            load_image();
            mirror_image();
            save_image();
            break;
        case 11:
            load_image();
            shuffle();
            save_image();
            break;
        case 12:
            load_image();
            blur();
            save_image();
            break;
        default:
            cout << "Please enter a choice from the above :)" << endl;
            break;
    }
    return 0;
}
/*-----------------------------------------------------------------------------------------------------------*/

void load_image()
{
    char imageFileName[100];
    cout << "Please enter the source image file name: " << endl;
    cin >> imageFileName;
    // taking image File name
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

void save_image()
{
    char imageFileName[100];
    cout << "Please enter a new name to save the image: " << endl;
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, new_image );
}

void black_white()
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] > 127)
                new_image[i][j] = 255;
            else
                new_image[i][j] = 0;
        }
    }
}

void flip_image()
{
    int y;
    cout << "1.horizontally - 2. vertically\n";
    cin >> y;
    if (y == 1) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                new_image[i][j] = image[i][SIZE - j];
            }
        }
    } else if (y == 2) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                new_image[i][j] = image[SIZE - i][j];
            }
        }
    }
}

void mirror_image()
{
    char c;
    cout << "Choose which part to be mirrored (u)p (d)own (l)eft (r)ight: ";
    cin >> c;
    if (c == 'u') {
        for (int i = 0; i < SIZE / 2; i++)
            for (int j = 0; j < SIZE; j++)
                new_image[i][j] = image[i][j];

        for (int i = 127; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                new_image[i][j] = image[SIZE - i][j];

    } else if (c == 'd') {
        for (int i = 127; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                new_image[i][j] = image[i][j];

        for (int i = 0; i < SIZE / 2; i++)
            for (int j = 0; j < SIZE; j++)
                new_image[i][j] = image[SIZE - i][j];


    } else if (c == 'l') {
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE / 2; j++)
                new_image[i][j] = image[i][j];

        for (int i = 0; i < SIZE; i++)
            for (int j = 127; j < SIZE; j++)
                new_image[i][j] = image[i][SIZE - j];
    }
    else if (c == 'r') {
        for (int i = 0; i < SIZE; i++)
            for (int j = 127; j < SIZE ; j++)
                new_image[i][j] = image[i][j];

        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < 127; j++)
                new_image[i][j] = image[i][SIZE - j];
    }
}

void darken_lighten()
{
    char choice;
    cout << "Do you want to darken or lighten? For darken write d & for lighten write l." << endl;
    cin >> choice;
    if (choice == 'd' || choice == 'D') {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                new_image[i][j] = (image[i][j]) / 2;
            }
        }
    }
    else if (choice == 'l' || choice == 'L') {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                new_image[i][j] = (image[i][j] + 255) / 2;
            }
        }
    }
    else
        cout << "Please enter d or l.";
}

void merge()
{
    char image2_name[100];

    cout << "Please enter the second image to merge: " << endl;
    cin >> image2_name;

    strcat (image2_name, ".bmp");
    readGSBMP(image2_name, image2);

    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            new_image[i][j] = (image[i][j] + image2[i][j]) / 2;

        }
    }
}

void blur()
{
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            new_image[i][j] = ( image[i+1][j] + image[i+2][j] + image[i+3][j] + image[i][j+1] + image[i][j+2]
                              + image[i][j+3] + image[i+1][j+1] + image[i+2][j+2] + image[i+3][j+3] ) / 9;
        }
    }
}

void shrink()
{
    char choice;
    cout << "Do you want to shrink half, third or quarter ?. write h or t or q." << endl;
    cin >> choice;
    if (choice == 'h' || choice == 'H')
    {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                new_image[i/2][j/2] = image[i][j];
            }
        }
    }
    else if (choice == 't' || choice == 'T')
    {
        for(int i = 0; i < SIZE; ++i){
            for(int j = 0; j < SIZE; ++j){
                new_image[i/3][j/3] = image[i][j];
            }
        }
    }
    else if (choice == 'q' || choice == 'Q')
    {
        for(int i = 0; i < SIZE; ++i){
            for(int j = 0; j < SIZE; ++j){
                new_image[i/4][j/4] = image[i][j];
            }
        }
    }
    else
        cout << "Please enter h, t or q." << endl;

}

void enlarge()
{
    int choice;
    cout << "Please enter the part of the image you want to enlarge. write 1, 2, 3 or 4" << endl;
    cin >> choice;
    if (choice == 1) {

        for (int i = 0, row = 0; i < SIZE; row++, i+=2) {
            for (int j = 0, col = 0; j < SIZE; col++, j +=2) {
                new_image[i][j] = image[row][col];
                new_image[i+1][j] = image[row][col];
                new_image[i][j+1] = image[row][col];
                new_image[i+1][j+1] = image[row][col];
            }
        }
    }
    else if (choice == 2){

        for (int i = 0, row = 0; i < SIZE; row++, i+=2) {
            for (int j = 0, col = 128; j < SIZE; col++, j +=2) {
                new_image[i][j] = image[row][col];
                new_image[i+1][j] = image[row][col];
                new_image[i][j+1] = image[row][col];
                new_image[i+1][j+1] = image[row][col];
            }
        }
    }
    else if (choice == 3){

        for (int i = 0, row = 128; i < SIZE; row++, i+=2) {
            for (int j = 0, col = 0; j < SIZE; col++, j +=2) {
                new_image[i][j] = image[row][col];
                new_image[i+1][j] = image[row][col];
                new_image[i][j+1] = image[row][col];
                new_image[i+1][j+1] = image[row][col];
            }
        }
    }
    else if (choice == 4){

        for (int i = 0, row = 128; i < SIZE; row++, i+=2) {
            for (int j = 0, col = 128; j < SIZE; col++, j +=2) {
                new_image[i][j] = image[row][col];
                new_image[i+1][j] = image[row][col];
                new_image[i][j+1] = image[row][col];
                new_image[i+1][j+1] = image[row][col];
            }
        }
    }
    else
        cout << "Please enter 1, 2, 3 or 4." << endl;
}

void shuffle() {
    int row, col;
    string order;
    cout << "Please enter the order without spaces: " << endl;
    cin.clear();
    cin.sync();

    getline(cin, order);
    for (int k = 0; k < 4; k++) {
        int r = 0, c = 0;
        r = k < 2 ? 0 : SIZE / 2;
        row = order[k] < '3' ? 0 : SIZE / 2;
        for (int i = row; i < row + SIZE / 2; i++, r++) {
            col = (order[k] - '0') % 2 == 1 ? 0 : SIZE / 2;
            c = k % 2 == 0 ? 0 : SIZE / 2;
            for (int j = col; j < col + SIZE / 2; j++, c++) {
                new_image[r][c] = image[i][j];
            }
        }
    }

}
