#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float color;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //get the value to set for RGB
            color = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            // set new values
            image[i][j].rgbtRed = color;
            image[i][j].rgbtGreen = color;
            image[i][j].rgbtBlue = color;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int originalRed, originalGreen, originalBlue, sepiaRed, sepiaGreen, sepiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //store original RGB values
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;


            //make conversion with the sepia formula
            sepiaRed = round((0.393 * originalRed) + (0.769 * originalGreen) + (0.189 * originalBlue));
            //set red out of range
            if (sepiaRed < 0)
            {
                image[i][j].rgbtRed = 0;
            }
            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }

            // set sepia formula for green
            sepiaGreen = round((0.349 * originalRed) + (0.686 * originalGreen) + (0.168 * originalBlue));
            //set green out of range
            if (sepiaGreen < 0)
            {
                image[i][j].rgbtGreen = 0;
            }
            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }

            // set sepia formula for blue
            sepiaBlue = round((0.272 * originalRed) + (0.534 * originalGreen) + (0.131 * originalBlue));
            //set blue out of range
            if (sepiaBlue < 0)
            {
                image[i][j].rgbtBlue = 0;
            }
            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, k = width; j < width; j++)
        {
            k--;
            //check if the row has been comepltely reflected
            if (k < j || k == j)
            {
                break;
            }
            //set color for red
            int originalRed = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][k].rgbtRed;
            image[i][k].rgbtRed = originalRed;

            //set color for green
            int originalGreen = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][k].rgbtGreen;
            image[i][k].rgbtGreen = originalGreen;

            //set color for blue
            int originalBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][k].rgbtBlue;
            image[i][k].rgbtBlue = originalBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    //copy image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // do the blur effect
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //top left corner
            if (i == 0 && j == 0)
            {
                image[i][j].rgbtRed     = round((copy[i][j].rgbtRed     + copy[i][j + 1].rgbtRed    + copy[i + 1][j].rgbtRed    + copy[i + 1][j +
                                                 1].rgbtRed)   / 4.0);
                image[i][j].rgbtGreen   = round((copy[i][j].rgbtGreen   + copy[i][j + 1].rgbtGreen  + copy[i + 1][j].rgbtGreen  + copy[i + 1][j +
                                                 1].rgbtGreen) / 4.0);
                image[i][j].rgbtBlue    = round((copy[i][j].rgbtBlue    + copy[i][j + 1].rgbtBlue   + copy[i + 1][j].rgbtBlue   + copy[i + 1][j +
                                                 1].rgbtBlue)  / 4.0);
                continue;
            }
            //top right corner
            if (i == 0 && j == (width - 1))
            {
                image[i][j].rgbtRed     = round((copy[i][j].rgbtRed     + copy[i][j - 1].rgbtRed    + copy[i + 1][j].rgbtRed    + copy[i + 1][j -
                                                 1].rgbtRed)   / 4.0);
                image[i][j].rgbtGreen   = round((copy[i][j].rgbtGreen   + copy[i][j - 1].rgbtGreen  + copy[i + 1][j].rgbtGreen  + copy[i + 1][j -
                                                 1].rgbtGreen) / 4.0);
                image[i][j].rgbtBlue    = round((copy[i][j].rgbtBlue    + copy[i][j - 1].rgbtBlue   + copy[i + 1][j].rgbtBlue   + copy[i + 1][j -
                                                 1].rgbtBlue)  / 4.0);
                continue;
            }
            //bottom left corner
            if (i == (height - 1) && (j == 0))
            {
                image[i][j].rgbtRed     = round((copy[i][j].rgbtRed     + copy[i][j + 1].rgbtRed    + copy[i - 1][j].rgbtRed    + copy[i - 1][j +
                                                 1].rgbtRed)   / 4.0);
                image[i][j].rgbtGreen   = round((copy[i][j].rgbtGreen   + copy[i][j + 1].rgbtGreen  + copy[i - 1][j].rgbtGreen  + copy[i - 1][j +
                                                 1].rgbtGreen) / 4.0);
                image[i][j].rgbtBlue    = round((copy[i][j].rgbtBlue    + copy[i][j + 1].rgbtBlue   + copy[i - 1][j].rgbtBlue   + copy[i - 1][j +
                                                 1].rgbtBlue)  / 4.0);
                continue;
            }
            //bottom right corner
            if (i == (height - 1) && j == (width - 1))
            {
                image[i][j].rgbtRed     = round((copy[i][j].rgbtRed     + copy[i][j - 1].rgbtRed    + copy[i - 1][j].rgbtRed    + copy[i - 1][j -
                                                 1].rgbtRed)   / 4.0);
                image[i][j].rgbtGreen   = round((copy[i][j].rgbtGreen   + copy[i][j - 1].rgbtGreen  + copy[i - 1][j].rgbtGreen  + copy[i - 1][j -
                                                 1].rgbtGreen) / 4.0);
                image[i][j].rgbtBlue    = round((copy[i][j].rgbtBlue    + copy[i][j - 1].rgbtBlue   + copy[i - 1][j].rgbtBlue   + copy[i - 1][j -
                                                 1].rgbtBlue)  / 4.0);
                continue;
            }
            //top edge
            if (i == 0 && ((j > 0) && (j < width)))
            {
                image[i][j].rgbtRed     =   round((copy[i][j].rgbtRed   + copy[i][j + 1].rgbtRed    + copy[i][j - 1].rgbtRed    + copy[i + 1][j -
                                                   1].rgbtRed    + copy[i + 1][j].rgbtRed      + copy[i + 1][j + 1].rgbtRed)   / 6.0);
                image[i][j].rgbtGreen   =   round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen  + copy[i][j - 1].rgbtGreen  + copy[i + 1][j -
                                                   1].rgbtGreen  + copy[i + 1][j].rgbtGreen    + copy[i + 1][j + 1].rgbtGreen) / 6.0);
                image[i][j].rgbtBlue    =   round((copy[i][j].rgbtBlue  + copy[i][j + 1].rgbtBlue   + copy[i][j - 1].rgbtBlue   + copy[i + 1][j -
                                                   1].rgbtBlue   + copy[i + 1][j].rgbtBlue     + copy[i + 1][j + 1].rgbtBlue)  / 6.0);
                continue;
            }
            //bottom edge
            if (i == (height - 1) && ((j > 0) && (j < width)))
            {
                image[i][j].rgbtRed     =   round((copy[i][j].rgbtRed   + copy[i][j + 1].rgbtRed    + copy[i][j - 1].rgbtRed    + copy[i - 1][j -
                                                   1].rgbtRed    + copy[i - 1][j].rgbtRed      + copy[i - 1][j + 1].rgbtRed)   / 6.0);
                image[i][j].rgbtGreen   =   round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen  + copy[i][j - 1].rgbtGreen  + copy[i - 1][j -
                                                   1].rgbtGreen  + copy[i - 1][j].rgbtGreen    + copy[i - 1][j + 1].rgbtGreen) / 6.0);
                image[i][j].rgbtBlue    =   round((copy[i][j].rgbtBlue  + copy[i][j + 1].rgbtBlue   + copy[i][j - 1].rgbtBlue   + copy[i - 1][j -
                                                   1].rgbtBlue   + copy[i - 1][j].rgbtBlue     + copy[i - 1][j + 1].rgbtBlue)  / 6.0);
                continue;
            }
            //left edge
            if (((i > 0) && (i < height)) && j == 0)
            {
                image[i][j].rgbtRed     =   round((copy[i][j].rgbtRed   + copy[i - 1][j].rgbtRed    + copy[i + 1][j].rgbtRed    + copy[i - 1][j +
                                                   1].rgbtRed    + copy[i][j + 1].rgbtRed      + copy[i + 1][j + 1].rgbtRed)   / 6.0);
                image[i][j].rgbtGreen   =   round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen  + copy[i + 1][j].rgbtGreen  + copy[i - 1][j +
                                                   1].rgbtGreen  + copy[i][j + 1].rgbtGreen    + copy[i + 1][j + 1].rgbtGreen) / 6.0);
                image[i][j].rgbtBlue    =   round((copy[i][j].rgbtBlue  + copy[i - 1][j].rgbtBlue   + copy[i + 1][j].rgbtBlue   + copy[i - 1][j +
                                                   1].rgbtBlue   + copy[i][j + 1].rgbtBlue     + copy[i + 1][j + 1].rgbtBlue)  / 6.0);
                continue;
            }
            //right edge
            if (((i > 0) && (i < height)) && j == (width - 1))
            {
                image[i][j].rgbtRed     =   round((copy[i][j].rgbtRed   + copy[i - 1][j].rgbtRed    + copy[i + 1][j].rgbtRed    + copy[i - 1][j -
                                                   1].rgbtRed    + copy[i][j - 1].rgbtRed      + copy[i + 1][j - 1].rgbtRed)   / 6.0);
                image[i][j].rgbtGreen   =   round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen  + copy[i + 1][j].rgbtGreen  + copy[i - 1][j -
                                                   1].rgbtGreen  + copy[i][j - 1].rgbtGreen    + copy[i + 1][j - 1].rgbtGreen) / 6.0);
                image[i][j].rgbtBlue    =   round((copy[i][j].rgbtBlue  + copy[i - 1][j].rgbtBlue   + copy[i + 1][j].rgbtBlue   + copy[i - 1][j -
                                                   1].rgbtBlue   + copy[i][j - 1].rgbtBlue     + copy[i + 1][j - 1].rgbtBlue)  / 6.0);
                continue;
            }
            //middle pixel
            if (((i > 0) && (i < height)) && ((j > 0) && (j < width)))
            {
                image[i][j].rgbtRed     =   round((copy[i][j].rgbtRed   + copy[i - 1][j].rgbtRed    + copy[i + 1][j].rgbtRed    + copy[i - 1][j -
                                                   1].rgbtRed    + copy[i][j - 1].rgbtRed      + copy[i + 1][j - 1].rgbtRed      +   copy[i - 1][j + 1].rgbtRed      +   copy[i][j +
                                                           1].rgbtRed      +   copy[i + 1][j + 1].rgbtRed)     / 9.0);
                image[i][j].rgbtGreen   =   round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen  + copy[i + 1][j].rgbtGreen  + copy[i - 1][j -
                                                   1].rgbtGreen  + copy[i][j - 1].rgbtGreen    + copy[i + 1][j - 1].rgbtGreen    +   copy[i - 1][j + 1].rgbtGreen    +   copy[i][j +
                                                           1].rgbtGreen    +   copy[i + 1][j + 1].rgbtGreen)   / 9.0);
                image[i][j].rgbtBlue    =   round((copy[i][j].rgbtBlue  + copy[i - 1][j].rgbtBlue   + copy[i + 1][j].rgbtBlue   + copy[i - 1][j -
                                                   1].rgbtBlue   + copy[i][j - 1].rgbtBlue     + copy[i + 1][j - 1].rgbtBlue     +   copy[i - 1][j + 1].rgbtBlue     +   copy[i][j +
                                                           1].rgbtBlue     +   copy[i + 1][j + 1].rgbtBlue)    / 9.0);
                continue;
            }
        }
    }
    return;
}
