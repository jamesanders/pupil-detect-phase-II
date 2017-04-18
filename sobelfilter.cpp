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

	float threshold = 100;
	float floatOne = 1.000;
	float floatZero = 0.000;
	float GxSum = 0;
        float GySum = 0;
        float mag;
	int GxKernal[3][3] = {
				{-1,0,1},
				{-2,0,2},
				{-1,0,1}
			     };
	int GyKernal[3][3] = {
				{1,2,1},
				{0,0,0},
				{-1,-2,-1}
			     };

	//Determine the sum of the neighbors
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			GxSum += GxKernal[i][j]*neighImage.getVal(i,j);
			GySum += GyKernal[i][j]*neighImage.getVal(i,j);
		}
	}
	mag = abs(sqrt(pow(GxSum,2) + pow(GySum,2)));
	cout << "mag = " << mag << "\n";


	if (mag > threshold)
	{
		cout << "1\n";
		return floatOne;
	}
	else
	{
		cout << "0\n";
		return floatZero;
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

