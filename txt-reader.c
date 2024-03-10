#include <stdint.h>
#include <stdio.h>
#include <string.h>

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
        printf("Could not open file.\n");
        return 1;
    }

    /* Read the file and print each byte as a character */
    uint8_t buffer;

    while (fread(&buffer, 1, 1, file) == 1)
        printf("%c", buffer);

    /* Close the file */
    fclose(file);

    return 0;
}
