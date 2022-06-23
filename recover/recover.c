#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Size of blocks, in bytes, on the card.
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    typedef uint8_t BYTE;   // Sets a type 'BYTE'.

    BYTE buffer[BLOCK_SIZE];    // Creates a 'buffer' array of 'BYTES'.

    if (argc != 2)  // Checks for only one command-line argument.
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Opens a file for reading, from command line argument.
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)  // If unable to open file, prog will terminate.
    {
        return 1;
    }

    char *filename = malloc(sizeof(char) * 8);  // Creates a string for 7 characters + \0 for filenames.
    int counter = 0;    // A counter for number of jpgs found.

    sprintf(filename, "%03i.jpg", counter); // Prints a string to 'filename' that will be used to title image files.
    FILE *img = fopen(filename, "w");   // Opens a new file for writing to, using 'filename' as a title.

    // Loop that will cycle until a 512 byte block is no longer being read.
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, f) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)  // Start of new jpg.
        {
            if (counter == 0)   // First jpg.
            {
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
            }
            else // Not first.
            {
                fclose(img);    // Close last file.
                // New title and file opens to then write to.
                sprintf(filename, "%03i.jpg", counter);
                img = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
            }
            counter++;  // Counter for next jpg title.
        }
        else if (counter > 0)   // If not the start of a new jpg & first jpg has been found.
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);  // continues writing to file until start of next jpg is found.
        }
    }

    fclose(img);
    fclose(f);
    free(filename);
    return 0;
}