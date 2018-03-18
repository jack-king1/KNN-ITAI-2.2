//
//  TrainAndTest.h
//  MLCoursework
//
//  Created by Jim Smith on 06/02/2017.
//  Copyright © 2017 Jim SmithJim Smith. All rights reserved.
//

#ifndef TrainAndTest_h
#define TrainAndTest_h

#define IRIS_SET_SIZE 150
#define IRISFEATURES 4

#include <stdio.h>
#include "MLCoursework.h"

int  train( double **trainingSamples, char *trainingLabels, int numSamples, int numFeatures);
char  predictLabel(double *sample, int numFeatures);

#endif /* TrainAndTest_h */
