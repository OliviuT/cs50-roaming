#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //check for number of arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    //check if file is able to be opened
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fclose(file);
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    //create vars for file reading
    BYTE buffer[512 + 1];
    char name[8];
    int n = 0;
    FILE *fp;

    //initiate reading through the card.raw
    while (fread(buffer, sizeof(BYTE), 512, file))
    {
        //check header for a new JPG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //check if we're already writing on one JPG
            if (n)
            {
                fclose(fp);
            }
            //open a new file and write the first 512 bytes
            sprintf(name, "%03i.jpg", n);
            n++;
            fp  = fopen(name, "w");
            fwrite(buffer, sizeof(BYTE), 512, fp);
            continue;
        }
        //check if we're already writing on one JPG
        if (n)
        {
            fwrite(buffer, sizeof(BYTE), 512, fp);
        }
    }

    //free memory
    fclose(fp);
    fclose(file);
}