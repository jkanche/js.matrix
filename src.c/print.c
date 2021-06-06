#include <stdio.h>
// #include <stdlib.h>

__attribute__((used)) double printSumFloat64(double *array, int size) {
    double sum = 0;

    for (int i = 0; i < size; ++i) {
        sum += array[i];
    }

    return sum;
}

__attribute__((used)) int* printreturnarray(int size) {
    // int* result = malloc(size * sizeof(double));

    // for (int i = 0; i < size; ++i) {
    //     result[i] = i;
    // }

    double result[] = {1,2,3,4,2};
    int* r_addr = result;

    return r_addr;
}