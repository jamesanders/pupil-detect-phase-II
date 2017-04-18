/*
* Author: Ben Durette
* Class: BIEN 4290
* Lab 4
* Date: 3/28/17
* This file defines the non-linear noise reduction filter object and its
* associated functions
*/

#include <iostream>
#include <cmath>
#include "filter.h"
#include "sobelfilter.h"
#include "image.h"
using namespace std;

SobelFilter::SobelFilter() {}

//Virtual function redifined for this specific filter
float SobelFilter::updatePixel(Image & neighImage, int M, int N)
{
	int middleM = (M+1)/2 - 1;
	int middleN = (N+1)/2 - 1;
	float totalNeighbors = M*N - 1; 
	float sum;
	float mean;
	float stdDev;
	float sqSum = 0;
	float currentPixel;
	float updatedPixel;

	int GxKernal[3][3] = {
				{-1,0,1},
				{-2,0,2},
				{-1,0,1}
			     };
	float GxSum;
	float GySum;


	//Record value of current pixel being processed
	currentPixel = neighImage.getVal(middleM,middleN);
	//Set the current pixel to NULL to allow for easier calculation
	neighImage.setVal(middleM,middleN,NULL);

	//Determine the sum of the neighbors
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			sum = sum + neighImage.getVal(i,j);
		}
	}

	//Calculate the mean of neighbors
	mean = sum/totalNeighbors;

	//Sum the square of the difference from each neighbor to the mean
	for (int k = 0; k < M; k++)
	{
		for (int l = 0; l < N; l++)
		{
			if(!((k == middleM) && (l == middleN)))
			{
				sqSum = sqSum + ((neighImage.getVal(k,l)-mean)*(neighImage.getVal(k,l)-mean));
			}
		}
	}

	//Use the sum of square to calculate the standard deviation
	stdDev = sqrt(sqSum/(totalNeighbors));

	//If the current pixel value is outside of 3 standard deviations from the mean
	//of the neighbor pixels values, then it will stay the same
	if ((currentPixel < (mean - 3*stdDev)) || (currentPixel > (mean + 3*stdDev)))
	{updatedPixel = currentPixel;}

	//If not, set the output pixel to the mean of the neighbors
	else
	{updatedPixel = mean;}

	//Return the output pixel value
	return updatedPixel;
}

