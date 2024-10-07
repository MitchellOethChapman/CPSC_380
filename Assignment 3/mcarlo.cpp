#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int numIn, numOut;

void *eval_in_circle(void *points);

void main(int argc, char *argv[])
{
    pthread_t evalInsideCircle;

    //create thread
    int res;
    int numVals = 2;
    int numPoints = *(int *) argv[0]; // cast to int

    for (int i = 0; i < numPoints; i++) {
        // generate random point and create thread
        int x = random_double() * 2.0 - 1.0;
        int y = random_double() * 2.0 - 1.0;
    }
    res = pthread_create(&evalInsideCircle, NULL, eval_in_circle, &numPoints);
    if (res != 0) {
        perror("thread creation failed");
        exit(EXIT_FAILURE);
    }

    pthread_join(evalInsideCircle, NULL); // joining the thread

    
        
    exit(EXIT_SUCCESS);
}

void *eval_in_circle(void *points) {
    // int x = *(int *) points; // ?
    // int y = points[1];
    // if (sqrt(x*x + y*y) < 1.0 ) {
        
    // }
}

/* Generates a double precision random number */
double random_double()
{
    return random() / ((double)RAND_MAX + 1);
}
