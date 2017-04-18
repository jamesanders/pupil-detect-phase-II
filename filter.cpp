/*
* Author: Ben Durette
* Class: BIEN 4290
* Lab 4
* Date: 3/28/17
* This file defines the base filter object and its
* associated functions
* Adapted for final project 4/18/17
*/

#include <iostream>
#include <stdlib.h>
#include "filter.h"
#include "image.h"
using namespace std;

//Constructor for Filter object
Filter::Filter() {}

//Virtual function for updatePixel()
float Filter::updatePixel(Image & neighImage, int M, int N) {}

//This function iterates through every non-edge pixel of the image
//and calls the updatePixel function to filter each pixel
Image Filter::process(Image & inImage, int M, int N)
{
	int imageDimension = 256;

	if ( (M%2 == 0) || (N%2 == 0))
	{
		cout << "Error: Neighborhood pixel dimension is even\n";
		exit (EXIT_FAILURE);
	}

	if( (M > imageDimension) || (N > imageDimension) )
	{
		cout << "Error: Input filter dimensions exceed image dimensions\n";
		exit (EXIT_FAILURE);
	}

	//Create copy image and small temporary image for filter process
	Image tempIm(M,N);
	Image imageCopy = inImage;

	//Offsets are used to populate the temporary image object used for filtering
	int mOffset = (M+1)/2 - 1;
	int nOffset = (N+1)/2 - 1;

	//First two loops iterate through each pixel in the original image object
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{	
			//If the current pixel is not a border pixel, proceed with filtering
			if ( !((i==0) || (i==255) || (j==0) || (j==255)) )
			{
				//These two loops iterate through smaller image object and populate
				//with current pixel and neighbor pixel values
				for (int m = 0; m < M; m++)
				{
					for (int n = 0; n < N; n++)
					{
						tempIm.setVal(m,n,inImage.getVal((i+m-mOffset),(j+n-nOffset)));
					}
				}
				//Set the new value of the current pixel to the output image
				imageCopy.setVal(i,j,updatePixel(tempIm,M,N));

				//cout << "";
				cout << "";
			}
		}
	}
	//Return output image
	return imageCopy;
}

