#include <stdio.h>
#include <stdlib.h>
#include "mySort.h"

 
int main(int argc, char * argv[])
{
    int data[100000]; /* Array of ints to sort */
    int nDataItems;   /* number of actual items in the array */
    int i;

    fprintf(stderr, "I was invoked with the command: %s\n", argv[0]);

    if (argc > 1) {
        //setting the total number of data inputs
        nDataItems = argc - 1;

        //running through the data set given
        for(i = 0; i < argc-1; i++) {
            //adding the vales to the array
            data[i] = atoi(argv[i+1]);
        }
    } else {
        // Hardcoded data set
        nDataItems = 4;
        data[0] = 109;
        data[1] = 3;
        data[2] = 24;
        data[3] = 14;
    }
    
    //calling the sorting method 
    mySort(data, nDataItems);

 

    /* Check that the data array is sorted. */
    for(i = 0; i < nDataItems-1; i++) {
        if (data[i] > data[i+1]) {
            fprintf(stderr, "Sort error: data[%d] (= %d)"
              " should be <= data[%d] (= %d)- -aborting\n",
              i, data[i], i+1, data[i+1]);
            exit(1);
        }
    }

    /* Print sorted array to stdout */
    for(i = 0; i < nDataItems; i++) {
        printf("%d\n", data[i]);
    }
    exit(0);
}
