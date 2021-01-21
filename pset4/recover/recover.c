#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// delete print statements
// This is the messiet code EVER, but I spent hours trying to translate the logic into c

bool is_jpeg(unsigned char buff_a, unsigned char buff_b, unsigned char buff_c, unsigned char buff_d);

int get_count(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        return 0;
    }

    fseek(fp, 0L, SEEK_END);
    int size = ftell(fp);

    fclose(fp);

    return size / 512;
}

int main(int argc, char *argv[])
{
    // Program should accept 1 argument of the image name
    if (argc != 2)
    {
        return 1;
    }

    // // Open the memory card, check to see if this file is legit
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        return 1;
    }

    int chunk_count = get_count(argv[1]); // Seek the file seperately becuase it screws up the program
    int image_count = -1;
    int chunk_increment = 0;
    unsigned char BUFFER[512];

    // Find the STARTING Image
    while (chunk_increment < chunk_count)
    {
        // Read the first 3 bytes out of 512
        // unsigned char buffer[512];
        fread(BUFFER, sizeof(BUFFER), 1, file); // if this is one - returns # of items of size 'size' that were read

        // int index = (512*chunk_increment);
        int index = 0;

        //Check first three bytes
        if (is_jpeg(BUFFER[index], BUFFER[index + 1], BUFFER[index + 2], BUFFER[index + 3]))
        {
            //printf("Maybe a JPEG at %i.  ---- image_count = %i\n", 512 * chunk_increment, image_count);
            break;
        }

        chunk_increment += 1;
    }

    // Open a JPEG file and start writing
    //FILE *temp_file = NULL;
    FILE *temp_files[chunk_count]; // up to limit # of images
    int starting_index = (512 * chunk_increment) - 1; // This is the 512 byte block that it starts at

    //printf("Starting index is %i\n", starting_index);
    bool end_program = false;
    for (int i = starting_index; i <= (512 * chunk_count); i += 512)
    {
        // // Is this the start of a file?
        // fseek(file, -512L, SEEK_CUR); // step back 512 bytes to re-read?
        // unsigned char buffer[512];
        // fread(buffer, sizeof(buffer), 1, file);

        if (is_jpeg(BUFFER[0], BUFFER[1], BUFFER[2], BUFFER[3]))
        {
            // Yes, this is the start. Begin a new JPEG file
            //printf("Creating new file in temp_files\n");
            image_count += 1;

            // Close temp if it exists
            if (image_count > 0)
            {
                if (temp_files[image_count - 1] != NULL)
                {
                    fclose(temp_files[image_count - 1]);
                }
            }


            char *new_jpg = malloc(7 * sizeof(char));
            sprintf(new_jpg, "%03i.jpg", image_count);

            //printf("%lu\n", sizeof(temp_files));
            temp_files[image_count] = fopen(new_jpg, "w");
            // Now the new JPG file is ready to go
        }
        // else
        // {
        //     // // It is not the start:
        //     // if (image_count == 50 && BUFFER[511] >= 0xe0 && BUFFER[511] <= 0xef)
        //     // {
        //     //     end_program = true;
        //     // }

        //     // // Last Byte: 0xe0, 0xe1 -> 0xef
        // }

        // Check fread for erros
        if (temp_files[image_count] == NULL)
        {

        }

        // Save the chunk that will be added to temp_file
        unsigned char this_chunk[512];
        for (int a = 0; a < 512; a++)
        {
            this_chunk[a] = BUFFER[a];
        }

        // Last Byte: 0xe0, 0xe1 -> 0xef

        //printf("Writing this chunk to temp_files[%i], %lu\n", image_count, sizeof(temp_files[image_count]));
        int n = fwrite(this_chunk, 1, 512, temp_files[image_count]);

        if (!fread(BUFFER, n, 1, file))
        {
            fclose(temp_files[image_count]);
            break;
        }

        if (end_program)
        {
            fclose(temp_files[image_count]);
            break;
        }
    }

    // Write this block to a JPEG
    // Start at the next block:
    // If this is a JPEG, CLOSE
    // else, write and continue incrementing

    // fwrite(data, size, number, outptr);
    //fclose(temp_files[50]);

    // Close the file
    fclose(file);

}

bool is_jpeg(unsigned char buff_a, unsigned char buff_b, unsigned char buff_c, unsigned char buff_d)
{
    if (buff_a == 0xff && buff_b == 0xd8 && buff_c == 0xff && ((buff_d & 0xf0) == 0xe0))
    {
        return true;
    }

    return false;
}