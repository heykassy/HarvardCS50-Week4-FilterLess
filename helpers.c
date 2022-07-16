#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //Loop around the pixels, get the average of all three colors in each pixel and set each to the average number obtained
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //Loop around the pixels, use the formula to calculate the new value of each color
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            //Update values. Ternary condition to check if the number goes beyond 255. If so, then set it to 255.
            image[i][j].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //Loop around the pixels in each row. Set two variables, one to start on the far left and another to star at the far right and make them swap their values
    for (int i = 0; i < height; i++)
    {
        int swap = width - 1;
        int j = 0;
        while (swap > j)
        {
            RGBTRIPLE image_temp = image[i][j];
            image[i][j] = image [i][swap];
            image [i][swap] = image_temp;
            swap--;
            j++;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Create a temporary copy of image to use the original values without modification and iterate through image copying each pixel to "copy"
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float count = 0;
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            for (int x = i - 1; x <= i + 1; x++)
            {
                for (int y = j - 1; y <= j + 1; y++)
                {
                    if ((x >= 0 && x < height) && (y >= 0 && y < width))
                    {
                        sumRed += copy[x][y].rgbtRed;
                        sumGreen += copy[x][y].rgbtGreen;
                        sumBlue += copy[x][y].rgbtBlue;
                        count++;
                    }
                }
                image[i][j].rgbtRed = round(sumRed / count);
                image[i][j].rgbtGreen = round(sumGreen / count);
                image[i][j].rgbtBlue = round(sumBlue / count);
            }
        }
    }
    return;
}