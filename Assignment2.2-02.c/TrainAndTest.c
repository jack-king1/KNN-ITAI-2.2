//
//  TrainAndTest.c
//  MLCoursework
//
//  This is a fairly inefficient implentation that does not use any dynamic memory allocation
// because that wouldnot be safe on the DEWIS marking system
//
//  Created by Jim Smith on 06/02/2017.
//  Copyright © 2017 Jim SmithJim Smith. All rights reserved.
//

#include "TrainAndTest.h"
#include <math.h>

//declare this array as static but make it available to any function in this file
//in case we want to store the training examples  and use them later
static double myModel[NUM_TRAINING_SAMPLES][ NUM_FEATURES];
static double test_samples[NUM_TEST_SAMPLES][NUM_FEATURES];

//even if each item in the training set is from a diffferent class we know how many there are
static char myModelLabels[NUM_TRAINING_SAMPLES];
static char mySortedLabels[NUM_TRAINING_SAMPLES];

static int labelUsed[256] = { 0 };

static int trainingSetSize = 0;

static double distances_index[NUM_TRAINING_SAMPLES];

static double sortedIndex_Labels[NUM_TRAINING_SAMPLES];

static double max_Heap[10];

static int classVotes[3];

static k = 10;


double distanceCalculate(double w1, double w2, double x1, double x2, double y1, double y2, double z1, double z2)
{
	double w = w1 - w2;
	double x = x1 - x2; //calculating number to square in next step
	double y = y1 - y2;
	double z = z1 - z2;
	double calc;
	double dist;

	calc = pow(w, 2) + pow(x, 2) + pow(y, 2) + pow(z, 2);       //calculating Euclidean distance
	dist = sqrt(calc);
	return dist;
}

int  train( double **trainingSamples, char *trainingLabels, int numSamples, int numFeatures)
{
	/*
	Training Samples is a multi dimensional array of the data/features 4x150 array. Double** is a pointer to a pointer double

	Training Labels is an array of chars passed in from main.c from the current data set.

	numSamples is the amount of samples in the current data set.

	num features is the amount of features in the current data set e.g. 4, 5, 6 in the training set we are given 4.

	Step 1: Identify current labels in data set and assign them to the static int labelUsed variable.

	faq for: 2.2: https://blackboard.uwe.ac.uk/webapps/blackboard/content/listContent.jsp?course_id=_286896_1&content_id=_5615690_1

	k = amount of points. 

	The 10th point.

	Each features is a value, so for each training point and sample point there will be 4 different plot points which will decide what the label will be.

	//https://cs.stackexchange.com/questions/64188/k-nearest-neighbors-euclidean-distance-how-to-process-multiple-attributes

	Calculate K Closest in array: https://www.geeksforgeeks.org/find-k-closest-elements-given-value/
	*/

    int returnval = 1;
    int sample, feature;
	int currentLabel; //used to get the possible labels for data set.
	int charAsInt;
	int distcount;
	int class_sort;
	//double CalculateDistance;

    //clean the model because C leaves whatever is in the memory
    for (sample=0; sample < NUM_TRAINING_SAMPLES; sample++) 
	{
        for (feature=0; feature < NUM_FEATURES; feature++) 
		{
            myModel[sample][feature] = 0.0;
        }
    }

	//sets classVotes to zero
	for (class_sort = 0; class_sort < 3; class_sort++)
	{
		classVotes[class_sort] = 0;
	}

	//sets distances to 0
	for (sample = 0; sample < NUM_TRAINING_SAMPLES; sample++)
	{
		distances_index[NUM_TRAINING_SAMPLES] = 0;
	}

    //sanity checking
    if ( numFeatures > NUM_FEATURES || numSamples > NUM_TRAINING_SAMPLES) {
        fprintf(stdout,"error: called train with data set larger than spaced allocated to store it");
        returnval=0;
    }

    //this is a silly trivial train()_ function
    fprintf(stdout,"no ML algorithm implemented yet\n");
    
    //make a simple copy of the data we are being passed but don't do anything with it
    //I'm just giving you this for the sake of people less familiar with pointers etc.
     if(returnval==1) 
	 {
        //store the labels and the feature values
        trainingSetSize = numSamples;
        int index,feature;
        for (index=0; index < numSamples; index++) 
		{
            myModelLabels[index] = trainingLabels[index];

            for (feature=0; feature < numFeatures; feature++) 
			{
                myModel[index][feature] = trainingSamples[index][feature];
            }
        }
        fprintf(stdout,"data stored locally \n");
    }

    //now you could do whatever you like with the data
    //for example,  you could populate some rules etc.
    //you were given pseudocode in semester 1 to do this
    // you could also normalise the data to remove scaling effects if you want to use something like a MLP or kNN
    //just remember that anything that you want to acess in your predictLabel() function
    //needs to be declared static at the top of this file - as I have done for the "myModel"  and myModelLabels data.


	 //for (currentLabel = 0; currentLabel < trainingSamples; currentLabel++)
	 //{
		// //if char to int is equal to 
		// charAsInt = (int)trainingLabels[currentLabel];
		// labelUsed[charAsInt] = labelUsed[charAsInt] + 1;
	 //}


    return returnval;
}

char  predictLabel(double *sample, int numFeatures)
{
	int features;
	int sample_count;
	double test[4];
	int i; //inOrder
	int j; //nextInOrder
	int a; //swapOrder
	double tmp;
	char tmp_char;
	int nearest;
	int example;
	int class_type;
	int highest = 5;
	int sort;
	int labelsort;
	char prediction;
       //this is a silly trivial test function
       // obviously you need to replace this with something that uses the model you built in your train() function

	for (features = 0;features <= numFeatures; features++)
	{
		test[features] = sample[features];
	}

	//assigns every training data with distance to the sample data.
	for (sample_count = 0; sample_count <= NUM_TRAINING_SAMPLES; sample_count++)
	{
		distances_index[sample_count] =
			distanceCalculate(test[0], myModel[sample_count][0],
				test[1], myModel[sample_count][1],
				test[2], myModel[sample_count][2],
				test[3], myModel[sample_count][3]);
	}

	//orders the sample data distances into order.
	for (int i = 0; i < NUM_TRAINING_SAMPLES; i++)//Loop for ascending ordering
	{
		for (int j = 0; j < NUM_TRAINING_SAMPLES; j++)//Loop for comparing other values
		{
			if (distances_index[j] > distances_index[i])//Comparing other array elements
			{
				tmp = distances_index[i];//Using temporary variable for storing last value
				tmp_char = myModelLabels[i];
				distances_index[i] = distances_index[j];//replacing value
				myModelLabels[i] = myModelLabels[j];
				distances_index[j] = tmp;//storing last value
				myModelLabels[j] = tmp_char;				
			}
		}
	}

	for (nearest = 0; nearest <= k; nearest++)
	{
		class_type = myModelLabels[nearest];
		if (class_type == 'a')
		{
			classVotes[1] = classVotes[1] + 1;
		}
		else if (class_type == 'b')
		{
			classVotes[2] = classVotes[2] + 1;
		}
		else if (class_type == 'c')
		{
			classVotes[3] = classVotes[3] + 1;
		}
	}

	if (classVotes[1] > classVotes[2] && classVotes[1] > classVotes[3])
	{
		prediction = 'a';
	}
	else if (classVotes[2] > classVotes[1] && classVotes[2] > classVotes[3])
	{
		prediction = 'b';
	}
	else if (classVotes[3] > classVotes[1] && classVotes[3] > classVotes[2])
	{
		prediction = 'c';
	}
        
	return prediction;
}





