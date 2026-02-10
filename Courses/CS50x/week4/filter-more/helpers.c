#include "helpers.h"
#include <math.h>
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
    RGBTRIPLE **imageBuffer;
    imageBuffer = malloc(sizeof(RGBTRIPLE *) * height);
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

typedef struct
{
    int16_t rgbtBlue;
    int16_t rgbtGreen;
    int16_t rgbtRed;
} __attribute__((__packed__)) RGBTRIPLE16;

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE **imageBuffer = malloc(sizeof(RGBTRIPLE *) * height);
    for (int i = 0; i < height; i++)
        imageBuffer[i] = malloc(sizeof(RGBTRIPLE) * width);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE16 Gx;
            RGBTRIPLE16 Gy;
            int sign;
            int factor;
            Gx.rgbtBlue = 0;
            Gx.rgbtGreen = 0;
            Gx.rgbtRed = 0;
            Gy.rgbtBlue = 0;
            Gy.rgbtGreen = 0;
            Gy.rgbtRed = 0;

            // Calculate Gx
            for (int k = i - 1; k < i + 2; k++)
            {
                for (int l = j - 1; l < j + 2; l += 2)
                {
                    if (l == j - 1)
                        sign = -1;
                    else if (l == j + 1)
                        sign = 1;

                    if (k == i - 1 || k == i + 1)
                        factor = 1;
                    else if (k == i)
                        factor = 2;
                    if ((k >= 0 && k < height) && (l >= 0 && l < width))
                    {
                        Gx.rgbtBlue += image[k][l].rgbtBlue * sign * factor;
                        Gx.rgbtGreen += image[k][l].rgbtGreen * sign * factor;
                        Gx.rgbtRed += image[k][l].rgbtRed * sign * factor;
                    }
                }
            }

            // Calculate Gy
            for (int k = i - 1; k < i + 2; k += 2)
            {
                for (int l = j - 1; l < j + 2; l++)
                {
                    if (k == i - 1)
                        sign = -1;
                    else if (k == i + 1)
                        sign = 1;

                    if (l == j - 1 || l == j + 1)
                        factor = 1;
                    else if (l == j)
                        factor = 2;
                    if ((k >= 0 && k < height) && (l >= 0 && l < width))
                    {
                        Gy.rgbtBlue += image[k][l].rgbtBlue * sign * factor;
                        Gy.rgbtGreen += image[k][l].rgbtGreen * sign * factor;
                        Gy.rgbtRed += image[k][l].rgbtRed * sign * factor;
                    }
                }
            }

            int16_t magnitude = sqrt(pow(Gx.rgbtBlue, 2) + pow(Gy.rgbtBlue, 2)) + 0.5;
            imageBuffer[i][j].rgbtBlue = magnitude > 255 ? 255 : magnitude;
            magnitude = sqrt(pow(Gx.rgbtGreen, 2) + pow(Gy.rgbtGreen, 2)) + 0.5;
            imageBuffer[i][j].rgbtGreen = magnitude > 255 ? 255 : magnitude;
            magnitude = sqrt(pow(Gx.rgbtRed, 2) + pow(Gy.rgbtRed, 2)) + 0.5;
            imageBuffer[i][j].rgbtRed = magnitude > 255 ? 255 : magnitude;
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
