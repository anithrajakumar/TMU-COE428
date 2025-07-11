#include "mySort.h"
#include <stdio.h>

void merge(int array[], unsigned int first, unsigned int mid, unsigned int last)
{
    int count1 = mid - first + 1;
    int count2 = last - mid;
    int left = 0;
    int right = 0;
    int merged = first;

    //temporary arrays to use when og array gets split
    int arrayLeft[count1];
    int arrayRight[count2];

    //copying the elements of the og array to the temp array
    for (int i = 0; i < count1; ++i){
        myCopy(&array[first + i], &arrayLeft[i]);
    }
    for (int j = 0; j < count2; ++j){
        myCopy(&array[mid + 1 + j], &arrayRight[j]);
    }

    //merges the temporary arrays 
    while (left < count1 && right < count2){
        if (myCompare(arrayLeft[left], arrayRight[right]) <= 0){
            myCopy(&arrayLeft[left],&array[merged]);
            left++;
        }
        else{
            myCopy(&arrayRight[right], &array[merged]);
            right++;
        }
        merged++;
    }
    //merges remaining elements to the left of the og array
    while (left < count1){
        myCopy(&arrayLeft[left++], &array[merged++]);
    }
    //merges remaining elements to the right of the og array
    while (right < count2){
        myCopy(&arrayRight[right++], &array[merged++]);
    }
}

void mySort(int array[], unsigned int first, unsigned int last)
{
    if (first < last){
        //Splitting the array and calling the sort function again
        int mid = (first + last) / 2;
        mySort(array, first, mid);
        mySort(array, mid + 1, last);
        merge(array, first, mid, last);
    }
}