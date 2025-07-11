#include "mySort.h"
#include <stdio.h>

void mySort(int array[], unsigned int first, unsigned int last)
{
    int temp, j;
    if (first < last){
        for (int i = first + 1; i <= last; i++){
            temp = array[i];
            j = i - 1;
            while (j >= first && myCompare(array[j], temp) > 0){
                mySwap(&array[j + 1], &array[j]);
                j = j - 1;
            }
            myCopy(&temp, &array[j + 1]);
        }
    }
}