#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* 8 KB buffer */
#define BUFFER_SIZE 8192

int main(int argc, char *argv[])
{
    /* Check command line arguments */
    if (argc != 2)
    {
        printf("Usage:\n./txt_reader file.txt\n");
        return 1;
    }

    /* Check the file extension */
    char *extension = strrchr(argv[1], '.');
    if (extension == NULL || strcmp(extension, ".txt") != 0)
    {
        printf("This is not a '.txt' document.\n");
        return 1;
    }

    /* Open the file in read mode */
    FILE *file = fopen(argv[1], "r");

    /* Check if the file can be opened */
    if (file == NULL)
    {
        perror("Could not open file.");
        return 1;
    }

    /* Buffer to hold chunks of data read from the file */
    uint8_t buffer[BUFFER_SIZE];
    /* Number of bytes read in the current fread operation */
    size_t bytesRead = 0;

    /* Read the file in chunks using the buffer and write each chunk to stdout */
    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, file)) > 0)
    {
        /* Write the current chunk to stdout */
        if (fwrite(buffer, 1, bytesRead, stdout) != bytesRead)
        {
            perror("Error writing to stdout");
            fclose(file);
            return 1;
        }
    }

    /* Check for errors during the read operation */
    if (ferror(file))
    {
        perror("Error reading file");
        fclose(file);
        return 1;
    }
    
    fclose(file);
    return 0;
}
