#include "helpers.h"
#include <stdlib.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // for each pixel in bitmap, find average of rgb values and assign each
    // r,g, and b value that average val

    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            BYTE avg = ( image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3;
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }


    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){

            // BYTE sred = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            // BYTE sgreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            // BYTE sblue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;

            // if(sred>255) sred=255;
            // if(sgreen>255) sgreen=255;
            // if(sblue>255) sblue=255;

            int sred = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            int sgreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            int sblue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;

            if(sred>255) sred=255;
            if(sgreen>255) sgreen=255;
            if(sblue>255) sblue=255;




            image[i][j].rgbtRed = sred;
            image[i][j].rgbtGreen = sgreen;
            image[i][j].rgbtBlue = sblue;
        }
    }


    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i=0; i<height; i++){
        int start =0;
        int end = width -1;
        // reverses current row in bitmap
        while(start < end){
            RGBTRIPLE tmp = image[i][start];
            image[i][start] = image[i][end];
            image[i][end] = tmp;

            start++;
            end--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){

            int size =  8 * sizeof(RGBTRIPLE);

            // make array of pixels for the 8 surrounding pixels
            RGBTRIPLE *pixels = malloc( size   );

            // k should prob be k+= for the third for loop argument
            for(int k=0; k<size; k+=3){

                printf("i: %i, j: %i, k: %i\n",i,j,k);


                // i should be in range [0,height-1]
                // j should be in range [0,width-1]
                if( i-1>=0 && i-1<=height-1 && j-1>=0 && j-1<=width-1     ){
                    // equiv to pixels[k]
                    *(pixels+k) = image[i-1][j-1];
                    continue;
                }
                if( i-1>=0 && i-1<=height-1 && j>=0 && j<=width-1     ){
                    // equiv to pixels[k]
                    *(pixels+k) = image[i][j];
                    continue;
                }
                if( i-1>=0 && i-1<=height-1 && j+1>=0 && j+1<=width-1     ){
                    // equiv to pixels[k]
                    *(pixels+k) = image[i-1][j+1];
                    continue;
                }
                if( i>=0 && i<=height-1 && j-1>=0 && j-1<=width-1     ){
                    // equiv to pixels[k]
                    *(pixels+k) = image[i][j-1];
                    continue;
                }
                if( i>=0 && i<=height-1 && j+1>=0 && j+1<=width-1     ){
                    // equiv to pixels[k]
                    *(pixels+k) = image[i][j+1];
                    continue;
                }
                if( i+1>=0 && i+1<=height-1 && j-1>=0 && j-1<=width-1     ){
                    // equiv to pixels[k]
                    *(pixels+k) = image[i+1][j-1];
                    continue;
                }
                if( i+1>=0 && i+1<=height-1 && j>=0 && j<=width-1     ){
                    // equiv to pixels[k]
                    *(pixels+k) = image[i+1][j];
                    continue;
                }
                if( i+1>=0 && i+1<=height-1 && j+1>=0 && j+1<=width-1     ){
                    // equiv to pixels[k]
                    *(pixels+k) = image[i+1][j+1];
                    continue;
                }
            }
 printf("pojo\n");

            int totRed=0; int totGreen=0; int totBlue=0;
            // amount of pixels that are in bounds, from which we collect rgb values
            int amtPixels=0;
            for(int k=0; k<size; k+=3){
                if( (pixels+k)!=NULL ){
                    totRed += pixels[k].rgbtRed;
                    totGreen += pixels[k].rgbtGreen;
                    totBlue += pixels[k].rgbtBlue;
                    ++amtPixels;
                }
            }



            printf("poo\n");


            image[i][j].rgbtRed = totRed / amtPixels;
            image[i][j].rgbtGreen = totGreen / amtPixels;
            image[i][j].rgbtBlue = totBlue / amtPixels;

            printf("poko\n");

        }

    }




    return;
}

