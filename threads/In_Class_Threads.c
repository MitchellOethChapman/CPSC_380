#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

float avg;
int min, max;

int *values; // dynamic allocation

void *calc_avg(void *arg);
void *calc_min(void *arg);
void *calc_max(void *arg);

int main(int argc, char *argv[])
{
    pthread_t avgThread, minThread, maxThread;

    int res;
    int num_args = argc - 1;

    avg = 0.0;
    max = 0;
    min = 0;

    values = malloc(sizeof(int)*num_args); // wtf is this...
    for (int i = 0; i < num_args; i++) {
        values[i] = atoi(argv[i + 1]);
    }

    // Average
    res = pthread_create(&avgThread, NULL, calc_avg, &num_args);
    if (res != 0) {
        perror("Average thread creation failed");
        exit(EXIT_FAILURE);
    }

    // Max
    res = pthread_create(&maxThread, NULL, calc_max, &num_args);
    if (res != 0) {
        perror("Max thread creation failed");
        exit(EXIT_FAILURE);
    }

    // Min
    res = pthread_create(&minThread, NULL, calc_min, &num_args);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    // Joining the threads
    pthread_join(avgThread, NULL);
    pthread_join(maxThread, NULL);
    pthread_join(minThread, NULL);

    // Printing the results
    printf("The average value is %f\n", avg);
    printf("The maximum value is %i\n", max);
    printf("The minimum value is %i\n", min);

    exit(EXIT_SUCCESS);
}

void *calc_avg(void *arg)
{
    int cnt = *(int *)arg; // typecasting to an integer, then dereferencing the void pointer
    int sum = 0;
    
    for (int i = 0; i < cnt; i++) {
        sum += values[i];
    }
    avg = sum / (float)cnt;
}

void *calc_max(void *arg)
{
    int cnt = *(int *)arg;

    max = values[0];

    for (int i = 0; i < cnt; i++) {
        if (values[i] > max) {
            max = values[i];
        }
    }
}

void *calc_min(void *arg)
{
    int cnt = *(int *)arg;

    min = values[0];

    for (int i = 0; i < cnt; i++) {
        if (values[i] < min) {
            min = values[i];
        }
    }
}