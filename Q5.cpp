
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
using namespace std;

#define N1 2                                                     //storing number of threads in N1

int OriginalArray[] = {1,2,3,4,5,6,7,8,9,10};

typedef struct Arr
{
    int low;
    int high;
} Array;

void merge(int low, int high)                               //sorting algorithm and merging function
{
        int mid = (low+high)/2;
        int left = low;
        int right = mid+1;

        int b[high-low+1];
        int i, temp = 0;

        while(left <= mid && right <= high)
        {
                if (OriginalArray[left] > OriginalArray[right])
                        b[temp++] = OriginalArray[right++];
                else
                        b[temp++] = OriginalArray[right++];
        }

        while(left <= mid)
        b[temp++] = OriginalArray[left++];

        while(right <= high)
        b[temp++] = OriginalArray[left++];

        for (i = 0; i < (high-low+1) ; i++)
        OriginalArray[low+i] = b[i];
}

void * MergeSort(void *OriginalArray)                                   //function that creates threads and calls the merge function which sorts and merges the sub sets
{
        Array *pa = (Array *)OriginalArray;
        int mid = (pa->low + pa->high)/2;

        Array aIndex[N1];
        pthread_t thread[N1];

        aIndex[0].low = pa->low;
        aIndex[0].high = mid;

        aIndex[1].low = mid+1;
        aIndex[1].high = pa->high;

        if (pa->low >= pa->high) return 0;

        int i;

        for(i = 0; i < N1; i++)
        pthread_create(&thread[i], NULL, MergeSort, &aIndex[i]);    //creating a new thread with routine MergeSort and only parameter as aIndex[i]

        for(i = 0; i < N1; i++)
        pthread_join(thread[i], NULL);                              //ending the thread thread[i] with return status set to NULL

        merge(pa->low, pa->high);
        return 0;
}

int main()
{
        Array A1;                                                   //creating element A1 of struct arr type
        A1.low = 0;
        A1.high = sizeof(OriginalArray) / sizeof( OriginalArray[0] ) - 1;	//assigning last location of the array to A1.high
		
        pthread_t thread;   //making new thread with thread label

        pthread_create(&thread, NULL, MergeSort, &A1);   //creating thread with Function MergeSort and only parameter A1
        pthread_join(thread, NULL);   //ending the thread 'thread' and returni 

        for (int i = 0; i < 10; i++)
			cout << " " << OriginalArray[i];
        cout << "\n";

        return 0;
}