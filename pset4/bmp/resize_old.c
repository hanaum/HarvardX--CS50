#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char* argv[])
{
    if (argc != 4) {
        printf("Usage: ./resize n fileToResize resizedFile");
        return 1;
    }
    
    // n = pos int <= 100
    // GOTTA CHANGE THE CHAR TO AN INT
    int n = atoi(argv[1]);
    char* fileToResize = argv[2];
    char* resizedFile = argv[3];
    
    // open input file 
    FILE* inptr = fopen(fileToResize, "r");
    if (inptr == NULL) {
        printf("Could not open %s.\n", fileToResize);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(resizedFile, "w");
    if (outptr == NULL) {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", resizedFile);
        return 3;
    }
    
    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0) {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }  
    
    int inPadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int outPadding = (4 - (bi.biWidth * n * sizeof(RGBTRIPLE)) % 4) % 4;
 
    BITMAPINFOHEADER newBi;
    
    newBi.biSize = bi.biSize; 
    newBi.biWidth = bi.biWidth * n;
    newBi.biHeight = bi.biHeight * n;
    newBi.biPlanes = bi.biPlanes;
    newBi.biBitCount = bi.biBitCount;
    newBi.biCompression = bi.biCompression;
    newBi.biSizeImage = (sizeof(RGBTRIPLE) * newBi.biWidth + outPadding) * newBi.biHeight;
    newBi.biXPelsPerMeter = bi.biXPelsPerMeter;
    newBi.biYPelsPerMeter = bi.biYPelsPerMeter;
    newBi.biClrUsed = bi.biClrUsed;
    newBi.biClrImportant = bi.biClrImportant;
    

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&newBi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++) {
        for (int num = 0; num < n; num++) {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++) {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                for (int r = 0; r < n; r++)
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }

            // skip over padding, if any (SKIP INFILE?)
            fseek(inptr, inPadding, SEEK_CUR);

            // then add it back (to demonstrate how) (ADD OUTFILE?)
            for (int k = 0; k < outPadding; k++)
                fputc(0x00, outptr);
            if (num != n - 1)
                fseek(inptr, -(sizeof(RGBTRIPLE) * bi.biWidth + inPadding), SEEK_CUR);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
