#include "helpers.h"
#include <math.h>

int bitcheck(int x);
void swap(BYTE *a, BYTE *b);
void Reset(float *a, float *b, float *c);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average;    // Declares an int for average of pixels.
    for (int i = 0; i < height; i++)    // Counts rows.
    {
        for (int j = 0; j < width; j++) // Counts columns.
        {
            average = round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);    // Calculates the average.
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)    // Rows.
    {
        for (int j = 0; j < width; j++) // Columns.
        {
            if ((width - j) > width / 2)    // Leaves the middle pixel if width is an odd number.
            {
                swap(&image[i][(width - 1) - j].rgbtRed, &image[i][j].rgbtRed);   // swap function - note & passing over 'address of'.
                swap(&image[i][(width - 1) - j].rgbtGreen, &image[i][j].rgbtGreen);
                swap(&image[i][(width - 1) - j].rgbtBlue, &image[i][j].rgbtBlue);
            }
            else
            {
                break;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];  // Creates a copy of the image so as to not blur based off edited image.
    float avRed, avGreen, avBlue, counter; // Declare 3x ints fo averages of surrounding pixel values.
    int x, y;  // Declares 3x ints for while loops, counter is for average calc.
    for (int i = 0; i < height; i++)    // Rows.
    {
        for (int j = 0; j < width; j++) // Columns
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;   // Copies pixel values to copy image.
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }
    for (int i = 0; i < height; i++)    // Rows.
    {
        for (int j = 0; j < width; j++) // Columns.
        {
            avRed = 0;  // At the beginning of each row, averages & counter are reset to 0.
            avBlue = 0;
            avGreen = 0;
            counter = 0;

            x = i - 1;  // This resets x & y so as to scan surrounding pixels.
            y = j - 1;

            while (x < i + 2)
            {
                if (x >= 0 && x < height)   // Checks within image, if not it moves on to the next pixel.
                {
                    while (y < j + 2)
                    {
                        if (y >= 0 && y < width)
                        {
                            avRed += (float) copy[x][y].rgbtRed;  // Adds up the values of surrounding pixels for average calc.
                            avGreen += (float) copy[x][y].rgbtGreen;
                            avBlue += (float) copy[x][y].rgbtBlue;
                            counter++;  // Counts surrounding pixels for average calc.
                        }
                        y++;
                    }
                    y = j - 1;  // Resets y for next row.
                }
                x++;
            }
            image[i][j].rgbtRed = round(avRed / counter);   // Calculates average, rounds and updates image.
            image[i][j].rgbtGreen = round(avGreen / counter);
            image[i][j].rgbtBlue = round(avBlue / counter);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];  // Declare RGBTRIPLE array for copy of image.

    float Gx[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};   // Array for Gx.

    float Gy[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};   // Array for Gy.

    int counter;    // Counter so correct element of array is accessed.

    float GxRed, GxBlue, GxGreen, GyRed, GyBlue, GyGreen;   // Gx & Gy variables per pixel RGB.

    for (int i = 0; i < height; i++)    // For loop copies image.
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)    // Rows.
    {
        for (int j = 0; j < width; j++) // Columns. - pixel is now selected.
        {
            Reset(&GxRed, &GxGreen, &GxBlue);   // Resets everything to 0 before moving onto next pixel.
            Reset(&GyRed, &GyGreen, &GyBlue);
            counter = 0;

            for (int x = -1; x < 2; x++)    // Rows - surrounding pixels.
            {
                for (int y = -1; y < 2; y++)    // Columns - surrounding pixels.
                {
                    if (j + y < 0 || j + y >= width || i + x < 0 || i + x >= height)  // Edges + corner cases.
                    {
                        counter++;
                        continue;
                    }

                    GxRed += (copy[i + x][j + y].rgbtRed * Gx[counter]);
                    GxGreen += (copy[i + x][j + y].rgbtGreen * Gx[counter]);
                    GxBlue += (copy[i + x][j + y].rgbtBlue * Gx[counter]);
                    GyRed += (copy[i + x][j + y].rgbtRed * Gy[counter]);
                    GyGreen += (copy[i + x][j + y].rgbtGreen * Gy[counter]);
                    GyBlue += (copy[i + x][j + y].rgbtBlue * Gy[counter]);
                    counter++;
                }
            }   // Squares Gx & Gy before adding them together, then gets the square root, rounds it, bitchecks and returns value to image RG or B.
            image[i][j].rgbtRed = bitcheck((int) round(sqrt((GxRed * GxRed) + (GyRed * GyRed))));
            image[i][j].rgbtGreen = bitcheck((int) round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen))));
            image[i][j].rgbtBlue = bitcheck((int) round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue))));
        }
    }
    return;
}

int bitcheck(int x)
{
    if (x > 255)
    {
        return 255;
    }
    else
    {
        return x;
    }
}

void swap(BYTE *a, BYTE *b)
{
    int temp;
    temp = *b;
    *b = *a;
    *a = temp;
}

void Reset(float *a, float *b, float *c)
{
    *a = 0;
    *b = 0;
    *c = 0;
}