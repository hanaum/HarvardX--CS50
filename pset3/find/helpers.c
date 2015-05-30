/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    /*
    if (n == 0)
        return false;
    for (int i = 0; i < n; i++) {
        if (values[i] == value)
            return true;
    }
    return false;
    */
    int upper = n - 1;
    int lower = 0;
    int mid = (upper +lower)/2;
    
    while (lower <= upper) {
        if (values[mid] == value)
            return true;
        
        else if (values[mid] < value)
            lower = mid + 1;
        
        else upper = mid + 1;
        
        mid = (upper + lower)/2;
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int tmp, j;
    
    for (int i = 0; i < (n-1); i++) {
        for (j = 0; j <= n-2-i; j++) {
            if (values[j] > values[j+1]) {
                tmp = values[j];
                values[j] = values[j+1];
                values[j+1] = tmp;
            }
        }
    }
}
