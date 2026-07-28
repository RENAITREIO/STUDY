#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK 512
int is_jpg_header(uint8_t buffer[]);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Unable to open file.\n");
        return 2;
    }
    uint8_t buffer[BLOCK];
    FILE *output = NULL;
    char filename[8];
    int count = 0;
    while (fread(buffer, 1, BLOCK, input))
    {
        if (is_jpg_header(buffer))
        {
            // If a JPEG is already open, close it
            if (output != NULL)
            {
                fclose(output);
            }

            // Create a new file for the new JPEG
            sprintf(filename, "%03d.jpg", count++);
            output = fopen(filename, "w");
            if (output == NULL)
            {
                fclose(input);
                printf("Unable to create file.\n");
                return 3;
            }
        }

        // If we’ve found a JPEG, keep writing blocks to it
        if (output != NULL)
        {
            fwrite(buffer, 1, BLOCK, output);
        }
    }

    // Close any remaining open file
    if (output != NULL)
    {
        fclose(output);
    }
    fclose(input);
    return 0;
}

int is_jpg_header(uint8_t buffer[])
{
    return buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
           (buffer[3] & 0xf0) == 0xe0;
}
