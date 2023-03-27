#include "array_operations.hh"

int greatest_v1(int* itemptr, int size){
    int max = itemptr[0];
        for (int i = 0; i < size; i++){
            if (itemptr[i] > max){
                max = itemptr[i];
            }
        }
        return max;
    }

int greatest_v2(int *itemptr, int *endptr)
{
    int max = 0;
    while (itemptr < endptr){
        if (*itemptr >= max){
            max=*itemptr;
        }
        ++itemptr;
    }
    return max;
}


void copy(int *itemptr, int *endptr, int *targetptr)
{
    while (itemptr < endptr){
        {
            *targetptr=*itemptr;
        }
        ++itemptr;
        ++targetptr;
    }
}

void reverse(int *leftptr, int *rightptr) {
    --rightptr;
    while (leftptr <= rightptr) {
        int temp = *leftptr;
        *leftptr = *rightptr;
        *rightptr = temp;
        ++leftptr;
        --rightptr;
    }
}
