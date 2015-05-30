/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    FILE* rawFile = fopen("card.raw", "r");
    FILE* newFile;
    char start1[4] = {0xff, 0xd8, 0xff, 0xe0};
    char start2[4] = {0xff, 0xd8, 0xff, 0xe1};
    char* buffer = malloc(512);
    char* filename = malloc(sizeof(char) * 8);
    
    int numJpg = 0;
    while (fread(buffer, 512, 1, rawFile) != 0) {
        if ((buffer[0] == start1[0] && buffer[1] == start1[1] && buffer[2] == start1[2] && buffer[3] == start1[3])
            || (buffer[0] == start2[0] && buffer[1] == start2[1] && buffer[2] == start2[2] && buffer[3] == start2[3])) {  
            sprintf(filename, "%03d.jpg", numJpg);
            newFile = fopen(filename, "w");
            fwrite(buffer, 512, 1, newFile);
            numJpg++;
            break;
        }
    }
    
    while (fread(buffer, 512, 1, rawFile) != 0) {
         if ((buffer[0] == start1[0] && buffer[1] == start1[1] && buffer[2] == start1[2] && buffer[3] == start1[3])
             || (buffer[0] == start2[0] && buffer[1] == start2[1] && buffer[2] == start2[2] && buffer[3] == start2[3])) {
             fclose(newFile);
             sprintf(filename, "%03d.jpg", numJpg);
             newFile = fopen(filename, "w");
             fwrite(buffer, 512, 1, newFile);
             numJpg++;    
         }
         else
             fwrite(buffer, 512, 1, newFile);        
    }
        
    free(buffer);
    free(filename);
    fclose(rawFile);
    fclose(newFile);
}
