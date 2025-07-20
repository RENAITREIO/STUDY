#include "helpers.h"
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE temp =
                (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0 + 0.5;
            image[i][j].rgbtBlue = temp;
            image[i][j].rgbtGreen = temp;
            image[i][j].rgbtRed = temp;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            uint16_t sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                                .189 * image[i][j].rgbtBlue + 0.5;
            uint16_t sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                                  .168 * image[i][j].rgbtBlue + 0.5;
            uint16_t sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                                 .131 * image[i][j].rgbtBlue + 0.5;
            image[i][j].rgbtBlue = (sepiaBlue < 255 ? sepiaBlue : 255);
            image[i][j].rgbtGreen = (sepiaGreen < 255 ? sepiaGreen : 255);
            image[i][j].rgbtRed = (sepiaRed < 255 ? sepiaRed : 255);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            BYTE bufferBlue = image[i][j].rgbtBlue;
            BYTE bufferGreen = image[i][j].rgbtGreen;
            BYTE bufferRed = image[i][j].rgbtRed;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][width - 1 - j].rgbtBlue = bufferBlue;
            image[i][width - 1 - j].rgbtGreen = bufferGreen;
            image[i][width - 1 - j].rgbtRed = bufferRed;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE **imageBuffer = malloc(sizeof(RGBTRIPLE *) * height);
    for (int i = 0; i < height; i++)
        imageBuffer[i] = malloc(sizeof(RGBTRIPLE) * width);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            uint16_t bufferBlue = 0;
            uint16_t bufferGreen = 0;
            uint16_t bufferRed = 0;
            int count = 0;
            for (int k = i - 1; k < i + 2; k++)
            {
                for (int l = j - 1; l < j + 2; l++)
                {
                    if ((k >= 0 && k < height) && (l >= 0 && l < width))
                    {
                        bufferBlue += image[k][l].rgbtBlue;
                        bufferGreen += image[k][l].rgbtGreen;
                        bufferRed += image[k][l].rgbtRed;
                        count++;
                    }
                }
            }
            imageBuffer[i][j].rgbtBlue = bufferBlue / (float) count + 0.5;
            imageBuffer[i][j].rgbtGreen = bufferGreen / (float) count + 0.5;
            imageBuffer[i][j].rgbtRed = bufferRed / (float) count + 0.5;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = imageBuffer[i][j].rgbtBlue;
            image[i][j].rgbtGreen = imageBuffer[i][j].rgbtGreen;
            image[i][j].rgbtRed = imageBuffer[i][j].rgbtRed;
        }
    }
    for (int i = 0; i < height; i++)
        free(imageBuffer[i]);
    free(imageBuffer);
    return;
}
